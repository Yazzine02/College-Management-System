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
    std::cout << "\033[1;4;97mWelcome to the College Management System!\033[0m" << std::endl;
    std::cout << "\033[96m1. Student Login\033[0m" << std::endl;
    std::cout << "\033[94m2. Teacher Login\033[0m" << std::endl;
    std::cout << "\033[95m3. Head of Department Login\033[0m" << std::endl;
    std::cout << "\033[31m0. Exit\033[0m" << std::endl;
    std::cout << "\033[97m\033[1;3mEnter your choice: \033[0m";
}

void Interface::display_student_menu() {
    std::cout << "\033[96m\033[1;4mStudent Menu:\033[0m" << std::endl;
    std::cout << "\033[96m1. Check Grades\033[0m" << std::endl;
    std::cout << "\033[96m2. Check Attendance\033[0m" << std::endl;
    std::cout << "\033[31m0. Logout\033[0m" << std::endl;
    std::cout << "\033[97m\033[1;3mEnter your choice: \033[0m";
}

void Interface::display_teacher_menu() {
    std::cout << "\033[94m\033[1;4mTeacher Menu:\033[0m" << std::endl;
    std::cout << "\033[94m1. Input Mark\033[0m" << std::endl;
    std::cout << "\033[94m2. Input Attendance\033[0m" << std::endl;
    std::cout << "\033[31m0. Logout\033[0m" << std::endl;
    std::cout << "\033[97m\033[1;3mEnter your choice: \033[0m";
}

void Interface::display_headofdepartement_menu() {
    std::cout << "\033[95m\033[1;4mHead of Department Menu:\033[0m" << std::endl;
    std::cout << "\033[95m1. Add Teacher\033[0m" << std::endl;
    std::cout << "\033[95m2. Remove Teacher\033[0m" << std::endl;
    std::cout << "\033[95m3. Add Student\033[0m" << std::endl;
    std::cout << "\033[95m4. Remove Student\033[0m" << std::endl;
    std::cout << "\033[95m5. Add Course\033[0m" << std::endl;
    std::cout << "\033[95m6. Remove Course\033[0m" << std::endl;
    std::cout << "\033[95m7. Input Mark\033[0m" << std::endl;
    std::cout << "\033[95m8. Input Attendance\033[0m" << std::endl;
    std::cout << "\033[95m9. Search person\033[0m" << std::endl;
    std::cout << "\033[31m0. Logout\033[0m" << std::endl;
    std::cout << "\033[97m\033[1;3mEnter your choice: \033[0m";
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
            case 9: { // Search person
                hod.search_person();
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

