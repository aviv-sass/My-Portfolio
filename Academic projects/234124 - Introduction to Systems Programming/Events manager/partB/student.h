#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
#include <ostream>
using std::cout;
using std::endl;
using namespace std;

namespace mtm{
    class Student{
        private:
            int id;
        public:
            Student(const int i);
            Student(const Student& s);
            bool operator<(const Student& stud);
            bool operator>(const Student& stud);
            bool operator==(const Student& stud);
            bool operator!=(const Student& stud);
            
            /**
            * studentIdGet: get the id of the student.
            * @return :
            * 	a integer - the id.
            */ 
            int studentIdGet();
            ~Student() = default;
    };
}

#endif