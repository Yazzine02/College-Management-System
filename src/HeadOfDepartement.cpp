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
