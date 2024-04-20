#include "Interface.h"

Interface::Interface():db("/home/yazzine/Desktop/College_Project/DB/college-project.db"){
	bool continue_loop = true;
	while(continue_loop){
		display_login();
		//Necessary variables to store input data
		int option = 0;
		string username="",password="";
		cin>>option;
		cin.ignore();
		switch(option){
			case 1:{ // Student login 
				student_login();
				continue_loop=false;
				break;
			}
				
			case 2:{ // Teacher login 
				teacher_login();
			    	continue_loop=false;
			    	break;
			}
			
			case 3:{ // Head Of Departement login 
				headofdepartement_login();
				continue_loop=false;
				break;
			}
			    
			case 0:{ //exit program
				cout << "Exiting the program. Goodbye!" << endl;
			    	exit(EXIT_SUCCESS);
			    	break;
			}
			    
			default:{ // Invalid input
				cout << "Invalid option. Please select a valid option." << endl;
			    	break;	
			}
			    
		};
	}
}

// DISPLAYS

void Interface::display_login(){
	std::cout << "Welcome to the College Management System!" << std::endl;
        std::cout << "1. Student Login" << std::endl;
        std::cout << "2. Teacher Login" << std::endl;
        std::cout << "3. Head of Department Login" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
}

void Interface::display_student_menu() {
    	cout << "Student Menu:" << endl;
    	cout << "1. Check Grades" << endl;
    	cout << "2. Check Attendance" << endl;
    	cout << "0. Logout" << endl;
    	cout << "Enter your choice: ";
}

void Interface::display_teacher_menu() {
    	cout << "Teacher Menu:" << endl;
    	cout << "1. Input Mark" << endl;
    	cout << "2. Input Attendance" << endl;
    	cout << "0. Logout" << endl;
    	cout << "Enter your choice: ";
}

void Interface::display_headofdepartement_menu() {
    	cout << "Head of Department Menu:" << endl;
    	cout << "1. Add Teacher" << endl;
    	cout << "2. Remove Teacher" << endl;
    	cout << "3. Add Student" << endl;
    	cout << "4. Remove Student" << endl;
    	cout << "5. Add Course" << endl;
    	cout << "6. Remove Course" << endl;
    	cout << "7. Input Mark" << endl;
	cout << "8. Input Attendance" << endl;
    	cout << "0. Logout" << endl;
    	cout << "Enter your choice: ";
}


// LOGINS

void Interface::student_login(){
	string username, password;
    	cout << "Enter student username: ";
   	getline(cin, username);
    	cout << "Enter student password: ";
    	getline(cin, password);

    	// Perform student login authentication
    	if (db.login_student(username, password)) {
       		// If login successful, display student menu
       		Student student(username,password);
        	handle_student_actions(student);
    	} else {
        	cerr << "Student login failed. Please try again." << endl;
    	}
}

void Interface::teacher_login(){
	string username, password;
    	cout << "Enter teacher username: ";
    	getline(cin, username);
    	cout << "Enter teacher password: ";
    	getline(cin, password);

    	// Perform teacher login authentication
    	if (db.login_teacher(username, password)) {
        	// If login successful, display teacher menu
        	Teacher teacher(username,password);
        	handle_teacher_actions(teacher);
    	} else {
        	cerr << "Teacher login failed. Please try again." << endl;
    	}
}
void Interface::headofdepartement_login(){
	string username, password;
    	cout << "Enter Head of departement username: ";
    	getline(cin, username);
    	cout << "Enter Head of departement password: ";
    	getline(cin, password);

    	// Perform HOD login authentication
    	if (db.login_headofdepartement(username, password)) {
        	// If login successful, display HOD menu
        	HeadOfDepartement headofdepartement(username,password);
        	handle_headofdepartement_actions(headofdepartement);
    	} else {
        	cerr << "Head of departement login failed." << endl;
    	}
}


// HANDLE ACTIONS

void Interface::handle_student_actions(Student& student){
	while(true){
		display_student_menu();
		int option_action = 0;
		cin>>option_action;
		cin.ignore();
		switch(option_action){
			case 1:{ // Check grades
				student.check_grades();
				break;
			}
				
			case 2:{ // Check Attendance
				student.check_attendance();
			    	break;
			}
			    
			case 0:{ //exit program
				cout << "Loging out... Goodbye!" << endl;
			    	exit(EXIT_SUCCESS);
			    	break;
			}
			    
			default:{ // Invalid input
				cout << "Invalid option. Please select a valid option." << endl;
			    	break;	
			}
			    
		};
	}
}
void Interface::handle_teacher_actions(Teacher& teacher){
	while(true){
		display_teacher_menu();
		int option_action = 0;
		cin>>option_action;
		cin.ignore();
		switch(option_action){
			case 1:{ // Check grades
				teacher.input_mark();
				break;
			}
				
			case 2:{ // Check Attendance
				teacher.input_attendance();
			    	break;
			}
			    
			case 0:{ //exit program
				cout << "Loging out... Goodbye!" << endl;
			    	exit(EXIT_SUCCESS);
			    	break;
			}
			    
			default:{ // Invalid input
				cout << "Invalid option. Please select a valid option." << endl;
			    	break;	
			}
			    
		};
	}
}
void Interface::handle_headofdepartement_actions(HeadOfDepartement& hod){
    while (true) {
        display_headofdepartement_menu();
        int option_action = 0;
        cin >> option_action;
        cin.ignore();
        switch (option_action) {
            case 1: { // Add Teacher
                string username, password, first_name, last_name, date_of_birth;
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                cout << "Enter first name: ";
                getline(cin, first_name);
                cout << "Enter last name: ";
                getline(cin, last_name);
                cout << "Enter date of birth (YYYY-MM-DD): ";
                getline(cin, date_of_birth);
                hod.add_teacher(username, password, first_name, last_name, date_of_birth);
                break;
            }
            case 2: { // Remove Teacher
                int teacher_id;
                cout << "Enter teacher ID to remove: ";
                cin >> teacher_id;
                cin.ignore();
                hod.remove_teacher(teacher_id);
                break;
            }
            case 3: { // Add Student
                string username, password, first_name, last_name, date_of_birth;
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                cout << "Enter first name: ";
                getline(cin, first_name);
                cout << "Enter last name: ";
                getline(cin, last_name);
                cout << "Enter date of birth (YYYY-MM-DD): ";
                getline(cin, date_of_birth);
                hod.add_student(username, password, first_name, last_name, date_of_birth);
                break;
            }
            case 4: { // Remove Student
                int student_id;
                cout << "Enter student ID to remove: ";
                cin >> student_id;
                cin.ignore();
                hod.remove_student(student_id);
                break;
            }
            case 5: { // Add Course
                string title, description;
                cout << "Enter course title: ";
                getline(cin, title);
                cout << "Enter course description: ";
                getline(cin, description);
                hod.add_course(title, description);
                break;
            }
            case 6: { // Remove Course
                int course_id;
                cout << "Enter course ID to remove: ";
                cin >> course_id;
                cin.ignore();
                hod.remove_course(course_id);
                break;
            }
            case 7: { // Input Mark
                hod.input_mark();
                break;
            }
            case 8: { // Input Attendance
                hod.input_attendance();
                break;
            }
            case 0: { // Exit
                cout << "Logging out... Goodbye!" << endl;
                exit(EXIT_SUCCESS);
                break;
            }
            default: { // Invalid input
                cout << "Invalid option. Please select a valid option." << endl;
                break;
            }
        };
    }

}

