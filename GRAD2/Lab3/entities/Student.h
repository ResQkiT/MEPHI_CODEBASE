#pragma once
#include "Person.h"
#include <string>

class Student : public Person
{
private:
    const size_t student_id;
public:
    Student(std::string name,std::string surname, size_t student_id);
    Student(std::string name,std::string surname, std::string email, size_t student_id);
    ~Student();
    size_t get_student_id() const;
};

