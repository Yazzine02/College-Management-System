#include <Person.h>

Person::Person(string first_name,string last_name,string date_of_birth,string username,string password,int id){
	first_name=first_name;
	last_name=last_name;
	date_of_birth=date_of_birth;
	username=username;
	password=password;
	id=id;
}

void Person::check_info {
	cout<<"ID:"<<id<<endl;
	cout<<"First name:"<<first_name<<endl;
	cout<<"Last name:"<<last_name<<endl;
	cout<<"Date of birth"<<date_of_birth<<endl;
}
