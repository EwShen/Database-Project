//Ewan Shen
//2396486
//ewshen@chapman.edu
//Michael Smith
//2396546
//michsmith@chapman.edu
//CPSC-350-01
//PA5
//header file for faculty class

#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include "DblList.h"

using namespace std;

class Faculty{
    public:
    //  integer Faculty ID, a string name, a string level
    //(lecturer, assistant prof, associate prof, etc.), a string department, 
    // and a list of integers corresponding to all of the faculty member’s advisees’ ids
        Faculty();//constructor
        Faculty(int id, string name, string level, string department);
        virtual ~Faculty();//destructor
        // mutators and accessors
        //accessors
        int getID();
        std::string getName();
        std::string getLevel();
        std::string getDepartment();
        DblList<int>* getAdviseesID();
        //mutators
        void setID(int id);
        void setName(string name);
        void setLevel(string level);
        void setDepartment(string department);
        void addStudent(int id);
        void removeStudent(int id);
    private:
        //private member variables
        int m_ID;
        std::string m_name;
        std::string m_level;
        std::string m_department;
        DblList<int>* m_adviseesID;
};

#endif