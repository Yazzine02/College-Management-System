#include <iostream>
#include <string>

using namespace std;

class Person{
	protected:
		string first_name,last_name,date_of_birth;
		string username,password;
		int id;
		int status;
	public:
		Person(string first_name,string last_name,string date_of_birth,int id);
		void check_info();
}
