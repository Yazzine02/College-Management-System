#include "Person.h"

Person::Person(const std::string& first_name, const std::string& last_name, const std::string& date_of_birth,
               const std::string& username, const std::string& password, int id)
    : first_name(first_name), last_name(last_name), date_of_birth(date_of_birth),
      username(username), password(password), id(id) {}

void Person::check_info() {
    std::cout << "ID: " << this->id << std::endl;
    std::cout << "Username: " << this->username << std::endl;
    std::cout << "First name: " << this->first_name << std::endl;
    std::cout << "Last name: " << this->last_name << std::endl;
    std::cout << "Date of birth: " << this->date_of_birth << std::endl;
}
