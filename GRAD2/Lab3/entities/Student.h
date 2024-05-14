#pragma once
#include "Person.h"
#include <string>

class Student : public Person
{
private:
    size_t student_id;
    size_t current_grand_bill;
public:
    Student();
    Student(std::string name,std::string surname, size_t student_id);
    Student(std::string name,std::string surname, std::string email, size_t student_id);
    Student(std::string name,std::string surname, std::string email, size_t student_id, size_t start_money);
    Student(const Student & other);
    Student(Student && other);
    ~Student();
    size_t get_student_id() const;
    size_t get_money() const;
    void add_money(size_t extra_grant) ;
    Student& operator=(const Student & other);
};

