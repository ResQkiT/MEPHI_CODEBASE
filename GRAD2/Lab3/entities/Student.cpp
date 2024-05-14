#include "Student.h"
#include <string>
Student::Student() : Person(), student_id{0}, current_grand_bill{0}{};
Student::Student(std::string name,std::string surname, size_t student_id) : Person(name, surname), student_id{student_id}, current_grand_bill{0}
{}

Student::Student(std::string name,std::string surname, std::string email, size_t student_id) : Person(name, surname, email), student_id{student_id}, current_grand_bill{0}
{}
Student::Student(std::string name,std::string surname, std::string email, size_t student_id, size_t start_money) :
                Student(name, surname, email, student_id)
{
    current_grand_bill = start_money;
}
Student::Student(const Student & other):Student(other.name, other.surname, other.email, other.student_id, other.current_grand_bill)
{}
Student::Student(Student && other){
    name = std::move(other.name);
    surname = std::move(other.surname);
    email = std::move(other.email);
    student_id = std::move(other.student_id);
    current_grand_bill = std::move(other.current_grand_bill);
    other.name.clear();
    other.surname.clear();
    other.email.clear();
    other.student_id = 0;
    other.current_grand_bill = 0;
} 
Student::~Student() = default;

size_t Student::get_student_id() const{
    return student_id;
}
size_t Student::get_money() const{
    return current_grand_bill;
}
void Student::add_money(size_t extra_grant){
    current_grand_bill += extra_grant;
}
Student& Student::operator=(const Student & other){
    this->name = other.name;
    this->surname = other.surname;
    this->email = other.email;
    this->student_id = other.student_id;
    this->current_grand_bill = other.current_grand_bill;
    return *this;
}