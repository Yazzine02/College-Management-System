#ifndef TEACHER_H
#define TEACHER_H

#include <iostream>
#include <string>
#include "Person.h"
#include "Database.h"

class Teacher : public Person {
protected:
    Database db;
public:
	Teacher();
    Teacher(const std::string& username, const std::string& password);//OK
    //void show_info();  Inherited from class Person
    void input_mark();//OK
    void input_attendance();//OK
};

#endif
