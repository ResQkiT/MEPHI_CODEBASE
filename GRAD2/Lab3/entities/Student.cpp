#include "Student.h"
#include <string>

Student::Student(std::string name,std::string surname, size_t student_id) : Person(name, surname), student_id{student_id}
{}

Student::Student(std::string name,std::string surname, std::string email, size_t student_id) : Person(name, surname, email), student_id{student_id}
{}
Student::~Student() = default;

size_t Student::get_student_id() const{
    return student_id;
}