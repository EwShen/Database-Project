//Ewan Shen
//2396486
//ewshen@chapman.edu
//Michael Smith
//2396546
//michsmith@chapman.edu
//CPSC-350-01
//PA5
//describes the attributes of a student object
//including the Student's id, name, level, major, gpa, and faculty id

#include "Student.h"
#include <iostream>
#include <cstdlib>

Student::Student(){
    m_ID = 0;
    m_name = "";
    m_level = "";
    m_major = "";
    m_GPA = 0;
    m_FID = 0;
}

Student::Student(int id, string name, string level, string major, double gpa, int fid){
    m_ID = id;
    m_name = name;
    m_level = level;
    m_major = major;
    m_GPA = gpa;
    m_FID = fid;
}

//destructor - a special class member function that is called automatically when a variable of that type is destroyed
//if the object is created using "new" or the constructor uses new to allocate memory on the heap, the destructor should use "delete" to free the memory
Student::~Student(){
}

// accessors

int Student::getID(){
    return m_ID;
}

string Student::getName(){
    return m_name;
}

string Student::getLevel(){
    return m_level;
}

string Student::getMajor(){
    return m_major;
}

double Student::getGPA(){
    return m_GPA;
}

int Student::getFID(){
    return m_FID;
}

// mutators
void Student::setID(int id){
    m_ID = id;
}

void Student::setName(string name){
    m_name = name;
}

void Student::setLevel(string level){
    m_level = level;
}

void Student::setMajor(string major){
    m_major = major;
}

void Student::setGPA(double gpa){
    m_GPA = gpa;
}

void Student::setFID(int fid){
    m_FID = fid;
}

//overloaded operators
//simplifies code by overloading the operator and directly comparing two student objects
//standard comparison operations are implemented (greater than, less than, equal to, etc...)
//the student IDs are compared
bool operator > (Student& a, Student& b){
    if (a.getID() > b.getID()){
        return true;
    }else{
        return false;
    }
}

bool operator < (Student& a, Student& b){
    if (a.getID() < b.getID()){
        return true;
    }else{
        return false;
    }
}

bool operator >= (Student& a, Student& b){
    if (a.getID() >= b.getID()){
        return true;
    }else{
        return false;
    }
}

bool operator <= (Student& a, Student& b){
    if (a.getID() <= b.getID()){
        return true;
    }else{
        return false;
    }
}

bool operator == (Student& a, Student& b){
    if (a.getID() == b.getID()){
        return true;
    }else{
        return false;
    }
}

bool operator != (Student& a, Student& b){
    if (a.getID() != b.getID()){
        return true;
    }else{
        return false;
    }
}

//overloaded operator
//directly prints the information of the faculty when the operator is called upon
std::ostream& operator<<(std::ostream& os, Student& s)
{
    os << "Student ID: " << s.getID() << endl;
    os << "Student Name: " << s.getName() << endl;
    os << "Student Level: " << s.getLevel() << endl;
    os << "Student Major: " << s.getMajor() << endl;
    os << "Student GPA: " << s.getGPA() << endl;
    os << "Student's Advisor Faculty ID: " << s.getFID() << endl;
    return os;
}