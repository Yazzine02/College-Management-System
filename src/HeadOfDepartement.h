#include <iostream>
#include <string>
#include "Teacher.h"

class HeadOfDepartment:public Teacher{
	public:
		void add_teacher();
		void remove_teacher();
		void add_student();
		void remove_student();
		void add_course();
		void remove_course();
		void time_table();
}
