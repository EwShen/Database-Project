//Ewan Shen
//2396486
//ewshen@chapman.edu
//Michael Smith
//2396546
//michsmith@chapman.edu
//CPSC-350-01
//PA5
//header file for student class

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

class Student{
    public:
        Student();
        Student(int id, string name, string level, string major, double gpa, int fid);
        virtual ~Student();
        // mutators and accessors
        //accessors
        int getID();
        std::string getName();
        std::string getLevel();
        std::string getMajor();
        double getGPA();
        int getFID();
        //mutators
        void setID(int id);
        void setName(string name);
        void setLevel(string level);
        void setMajor(string major);
        void setGPA(double gpa);
        void setFID(int fid);
    private:
        //private member variables
        int m_ID;
        std::string m_name;
        std::string m_level;
        std::string m_major;
        double m_GPA;
        int m_FID;
};

#endif