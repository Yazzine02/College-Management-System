#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

#include "Person.h"
#include "Database.h"


class Student: public Person{
	private:
		unordered_map<int,double> grades;
		vector<int> attendance;
		Database db;
	public:
		Student(const string& username,const string& password);//OK
		//coid check_info(); Inherited from class Person  //OK
		void check_grades();//OK
		void check_attendance();//OK
};

#endif
