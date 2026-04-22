#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    // Constructor (Assignment in body form)
    Person(string n = "", int a = 0){
        name = n;
        age = a;
    }
    // Destructor (with tracing output)
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
    // Constructor (Assignment in body form)
    Student(string id = "", string n = "", int a = 0, string d = "", string c = "", double f = 0.0)
        : Person(n, a) // Base class initialized in list, members assigned in body
    {
        studentID = id;
        department = d;
        course = c;
        fee = f;
    }

    // Destructor (with tracing output)
    ~Student() override {
        cout << "Student " << name << " deleted.\n";
    }

    string getID() const { return studentID; }
    string getDept() const { return department; }
    string getCourse() const { return course; }
    double getFee() const { return fee; }

    void displayInfo() const override {
        cout << "\n--- Student Info ---\n";
        cout << "ID: " << studentID << "\nName: " << name << "\nAge: " << age
             << "\nDepartment: " << department << "\nCourse: " << course
             << "\nFee: " << fee << "\n";
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
    // Constructor (Assignment in body form)
    Teacher(string id = "", string n = "", int a = 0, string d = "", int exp = 0)
        : Person(n, a) // Base class initialized in list, members assigned in body
    {
        teacherID = id;
        department = d;
        experience = exp;
    }

    // Destructor (with tracing output)
    ~Teacher() override {
        cout << "Teacher " << name << " deleted.\n";
    }

    void displayInfo() const override {
        cout << "\n--- Teacher Info ---\n";
        cout << "ID: " << teacherID << "\nName: " << name << "\nAge: " << age
             << "\nDepartment: " << department << "\nExperience: " << experience << " years\n";
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
    // Constructor (Assignment in body form)
    Department(string id = "", string name = "", string h = "")
    {
        deptID = id;
        deptName = name;
        hod = h;
    }

    // Destructor (Simple empty body, as no tracing was present initially)
    ~Department() {}

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
    // Constructor (Assignment in body form)
    Course(string c = "", string n = "", string d = "", double f = 0.0)
    {
        code = c;
        name = n;
        department = d;
        fee = f;
    }

    // Destructor (Simple empty body, as no tracing was present initially)
    ~Course() {}

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

public:
    // Constructor (with tracing output)
    CollegeManagement() { cout << "College Management System initialized.\n"; }

    // Destructor (with tracing output)
    ~CollegeManagement() { cout << "System shutting down.\n"; }

    void addStudent() {
        try {
            string id, name, dept, course;
            int age;
            double fee;

            cout << "\nEnter Student ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            cin.ignore();
            cout << "Enter Department: ";
            getline(cin, dept);
            cout << "Enter Course: ";
            getline(cin, course);
            cout << "Enter Fee: ";
            cin >> fee;

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
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            cin.ignore();
            cout << "Enter Department: ";
            getline(cin, dept);
            cout << "Enter Experience (years): ";
            cin >> exp;

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
            cin.ignore();
            cout << "Enter Department Name: ";
            getline(cin, name);
            cout << "Enter HOD Name: ";
            getline(cin, hod);

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
            cin.ignore();
            cout << "Enter Course Name: ";
            getline(cin, name);
            cout << "Enter Department: ";
            getline(cin, dept);
            cout << "Enter Fee: ";
            cin >> fee;

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
            cout << "\n--- STUDENT MENU ---\n1. Add Student\n2. Back\nChoice: ";
            cin >> ch;
            switch (ch) {
                case 1: addStudent(); break;
                case 2: return;
            }
        } while (ch != 2);
    }

    void teacherMenu() {
        int ch;
        do {
            cout << "\n--- TEACHER MENU ---\n1. Add Teacher\n2. Back\nChoice: ";
            cin >> ch;
            switch (ch) {
                case 1: addTeacher(); break;
                case 2: return;
            }
        } while (ch != 2);
    }

    void courseMenu() {
        int ch;
        do {
            cout << "\n--- COURSE MENU ---\n1. Add Course\n2. Back\nChoice: ";
            cin >> ch;
            switch (ch) {
                case 1: addCourse(); break;
                case 2: return;
            }
        } while (ch != 2);
    }

    void departmentMenu() {
        int ch;
        do {
            cout << "\n--- DEPARTMENT MENU ---\n1. Add Department\n2. Back\nChoice: ";
            cin >> ch;
            switch (ch) {
                case 1: addDepartment(); break;
                case 2: return;
            }
        } while (ch != 2);
    }

    void mainMenu() {
        int choice;
        do {
            system("CLS");
            cout << "\n===== COLLEGE MANAGEMENT SYSTEM =====\n";
            cout << "1. Department Management\n";
            cout << "2. Course Management\n";
            cout << "3. Student Management\n";
            cout << "4. Teacher Management\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: departmentMenu(); break;
                case 2: courseMenu(); break;
                case 3: studentMenu(); break;
                case 4: teacherMenu(); break;
                case 5: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice!\n";
            }
        } while (choice != 5);
    }
};

int main() {
    CollegeManagement cms;
    cms.mainMenu();
    return 0;
}