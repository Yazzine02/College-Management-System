#include <iostream>
#include <string>

#include "Database.h"
#include "Student.h"
#include "Person.h"
#include "Teacher.h"
#include "HeadOfDepartement.h"
#include "Interface.h"

#include <cstdlib> // Needed for rand() and srand()
#include <ctime>   // Needed for time()

using namespace std;

int main(){
	Interface interface;
	/*
	Database db("/home/yazzine/Desktop/College_Project/DB/college-project.db");
	db.create_student("john_doe", "johndoe123", "John", "Doe", "1998-05-15");
	db.create_student("alice_smith", "alice123", "Alice", "Smith", "1999-09-21");
	db.create_student("bob_johnson", "bob123", "Bob", "Johnson", "2000-03-10");
	db.create_student("emily_davis", "emily123", "Emily", "Davis", "1997-11-30");
	db.create_student("michael_brown", "michael123", "Michael", "Brown", "1998-07-04");
	db.create_student("sarah_jones", "sarah123", "Sarah", "Jones", "2001-01-25");
	db.create_student("david_lee", "david123", "David", "Lee", "1999-08-12");
	db.create_student("emma_taylor", "emma123", "Emma", "Taylor", "2000-04-18");
	db.create_student("james_wilson", "james123", "James", "Wilson", "1998-12-05");
	db.create_student("olivia_clark", "olivia123", "Olivia", "Clark", "1997-06-28");

	db.create_teacher("michael_johnson", "michael123", "Michael", "Johnson", "1978-05-15");
	db.create_teacher("emily_brown", "emily123", "Emily", "Brown", "1982-11-28");
	db.create_teacher("john_smith", "john123", "John", "Smith", "1975-09-20");

	db.create_headofdepartement("alice_williams", "alice123", "Alice", "Williams", "1967-03-10");
	db.create_headofdepartement("david_miller", "david123", "David", "Miller", "1972-08-22");
	
    
    db.add_course("Introduction to Computer Science", "This course introduces the basics of computer science.");
    db.add_course("Data Structures and Algorithms", "This course covers fundamental data structures and algorithms.");
    db.add_course("Object-Oriented Programming", "This course teaches object-oriented programming principles.");
    db.add_course("Database Management Systems", "This course covers database design and querying.");
    db.add_course("Web Development", "This course covers web development technologies and frameworks.");
    
	srand(time(nullptr));

	for(int student_id = 1; student_id <= 11; student_id++) {
		for(int course_id = 1; course_id <= 9; course_id++) {
		    // Generate a random double between 1.0 and 20.0
		    double random_mark = 1.0 + static_cast<double>(rand()) / RAND_MAX * 19.0;
		    db.input_mark(course_id, student_id, random_mark);
		}
	}
	*/
	return 0;
}
