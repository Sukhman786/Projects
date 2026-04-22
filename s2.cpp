#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdexcept>
#include <limits>
#include <conio.h>
#include <windows.h>
using namespace std;

void clearScreen() {
    system("cls");
}

void pressEnterToContinue() {
    cout << "\n\nPress Enter to continue...";
    _getch();
}

void showLoading() {
    cout << "\n\nLoading data";
    for (int i = 0; i < 3; ++i) {
        Sleep(300);
        cout << ".";
    }
    cout << "\n";
}

class Person {
protected:
    string name;
    int age;

public:
    Person(string n = "", int a = 0){
        name = n;
        age = a;
    }
    virtual ~Person(){
        cout << "Destructor called for " << name << endl;
    }

    void setName(string n){
        name = n;
    }
    string getName() const{
        return name;
    }

    void setAge(int a){
        age = a;
    }
    int getAge() const{
        return age;
    }

    virtual void displayInfo() const = 0;
};

class Student : public Person {
private:
    string studentID;
    string department;
    string course;
    double fee;

public:
    Student(string id = "", string n = "", int a = 0, string d = "", string c = "", double f = 0.0)
        : Person(n, a){
            studentID=id;
            department=d;
            course=c;
            fee=f;
        }
    ~Student() override {
        cout << "Student " << name << " deleted.\n";
    }

    string getID() const { return studentID; }
    string getDept() const { return department; }
    string getCourse() const { return course; }
    double getFee() const { return fee; }

    void displayInfo() const override {
        cout << left;
        cout << "| " << setw(10) << studentID
             << "| " << setw(20) << name
             << "| " << setw(5) << age
             << "| " << setw(15) << department
             << "| " << setw(15) << course
             << "| " << fixed << setprecision(2) << setw(10) << fee << " |" << endl;
    }

    void saveToFile() const {
        ofstream fout("students.dat", ios::app);
        if (!fout.is_open())
            throw runtime_error("Error opening students.dat file!");
        fout << studentID << "|" << name << "|" << age << "|" << department << "|" << course << "|" << fee << "\n";
        fout.close();
    }
};

class Teacher : public Person {
private:
    string teacherID;
    string department;
    int experience;

public:
    Teacher(string id = "", string n = "", int a = 0, string d = "", int exp = 0)
        : Person(n, a){
            teacherID = id;
            department=d;
            experience=exp;
        }
    ~Teacher() override { cout << "Teacher " << name << " deleted.\n"; }

    string getID() const { return teacherID; }
    
    void displayInfo() const override {
        cout << left;
        cout << "| " << setw(10) << teacherID
             << "| " << setw(20) << name
             << "| " << setw(5) << age
             << "| " << setw(15) << department
             << "| " << setw(15) << experience << " |" << endl;
    }

    void saveToFile() const {
        ofstream fout("teachers.dat", ios::app);
        if (!fout)
            throw runtime_error("Error opening teachers.dat file!");
        fout << teacherID << "|" << name << "|" << age << "|" << department << "|" << experience << "\n";
        fout.close();
    }
};

class Department {
private:
    string deptID, deptName, hod;

public:
    Department(string id = "", string name = "", string h = ""){
        deptID=id;
        deptName=name;
        hod=h;
    }

    void display() const {
        cout << left << setw(10) << deptID << setw(20) << deptName << setw(20) << hod << endl;
    }

    void saveToFile() const {
        ofstream fout("departments.dat", ios::app);
        if (!fout)
            throw runtime_error("Error opening departments.dat!");
        fout << deptID << "|" << deptName << "|" << hod << "\n";
        fout.close();
    }
};

class Course {
private:
    string code, name, department;
    double fee;

public:
    Course(string c = "", string n = "", string d = "", double f = 0.0){
        code=c;
        name=n;
        department=d;
        fee=f;
    }

    void display() const {
        cout << left << setw(10) << code << setw(20) << name << setw(20) << department
             << "₹" << fixed << setprecision(2) << fee << endl;
    }

    void saveToFile() const {
        ofstream fout("courses.dat", ios::app);
        if (!fout)
            throw runtime_error("Error opening courses.dat!");
        fout << code << "|" << name << "|" << department << "|" << fee << "\n";
        fout.close();
    }
};

