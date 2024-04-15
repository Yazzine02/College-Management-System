#include <iostream>
#include <string>
#include "Person.h"

class Student: public Person{
	public:
		Student(string first_name,string last_name,string date_of_birth,int id);
		void check_grades();
		void check_attendance();
		void check_timetable();
		void choose_course();
}
