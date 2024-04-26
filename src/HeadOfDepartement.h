#ifndef HEADOFDEPARTEMENT_H
#define HEADOFDEPARTEMENT_H

#include <iostream>
#include <string>
#include "Teacher.h"

class HeadOfDepartement : public Teacher {
public:
    HeadOfDepartement(const std::string& username, const std::string& password);//OK
    //void check_info();  Inherited from class Person
    //void input_mark();//OK
    //void input_attendance();
    void add_teacher(const std::string& username, const std::string& password,  const std::string& first_name, const std::string& last_name, const std::string& date_of_birth);
    void remove_teacher(int teacher_id);
    void add_student(const std::string& username, const std::string& password, const std::string& first_name, const std::string& last_name, const std::string& date_of_birth);
    void remove_student(int student_id);
    void add_course(const string& title,const string& description);
    void remove_course(int course_id);
    void search_person();
    //void time_table();
};

#endif

