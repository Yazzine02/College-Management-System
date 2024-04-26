#include "HeadOfDepartement.h"

HeadOfDepartement::HeadOfDepartement(const std::string& username, const std::string& password)
    : Teacher() {
    db.get_head_of_departement_info(username, password, &first_name, &last_name, &date_of_birth, &id);
}

void HeadOfDepartement::add_teacher(const std::string& username, const std::string& password,  const std::string& first_name, const std::string& last_name, const std::string& date_of_birth){
	db.add_teacher(username,password,first_name,last_name,date_of_birth);
}

void HeadOfDepartement::remove_teacher(int teacher_id){
	db.remove_teacher(teacher_id);
}
void HeadOfDepartement::add_student(const std::string& username, const std::string& password, const std::string& first_name, const std::string& last_name, const std::string& date_of_birth){
	db.add_student(username,password,first_name,last_name,date_of_birth);
}
void HeadOfDepartement::remove_student(int student_id){
	db.remove_student(student_id);
}
void HeadOfDepartement::add_course(const string& title,const string& description){
	db.add_course(title,description);
}
void HeadOfDepartement::remove_course(int course_id){
	db.remove_course(course_id);
}
void HeadOfDepartement::search_person(){
	cout << "What type of person are you looking for ?" << endl;
	cout << "1. Student" << endl;
	cout << "2. Teacher" << endl;
	cout << "3. Head of Departement" << endl;
	cout << "Enter your choice: " << endl;
	int option;
	cin >> option;
	cin.ignore(); // Ignore the newline character in the input buffer

	switch (option){
		case 1:{
			cout << "You are Searching for a student." << endl;
			cout << "Please enter the student id: " << endl;
			int student_id;
			cin >> student_id;
			cin.ignore();
			db.search_student(student_id);
			break;
		}
		case 2:{
			cout << "You are Searching for a teacher." << endl;
			cout << "Please enter the teacher id: " << endl;
			int teacher_id;
			cin >> teacher_id;
			cin.ignore();
			db.search_teacher(teacher_id);
			break;
		}
		case 3:{
			cout << "You are Searching for a head of departement." << endl;
			cout << "Please enter the head of departement id: " << endl;
			int hod_id;
			cin >> hod_id;
			cin.ignore();
			db.search_headofdepartement(hod_id);
			break;
		}
		default:
			cout << "Invalid option. Please enter a valid option." << endl;
	}
}
