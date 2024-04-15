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
		
		bool create_student(const std::string& username, const std::string& password, const std::string& first_name, const std::string& last_name, const std::string& date_of_birth);
		bool login_student(const std::string& username, const std::string& password);
		bool create_teacher(const std::string& username, const std::string& password,  const std::string& first_name, const std::string& last_name, const std::string& date_of_birth);
		bool login_teacher(const std::string& username, const std::string& password);
		bool create_headofdepartement(const std::string& username, const std::string& password,  const std::string& first_name, const std::string& last_name, const std::string& date_of_birth);
		bool login_headofdepartement(const std::string& username, const std::string& password);
		
		bool input_mark(int course_id, int student_id, double note);
	    	bool input_attendance(int courseId, int studentId);

	    	bool add_teacher(const std::string& username, const std::string& password,  const std::string& first_name, const std::string& last_name, const std::string& date_of_birth);
	   	bool remove_teacher(int teacher_id);
	    	/*bool add_student(int student_id);
	    	bool remove_student(int student_id);
	    	bool add_course(int course_id);
	    	bool remove_course(int course_id);
	    	*/
};
