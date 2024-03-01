//Ewan Shen
//2396486
//ewshen@chapman.edu
//Michael Smith
//2396546
//michsmith@chapman.edu
//CPSC-350-01
//PA5
//describes the attributes of a faculty object
//including the faculty's id, name, level, department, and list of advisees' id

#include "Faculty.h"
#include <iostream>
#include <cstdlib>

//default constructor
Faculty::Faculty(){
    m_ID = 0;
    m_name = "";
    m_level = "";
    m_department = "";
    m_adviseesID = new DblList<int>();
}

//constructor
Faculty::Faculty(int id, string name, string level, string department){
    m_ID = id;
    m_name = name;
    m_level = level;
    m_department = department;
    m_adviseesID = new DblList<int>();
}

//destructor
Faculty::~Faculty(){
}

// accessors

int Faculty::getID(){
    return m_ID;
}

string Faculty::getName(){
    return m_name;
}

string Faculty::getLevel(){
    return m_level;
}

string Faculty::getDepartment(){
    return m_department;
}

// mutators
void Faculty::setID(int id){
    m_ID = id;
}

void Faculty::setName(string name){
    m_name = name;
}

void Faculty::setLevel(string level){
    m_level = level;
}

void Faculty::setDepartment(string department){
    m_department = department;
}

void Faculty::addStudent(int id){
    m_adviseesID->addBack(id);
}

void Faculty::removeStudent(int id){
    m_adviseesID->removeElement(id);
}

DblList<int>* Faculty::getAdviseesID(){
    return m_adviseesID;
}

//overloaded operators
//simplifies code by overloading the operator and directly comparing two faculty objects
//standard comparison operations are implemented (greater than, less than, equal to, etc...)
//the faculy IDs are compared
bool operator>(Faculty& a, Faculty& b){
    if (a.getID() > b.getID()){
        return true;
    }else{
        return false;
    }
}

bool operator<(Faculty& a, Faculty& b){
    if (a.getID() < b.getID()){
        return true;
    }else{
        return false;
    }
}

bool operator>=(Faculty& a, Faculty& b){
    if (a.getID() >= b.getID()){
        return true;
    }else{
        return false;
    }
}

bool operator<=(Faculty& a, Faculty& b){
    if (a.getID() <= b.getID()){
        return true;
    }else{
        return false;
    }
}

bool operator==(Faculty& a, Faculty& b){
    if (a.getID() == b.getID()){
        return true;
    }else{
        return false;
    }
}

bool operator!=(Faculty& a, Faculty& b){
    if (a.getID() != b.getID()){
        return true;
    }else{
        return false;
    }
}

//overloaded operator
//directly prints the information of the faculty when the operator is called upon
ostream& operator<<(ostream& os, Faculty& f)
{
    os << "Faculty ID: " << f.getID() << "\n";
    os << "Faculty Name: " << f.getName() << "\n";
    os << "Faculty Level: " << f.getLevel() << "\n";
    os << "Faculty Department: " << f.getDepartment() << "\n";
    os << "Faculty Advisees' IDs:\n";
    DblList<int>* advisees = f.getAdviseesID();
    advisees->log(os);
    os << std::endl;
    return os;
}