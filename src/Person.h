#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <ostream>
#include <string>

using namespace std;

class Person {
protected:
    string first_name, last_name, date_of_birth;
    string username, password;
    int id;
public:
    Person(const string& first_name, const string& last_name, const string& date_of_birth,
           const string& username, const string& password, int id);
    void check_info();
};


#endif