class CollegeManagement {
private:
    vector<Student> students;
    vector<Teacher> teachers;
    vector<Course> courses;
    vector<Department> departments;

    string getValidInput(string prompt) {
        string input;
        while (true) {
            cout << prompt;
            getline(cin, input);
            if (input.empty()) {
                cout << "Input cannot be empty. Please try again.\n";
            } else {
                return input;
            }
        }
    }

public:
    CollegeManagement() { 
        showLoading();
        cout << "College Management System initialized.\n"; 
    }
    ~CollegeManagement() { cout << "System shutting down.\n"; }

    void showFrontPage() {
        clearScreen();
        cout << "====================================================\n";
        cout << "|                                                  |\n";
        cout << "|      WELCOME TO THE COLLEGE MANAGEMENT SYSTEM    |\n";
        cout << "|                                                  |\n";
        cout << "====================================================\n";
        pressEnterToContinue();
    }
    
    void displayAllStudents() {
        clearScreen();
        cout << "--- All Students ---\n\n";
        
        if (students.empty()) {
            cout << "No student records found.\n";
            return;
        }

        cout << "----------------------------------------------------------------------------------\n";
        cout << left;
        cout << "| " << setw(10) << "ID"
             << "| " << setw(20) << "Name"
             << "| " << setw(5) << "Age"
             << "| " << setw(15) << "Department"
             << "| " << setw(15) << "Course"
             << "| " << setw(10) << "Fee" << " |" << endl;
        cout << "----------------------------------------------------------------------------------\n";

        for (const auto& s : students) {
            s.displayInfo();
        }
        cout << "----------------------------------------------------------------------------------\n";
    }

    void displayAllTeachers() {
        clearScreen();
        cout << "--- All Teachers ---\n\n";
        
        if (teachers.empty()) {
            cout << "No teacher records found.\n";
            return;
        }

        cout << "------------------------------------------------------------------\n";
        cout << left;
        cout << "| " << setw(10) << "ID"
             << "| " << setw(20) << "Name"
             << "| " << setw(5) << "Age"
             << "| " << setw(15) << "Department"
             << "| " << setw(15) << "Experience" << " |" << endl;
        cout << "------------------------------------------------------------------\n";

        for (const auto& t : teachers) {
            t.displayInfo();
        }
        cout << "------------------------------------------------------------------\n";
    }

    void displayAllCourses() {
        clearScreen();
        cout << "--- All Courses ---\n\n";
        
        if (courses.empty()) {
            cout << "No course records found.\n";
            return;
        }

        cout << left << setw(10) << "Code" << setw(20) << "Name" << setw(20) << "Department" << "Fee" << endl;
        cout << "----------------------------------------------------------\n";

        for (const auto& c : courses) {
            c.display();
        }
    }

    void displayAllDepartments() {
        clearScreen();
        cout << "--- All Departments ---\n\n";

        if (departments.empty()) {
            cout << "No department records found.\n";
            return;
        }
        
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(20) << "HOD" << endl;
        cout << "----------------------------------------------------------\n";

        for (const auto& d : departments) {
            d.display();
        }
    }

