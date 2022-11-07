#define STUDENT_H
#ifndef STUDENT_H

#include <string>

class Student{
    public:
        Student();
        ~Student();
    private:
        int m_ID;
        std::string m_name;
        std::string m_level;
        std::string m_major;
        double m_GPA;
        int m_FID;
};