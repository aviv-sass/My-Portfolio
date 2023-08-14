#include "student.h"
using namespace std;

namespace mtm{
    class Student;

    Student::Student(const int i):id(i){}
            
    Student::Student(const Student& s):id(s.id){}

    bool Student::operator<(const Student& stud){
        return this->id < stud.id;
    }

    bool Student::operator>(const Student& stud){
        return this->id > stud.id;
    }

    bool Student::operator==(const Student& stud){
        return this->id == stud.id;
    }

    bool Student::operator!=(const Student& stud){
        return this->id != stud.id;
    }

    int Student::studentIdGet(){
        return id;
    }
}