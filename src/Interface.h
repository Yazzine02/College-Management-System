#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>

#include "Database.h"
#include "Student.h"
#include "Person.h"
#include "Teacher.h"
#include "HeadOfDepartement.h"

using namespace std;

class Interface{
	private:
		Database db;
	public:
		Interface();
		
		// Displays
		void display_login();
		
		void display_student_menu();
		void display_teacher_menu();
		void display_headofdepartement_menu();
		
		// LOGINS
		void student_login();
		void teacher_login();
		void headofdepartement_login();
		
		// HANDLE ACTIONS
	    	void handle_student_actions(Student& student);
	    	void handle_teacher_actions(Teacher& teacher);
	    	void handle_headofdepartement_actions(HeadOfDepartement& hod);
	    	
};

#endif
