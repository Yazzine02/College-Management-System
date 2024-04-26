#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Database{
	private:
		sqlite3* db;
		
	public:
		Database(const string& dbPath);
		~Database();
		
		// UTILITIES
		void get_student_info(const std::string& username, const std::string& password, std::string* first_name, std::string* last_name, std::string* date_of_birth, int* student_id);//OK
		void get_teacher_info(const string& username, const string& password, string* first_name, string* last_name, string* date_of_birth, int* teacher_id);//OK
    void get_head_of_departement_info(const string& username, const string& password, string* first_name, string* last_name, string* date_of_birth, int* hod_id);//OK

		// STUDENT SECTION
		bool create_student(const std::string& username, const std::string& password, const std::string& first_name, const std::string& last_name, const std::string& date_of_birth);//OK
		bool login_student(const std::string& username, const std::string& password);//OK
		unordered_map<int,double> get_grades(int student_id);//OK
		vector<int> get_attendance(int student_id);//OK
		
		// TEACHER SECTION
		bool create_teacher(const std::string& username, const std::string& password, const std::string& first_name, const std::string& last_name, const std::string& date_of_birth);//OK
		bool login_teacher(const std::string& username, const std::string& password);//OK
		bool input_mark(int course_id, int student_id, double note);//OK
		bool input_attendance(int course_id,int student_id);//OK
		
		// HEAD OF DEPARTEMENT SECTION
		bool create_headofdepartement(const std::string& username, const std::string& password, const std::string& first_name, const std::string& last_name, const std::string& date_of_birth);//OK
		bool login_headofdepartement(const std::string& username, const std::string& password);//OK
		bool add_teacher(const std::string& username, const std::string& password,  const std::string& first_name, const std::string& last_name, const std::string& date_of_birth);//OK
		bool remove_teacher(int teacher_id);//OK
		bool add_student(const std::string& username, const std::string& password, const std::string& first_name, const std::string& last_name, const std::string& date_of_birth);//OK
		bool remove_student(int student_id);//OK
		bool add_course(const string& title,const string& description);//OK
		bool remove_course(int course_id);//OK
		bool search_student(int student_id);//OK
		bool search_teacher(int teacher_id);//OK
		bool search_headofdepartement(int hod_id);//OK
};

#endif
