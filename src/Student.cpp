#include "Student.h"

Student::Student(const std::string& username, const std::string& password)
    : Person("a","a","a",username,password,0), db("/home/yazzine/Desktop/College_Project/DB/college-project.db") {
    db.get_student_info(username, password, &first_name, &last_name, &date_of_birth, &id);
    grades=db.get_grades(id);
    attendance=db.get_attendance(id);
}

void Student::check_grades(){
	cout<<"Grade(s)"<<endl;
	for(auto grade:db.get_grades(1))
		cout<<"Course ID: "<<grade.first<<"; "<<"Mark: "<<grade.second<<endl;
}
void Student::check_attendance(){
	cout<<"Missed Course(s)"<<endl;
	for(auto attendance:db.get_attendance(1))
		cout<<"Course ID: "<<attendance<<endl;
}