    void addStudent() {
        try {
            string id, name, dept, course;
            int age;
            double fee;

            cout << "\nEnter Student ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            name = getValidInput("Enter Name: ");
            cout << "Enter Age: ";
            cin >> age;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            dept = getValidInput("Enter Department: ");
            course = getValidInput("Enter Course: ");
            cout << "Enter Fee: ";
            cin >> fee;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (fee < 0) throw invalid_argument("Fee cannot be negative!");

            Student s(id, name, age, dept, course, fee);
            students.push_back(s);
            s.saveToFile();
            cout << "\nStudent added successfully!\n";
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void addTeacher() {
        try {
            string id, name, dept;
            int age, exp;
            cout << "\nEnter Teacher ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            name = getValidInput("Enter Name: ");
            cout << "Enter Age: ";
            cin >> age;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            dept = getValidInput("Enter Department: ");
            cout << "Enter Experience (years): ";
            cin >> exp;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            Teacher t(id, name, age, dept, exp);
            teachers.push_back(t);
            t.saveToFile();
            cout << "\nTeacher added successfully!\n";
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void addDepartment() {
        try {
            if (departments.size() >= 3)
                throw runtime_error("Cannot add more than 3 departments!");
            string id, name, hod;
            cout << "\nEnter Department ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            name = getValidInput("Enter Department Name: ");
            hod = getValidInput("Enter HOD Name: ");

            Department d(id, name, hod);
            departments.push_back(d);
            d.saveToFile();
            cout << "\nDepartment added successfully!\n";
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void addCourse() {
        try {
            string code, name, dept;
            double fee;
            cout << "\nEnter Course Code: ";
            cin >> code;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            name = getValidInput("Enter Course Name: ");
            dept = getValidInput("Enter Department: ");
            cout << "Enter Fee: ";
            cin >> fee;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (fee < 0)
                throw invalid_argument("Fee cannot be negative!");

            Course c(code, name, dept, fee);
            courses.push_back(c);
            c.saveToFile();
            cout << "\nCourse added successfully!\n";
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void studentMenu() {
        int ch;
        do {
            clearScreen();
            cout << "\n--- STUDENT MENU ---\n1. Add Student\n2. View All Students\n3. Back\nChoice: ";
            cin >> ch;
            if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); ch = -1; } 
            else { cin.ignore(numeric_limits<streamsize>::max(), '\n'); }

            switch (ch) {
                case 1: addStudent(); pressEnterToContinue(); break;
                case 2: displayAllStudents(); pressEnterToContinue(); break;
                case 3: return;
                default: cout << "Invalid choice!\n"; pressEnterToContinue();
            }
        } while (ch != 3);
    }

    void teacherMenu() {
        int ch;
        do {
            clearScreen();
            cout << "\n--- TEACHER MENU ---\n1. Add Teacher\n2. View All Teachers\n3. Back\nChoice: ";
            cin >> ch;
            if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); ch = -1; }
            else { cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
            
            switch (ch) {
                case 1: addTeacher(); pressEnterToContinue(); break;
                case 2: displayAllTeachers(); pressEnterToContinue(); break;
                case 3: return;
                default: cout << "Invalid choice!\n"; pressEnterToContinue();
            }
        } while (ch != 3);
    }

    void courseMenu() {
        int ch;
        do {
            clearScreen();
            cout << "\n--- COURSE MENU ---\n1. Add Course\n2. View All Courses\n3. Back\nChoice: ";
            cin >> ch;
            if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); ch = -1; }
            else { cin.ignore(numeric_limits<streamsize>::max(), '\n'); }

            switch (ch) {
                case 1: addCourse(); pressEnterToContinue(); break;
                case 2: displayAllCourses(); pressEnterToContinue(); break;
                case 3: return;
                default: cout << "Invalid choice!\n"; pressEnterToContinue();
            }
        } while (ch != 3);
    }

    void departmentMenu() {
        int ch;
        do {
            clearScreen();
            cout << "\n--- DEPARTMENT MENU ---\n1. Add Department\n2. View All Departments\n3. Back\nChoice: ";
            cin >> ch;
            if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); ch = -1; }
            else { cin.ignore(numeric_limits<streamsize>::max(), '\n'); }

            switch (ch) {
                case 1: addDepartment(); pressEnterToContinue(); break;
                case 2: displayAllDepartments(); pressEnterToContinue(); break;
                case 3: return;
                default: cout << "Invalid choice!\n"; pressEnterToContinue();
            }
        } while (ch != 3);
    }

    void mainMenu() {
        int choice;
        do {
            clearScreen();
            cout << "\n===== COLLEGE MANAGEMENT SYSTEM =====\n";
            cout << "1. Department Management\n";
            cout << "2. Course Management\n";
            cout << "3. Student Management\n";
            cout << "4. Teacher Management\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            
            cin >> choice;
            if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); choice = -1; }
            else { cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
            
            switch (choice) {
                case 1: departmentMenu(); break;
                case 2: courseMenu(); break;
                case 3: studentMenu(); break;
                case 4: teacherMenu(); break;
                case 5: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice!\n"; pressEnterToContinue();
            }
        } while (choice != 5);
    }
};

int main() {
    CollegeManagement cms;
    cms.showFrontPage();
    cms.mainMenu();
    return 0;
}