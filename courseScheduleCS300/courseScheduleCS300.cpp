// courseScheduleCS300.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

struct Course {
    string courseId;
    string courseName;
    vector<string> coursePrerequisite;
};

static int loadCourses(vector<Course>& courses, const string& userInputFileName) {
    //opens the file using ifstream
    //string fileName = "CS 300 ABCU_Advising_Program_Input.csv";
    ifstream file(userInputFileName);
    //error if file fails to open
    if (file.fail()) {
        cerr << "File failed to open." << endl;
        return 1;
    }

    string line; 

    while (getline(file, line)) {
        istringstream stream(line);
        vector<string> tokens;
        string token;
        //parses the lines splits "," and stores in token
        while (getline(stream, token, ',')) {
            tokens.push_back(token);
        }
        // if line in file has less than 2 tokens its skipped 
        if (tokens.size() < 2) {
            continue;
        }
        //assigns token
        Course course;
        course.courseId = tokens[0];
        course.courseName = tokens[1];
        // if the course has 2 or more prerequisites its pushed into token 2
        for (size_t i = 2; i < tokens.size(); ++i) {
            course.coursePrerequisite.push_back(tokens[i]);
        }

        courses.push_back(course);
    }
    // sorts the courses alphanumerically by courseId
    sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {
        return a.courseId < b.courseId;
        });
    return 0;
}
//prints a sample schedule
void printAllCourses(const vector<Course>&courses) {
    cout << "Here is a sample schedule: " << endl;
    cout << endl;
    for (const auto& course : courses) {
        cout << course.courseId << ", " << course.courseName << endl;

    }
}
static void printCourseInfo(const vector<Course>& courses, const string& courseNumber) {
    
    for (const auto& course : courses) {
        if (course.courseId == courseNumber) {
            cout << course.courseId << ", " << course.courseName << endl;
            cout << "Prerequisites: ";
            if (course.coursePrerequisite.empty()) {
                cout << "None";
            }
            else {
                for (size_t i = 0; i < course.coursePrerequisite.size(); ++i) {
                    cout << course.coursePrerequisite[i];
                    if (i < course.coursePrerequisite.size() - 1) {
                        cout << ", ";
                    }
                }
            }
            cout << endl;
            return;
        }
    }
    cout << "Course not found." << endl;
}

//prints menu
void printMenu() {
    cout << "Welcome to the course planner." << endl;
    cout << "1. Load courses into data structure." << endl;
    cout << "2. Print course list." << endl;
    cout << "3. Search and print a course." << endl;
    cout << "9. Exit." << endl;
}
//main funtion with a switch case
int main() {
    int option = 0;
    vector<Course> courses;

    while (option != 9) {
        printMenu();
        cin >> option;
        cin.clear();
        cin.ignore();
        
        switch (option) {
            case 1: {
                string userInputFileName;
                cout << "Enter file you would like to load: ";
                getline(cin, userInputFileName); //gets input and passes it to userInputFileName
                if (loadCourses(courses, userInputFileName) != 0) { 
                    cerr << "Failed to load that file, check your input." << endl;
                }
               break;
            }

            case 2: {
                printAllCourses(courses);
                break;
            }

            case 3: {
                string courseNumber;
                cout << "Enter course number: ";
                cin >> courseNumber;
                transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper); //upper case the input
                printCourseInfo(courses, courseNumber);
                break;
            }
            
            case 9: {
                cout << "Exiting.";
                break;
            }
            
            default: {
                cout << "Invalid selection, please try again." << endl;
                break;
            }
        }
    }

}
/*
bugs to fix

when 1 is pressed more than once the data is duplicated
option 3 can only works with lower case input, when upper case is entered infite loop happens
when cin ignore is executed it prints error duplicates 
*/


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
