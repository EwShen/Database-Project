//Ewan Shen
//2396486
//ewshen@chapman.edu
//Michael Smith
//2396546
//michsmith@chapman.edu
//CPSC-350-01
//PA5
//main class for the Database project
//prints out the 11 options for the user and prompts an input
//depending on the input, a case is selected and the code is ran
//error handling is accounted for

#include "ScapegoatST.h"
#include "Faculty.cpp"
#include "Student.cpp"
#include <iostream>
#include <limits>
#include  <bits/stdc++.h>


int main(){
    ScapegoatST<Faculty>* facultyTree = new ScapegoatST<Faculty>();//creates a new faculty scapegoat tree
    ScapegoatST<Student>* studentTree = new ScapegoatST<Student>();//creates a new student scapegoat tree
    bool exit = false;//boolean variable is set to false, meaning the program is still prompting the user for an input or executing a case
    int choice;//int variable for user choice

    //while loop to repeatedly prompt user for inputs until case 11 is chosen
    while(!exit){
        std::cout << "\n1.    Print all students and their information (sorted by ascending id #)\n";
        std::cout << "2.    Print all faculty and their information (sorted by ascending id #)\n";
        std::cout << "3.    Find and display student information given the students id\n";
        std::cout << "4.    Find and display faculty information given the faculty id\n";
        std::cout << "5.    Add a new student\n";
        std::cout << "6.    Delete a student given the id\n";
        std::cout << "7.    Add a new faculty member\n";
        std::cout << "8.    Delete a faculty member given the id.\n";
        std::cout << "9.    Change a student’s advisor given the student id and the new faculty id.\n";
        std::cout << "10.   Remove an advisee from a faculty member given the ids\n";
        std::cout << "11.   Exit\n";
        std::cout << std::endl;

        std::cin >> choice;
        std::cout << "\n";
        if(std::cin.fail()){//if the user does not type an input between 1 and 11, the error handling catches it and continues the while loop
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid Input - Type a number between 1 and 11 to perform a command" << endl;
            continue;
        }
        switch(choice){//switch statement providing the 11 case choices
            case 1:{//case 1 prints the student scapegoat tree in order
                studentTree->printInOrder();
                break;
            }
            case 2:{//case 2 prints the faculty scapegoat tree in order
                facultyTree->printInOrder();
                break;
            }
            case 3:{//case 3 finds and displays student information given the student ID
                int id;
                std::cout << "Enter the student's ID: ";
                std::cin >> id;
                if(std::cin.fail()){//error handling to catch invalid inputs
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid Input - Type a number for the student's ID" << endl;
                    continue;
                }
                Student s = Student();
                s.setID(id);
                
                if(studentTree->contains(s)){//contains method checks to see if the student ID is in the student scapegoat tree
                    s = studentTree->find(s);
                    std::cout << "\n" << s << std::endl;
                }else{
                    std::cout << "Could not find student" << std::endl;//if the student is not found, a message is outputted
                }
                break;
            }
            case 4:{//case 4 finds and displays faculty information given the faculty ID
                int id;
                std::cout << "Enter the faculty's ID: ";
                std::cin >> id;
                if(std::cin.fail()){//error handling to catch invalid inputs
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid Input - Type a number for the faculty's ID" << endl;
                    continue;
                }
                Faculty f = Faculty();
                f.setID(id);

                if(facultyTree->contains(f)){//contains method checks to see if the faculty is in the faculty scapegoat tree
                    f = facultyTree->find(f);
                    std::cout << "\n" << f << std::endl;
                }else{
                    std::cout << "Could not find faculty" << std::endl;
                }
                break;
            }
            case 5:{//case 5 adds a new student to the databse
                int id;//member variables define to the student object about to be added
                std::string name; 
                std::string level;
                std::string major; 
                double gpa;
                int fid;

                std::cout << "Enter the student's ID: ";
                std::cin >> id;
                if(std::cin.fail()){//error handling to catch invalid inputs
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid Input - Type a number for the student's ID" << endl;
                    continue;
                }
                
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "\nEnter the student's name: ";//student name is prompted and input is taken
                
                std::getline(cin, name);

                std::cout << "\nEnter the student's level: ";//student level is prompted and input is taken
                std::getline(cin, level);
                
                std::cout << "\nEnter the student's major: ";//student major is prompted and input is taken
                std::getline(cin, major);

                std::cout << "\nEnter the student's GPA: ";//student GPA is prompted and input is taken
                std::cin >> gpa;
                if(std::cin.fail()){//error handling to catch invalid inputs
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid Input - Type a number for the student's GPA" << endl;
                    continue;
                }
                
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


                std::cout << "\nEnter the ID of the student's advisor: ";//student's adviser ID is prompted and input is taken
                std::cin >> fid;
                if(std::cin.fail()){//error handling to catch invalid inputs
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid Input - Type a number for the student's advisor's ID" << endl;
                    continue;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                Faculty f = Faculty();
                f.setID(fid);
                if(facultyTree->contains(f)){//contains method looks to see if the faculty is in the faculty scapegoat tree based on the ID
                    f = facultyTree->find(f);
                }else{
                    std::cout << "Could not find faculty" << std::endl;//if the faculty is not in the tree, message is outputted
                    break;
                }

                Student s = Student(id, name, level, major, gpa, fid);
                if(studentTree->contains(s)){
                    std::cout << "A student with this ID already exists" << std::endl;//if the contains method returns with a student that already exists, a message is outputted
                    break;
                }
                f = facultyTree->find(f);
                f.addStudent(id);//if all the tests are passed and the student is viable to be added to the tree, the faculty is assigned the student
                studentTree->insert(s);//the student is added to the tree

                break;
            }
            case 6:{//case 6 deletes a student given the id
                int sid;
                std::cout << "Enter the student's ID: ";
                if(std::cin.fail()){//error handling to catch invalid inputs
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid Input - Type a number for the student's ID" << endl;
                    continue;
                }
                std::cin >> sid;

                Student s = Student();
                s.setID(sid);
                if(studentTree->contains(s)){//contains method searches for the student in the tree based on the ID
                    s = studentTree->find(s);
                    // std::cout << "\n" << s << std::endl;
                }else{
                    std::cout << "Could not find student" << std::endl;//if the student is not found, a message is outputted
                    break;
                }

                int fid = studentTree->find(s).getFID();//if the student is found, the student's adviser is accessed
                if(fid != 0){
                    Faculty f = Faculty();
                    f.setID(fid);
                    facultyTree->find(f).removeStudent(sid);//the student is removed from the faculty's advisee list
                    f = facultyTree->find(f);
                }
        
                s = studentTree->find(s);//the student is found in the student scapegoat tree
                studentTree->remove(s);//the student is removed from the student scapegoat tree
                break;
            }
            case 7:{//case 7 adds a new faculty member
                int id;//the faculty member's private member variables are defined for the object
                std::string name; 
                std::string level;
                std::string department;

                std::cout << "Enter the faculty's ID: ";//the faculty ID is prompted for, and an input is taken
                std::cin >> id;
                if(std::cin.fail()){//error handling to catch invalid inputs
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid Input - Type a number for the faculty's ID" << endl;
                    continue;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "\nEnter the faculty's name: ";//the faculty's name is prompted for and an input is taken
                std::getline(cin, name);

                std::cout << "\nEnter the faculty's level: ";//the faculty's level is prompted for and an input is taken
                std::getline(cin, level);

                std::cout << "\nEnter the faculty's department: ";//the faculty's department is prompted for and an input is taken
                std::getline(cin, department);

                Faculty f = Faculty(id, name, level, department);
                if(facultyTree->contains(f)){//the contains method searches for the faculty
                    std::cout << "A faculty with this ID already exists" << std::endl;//if the faculty already exists, a message is outputted
                    break;
                }
                facultyTree->insert(f);//the faculty is inserted into the faculty scapegoat tree
                f = facultyTree->find(f);
                break;
            }
            case 8:{//case 8 deletes a faculty member given the ID
                int id;
                std::cout << "Enter the faculty's ID: ";//faculty ID is prompted and an input is taken
                std::cin >> id;
                if(std::cin.fail()){//error handling to catch invalid inputs
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid Input - Type a number for the faculty's ID" << endl;
                    continue;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                Faculty f = Faculty();
                f.setID(id);

                if(facultyTree->contains(f)){//contains method looks to see if the faculty scapegoat tree contains the given faculty
                    f = facultyTree->find(f);
                    // std::cout << "\n" << f << std::endl;
                }else{
                    std::cout << "Could not find faculty" << std::endl;//if the faculty is not found, a message is outputted
                    break;
                }

                DblList<int>* list = f.getAdviseesID();//the faculty being removed has its list of advisees accessed
                if(list != nullptr && list->getSize() > 0){
                    int fid;
                    std::cout << "Enter the ID of the new advisor for the advisees: ";
                    std::cin >> fid;

                    if(std::cin.fail()){//error handling to catch invalid inputs
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid Input - Type a number for the faculty's ID" << endl;
                        continue;
                    }
                    Faculty f = Faculty();
                    f.setID(fid);

                    if(facultyTree->contains(f)){//contains method looks to see if the faculty scapegoat tree contains the given faculty
                        f = facultyTree->find(f);
                        // std::cout << "\n" << f << std::endl;
                    }else{
                        std::cout << "Could not find faculty" << std::endl;//if the faculty is not found, a message is outputted
                        break;
                    }

                    Student s = Student();
                    int size = list->getSize();
                    for(int i = 0; i < size; i++){//the list of advisees IDs is iterated through and the IDs are deleted
                        s.setID(list->removeFront());
                        studentTree->find(s).setFID(fid);
                        s = studentTree->find(s);
                        f.addStudent(s.getID());
                    }
                }
                facultyTree->remove(f);//the faculty is removed from the faculty scapegoat tree
                break;
            }
            case 9:{//case 9 changes a student's advisor given the student ID and the new faculty ID
                int sid;
                std::cout << "Enter the student's ID: ";//the student's ID is prompted for and an input is taken
                std::cin >> sid;
                if(std::cin.fail()){//error handling to catch invalid inputs
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid Input - Type a number for the student's ID" << endl;
                    continue;
                }

                Student s = Student();
                s.setID(sid);

                if(studentTree->contains(s)){//contains method to see if the student scapegoat tree contains the student
                    s = studentTree->find(s);
                }else{
                    std::cout << "Could not find student" << std::endl;//if the student is not found, a message is outputted
                    break;
                }

                int fid;
                std::cout << "Enter the faculty's ID: ";//faculty ID is prompted for and an input is taken
                std::cin >> fid;
                if(std::cin.fail()){//error handling to catch invalid inputs
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid Input - Type a number for the faculty's ID" << endl;
                    continue;
                }

                int tempFID = s.getFID();
                Faculty f = Faculty();
                if(tempFID != 0){//if the faculty ID is not 0, the student is removed from the original faculty advisees ID list
                    f.setID(tempFID);
                    facultyTree->find(f).removeStudent(sid);
                }
                
                
                Faculty newFaculty = Faculty();
                newFaculty.setID(fid);
                if(!facultyTree->contains(newFaculty)){//contains method to see if the faculty tree contains the new faculty member
                    std::cout << "Could not find faculty" << endl;//if the faculty member is not found, a message is outputted
                    break;
                }
                
                studentTree->find(s).setFID(fid);
                f.setID(fid);

                facultyTree->find(f).addStudent(sid);//the student is added to the new faculty member's advisees ID list
                break;
            }
            case 10:{//case 10 removes an advisee from a faculty member given the IDs
                int sid;
                std::cout << "Enter the student's ID: ";//student ID is prompted and an input is taken
                std::cin >> sid;
                if(std::cin.fail()){//error handling to catch invalid inputs
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid Input - Type a number for the student's ID" << endl;
                    continue;
                }

                Student s = Student();
                s.setID(sid);
                if(studentTree->contains(s)){//contains method to see if the student is in the student scapegoat tree
                    s = studentTree->find(s);
                }else{
                    std::cout << "Could not find student" << std::endl;//if the student is not in the student scapegoat tree, a message is outputted
                    break;
                }


                int fid;
                std::cout << "Enter the faculty's ID: ";//faculty ID is prompted and an input is taken
                std::cin >> fid;
                if(std::cin.fail()){//error handling to catch invalid inputs
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid Input - Type a number for the faculty's ID" << endl;
                    continue;
                }

                studentTree->find(s).setFID(0);

                Faculty f = Faculty();
                f.setID(fid);
                if(facultyTree->contains(f)){//contains method to see if the faculty is in the faculty tree
                    f = facultyTree->find(f);
                }else{
                    std::cout << "Could not find faculty" << std::endl;//if the faculty is not in the faculty scapegoat tree, a message is outputted
                    break;
                }

                facultyTree->find(f).removeStudent(sid);//the student is removed from the faculty's advisees ID list
                s = studentTree->find(s);
                f = facultyTree->find(f);
                // std::cout << s << "\n" << f << std::endl;//the student and faculty information is printed
                break;
            }
            case 11:{//case 11 ends the prompting of the user by ending the while loop and outputting the information to an output text file
                exit = true;//sets the boolean variable to tree, ending the while loop
                ofstream outFile;
                outFile.open("runLog.txt");//opens the output file
                studentTree->logTree(outFile);//logTree method logs the student scapegoat tree information and outputs it to an output file
                facultyTree->logTree(outFile);//logTree method logs the faculty scapegoat tree information and outputs it to an output file
                outFile.close();//closes the output file
                break;
            }
            default://default error handling to catch invalid inputs
                std::cout << "Invalid Input - Type a number between 1 and 11 to perform a command" << endl;
                choice = 0;
                continue;
        }
    }
}