#include <iostream>  
#include <fstream>   
#include <string>    
#include <vector>    
#include <iomanip>   
#include <conio.h>   
#include <windows.h> 
#include <limits>    

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
        Sleep(300); // Pause for 3 seconds
        cout << ".";
    }
    cout << "\n";
}

class Person {
protected:
    string id;
    string name;

public:
    Person() : id(""), name("") {}

    Person(string id, string name) : id(id), name(name) {}

    virtual ~Person() {}

    void setID(string id) { this->id = id; }
    string getID() { return id; }
    void setName(string name) { this->name = name; }
    string getName() { return name; }
    virtual void displayDetails() = 0;
    virtual void writeData(ofstream& outFile) = 0;
    virtual void readData(ifstream& inFile) = 0;
};

class Student : public Person {
private:
    string course;
    string department;

public:
    Student() : Person(), course(""), department("") {}
    Student(string id, string name, string course, string dept)
        : Person(id, name), course(course), department(dept) {}

    void setCourse(string c) { course = c; }
    string getCourse() { return course; }
    void setDepartment(string d) { department = d; }
    string getDepartment() { return department; }

    void displayDetails() override {
        cout << left; // Left-align text
        cout << "| " << setw(10) << id
             << "| " << setw(20) << name
             << "| " << setw(15) << department
             << "| " << setw(15) << course << " |" << endl;
    }
    void writeData(ofstream& outFile) override {
        outFile << id << endl;
        outFile << name << endl;
        outFile << course << endl;
        outFile << department << endl;
    }
    void readData(ifstream& inFile) override {
        getline(inFile, id);
        getline(inFile, name);
        getline(inFile, course);
        getline(inFile, department);
    }
};

class Teacher : public Person {
private:
    string department;
    string specialization;

public:
    Teacher() : Person(), department(""), specialization("") {}
    Teacher(string id, string name, string dept, string spec)
        : Person(id, name), department(dept), specialization(spec) {}

    void setDepartment(string d) { department = d; }
    string getDepartment() { return department; }
    void setSpecialization(string s) { specialization = s; }
    string getSpecialization() { return specialization; }

    void displayDetails() override {
        cout << left; // Left-align text
        cout << "| " << setw(10) << id
             << "| " << setw(20) << name
             << "| " << setw(15) << department
             << "| " << setw(15) << specialization << " |" << endl;
    }

    void writeData(ofstream& outFile) override {
        outFile << id << endl;
        outFile << name << endl;
        outFile << department << endl;
        outFile << specialization << endl;
    }

    void readData(ifstream& inFile) override {
        getline(inFile, id);
        getline(inFile, name);
        getline(inFile, department);
        getline(inFile, specialization);
    }
};

class College {
private:
    vector<Person*> students;
    vector<Person*> teachers;

    Person* findPerson(vector<Person*>& list, string id) {
        for (Person* p : list) {
            if (p->getID() == id) {
                return p;
            }
        }
        return nullptr;
    }

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

    void loadStudents() {
        ifstream file("students.txt");
        if (!file.is_open()) {
            cout << "Warning: 'students.txt' not found. Will be created on exit.\n";
            return; // File doesn't exist, just return
        }
    
        if (file.peek() == ifstream::traits_type::eof()) {
            file.close();
            return; // File is empty, do nothing
        }

        while (!file.eof()) {
            Student* newStudent = new Student();
            newStudent->readData(file);

            if (file.eof()) {
                delete newStudent; // Clean up the allocated memory
                break;
            }

            students.push_back(newStudent);
        }
        file.close();
    }

    void loadTeachers() {
        ifstream file("teachers.txt");
        if (!file.is_open()) {
            cout << "Warning: 'teachers.txt' not found. Will be created on exit.\n";
            return;
        }

        if (file.peek() == ifstream::traits_type::eof()) {
            file.close();
            return; 
        }

        while (!file.eof()) {
            Teacher* newTeacher = new Teacher();
            newTeacher->readData(file);

            if (file.eof()) {
                delete newTeacher;
                break;
            }

            teachers.push_back(newTeacher);
        }
        file.close();
    }

    void saveStudents() {
        ofstream file("students.txt");
        if (!file.is_open()) {
            cout << "ERROR: Could not save student data!\n";
            return;
        }
        for (Person* p : students) {
            p->writeData(file); // Polymorphism! Calls Student's writeData
        }
        file.close();
    }

    void saveTeachers() {
        ofstream file("teachers.txt");
        if (!file.is_open()) {
            cout << "ERROR: Could not save teacher data!\n";
            return;
        }
        for (Person* p : teachers) {
            p->writeData(file); // Polymorphism! Calls Teacher's writeData
        }
        file.close();
    }

public:
    College() {
        showLoading();
        loadStudents();
        loadTeachers();
    }

    ~College() {
        cout << "\nSaving data before exiting...\n";
        saveStudents();
        saveTeachers();

        for (Person* p : students) {
            delete p;
        }
        for (Person* p : teachers) {
            delete p;
        }
        cout << "Data saved. Goodbye!\n";
        Sleep(1000);
    }

    // --- Main Feature Functions ---

    void showFrontPage() {
        clearScreen();
        cout << "====================================================\n";
        cout << "|                                                  |\n";
        cout << "|      WELCOME TO THE COLLEGE MANAGEMENT SYSTEM    |\n";
        cout << "|                                                  |\n";
        cout << "====================================================\n";
        cout << "\n\nThis project is a simple demonstration of OOP in C++.\n";
        cout << "It manages student and teacher records and saves them to files.\n";
        pressEnterToContinue();
    }

    void displayDepartments() {
        clearScreen();
        cout << "--- Departments and Courses ---\n\n";

        cout << "1. Computer Science (CS)\n";
        cout << "   - Courses: B.Tech (CS), M.Tech (CS)\n";
        cout << "   - Fees: B.Tech - 100,000 /yr, M.Tech - 120,000 /yr\n\n";

        cout << "2. Mechanical Engineering (ME)\n";
        cout << "   - Courses: B.Tech (ME), M.Tech (ME)\n";
        cout << "   - Fees: B.Tech - 90,000 /yr, M.Tech - 110,000 /yr\n\n";

        cout << "3. Electronics & Communication (ECE)\n";
        cout << "   - Courses: B.Tech (ECE), M.Tech (ECE)\n";
        cout << "   - Fees: B.Tech - 95,000 /yr, M.Tech - 115,000 /yr\n\n";
    }

    // --- Student Management ---

    void addStudent() {
        clearScreen();
        cout << "--- Add New Student ---\n";
        string id = getValidInput("Enter Student ID: ");

        // Error Handling: Check if ID already exists
        if (findPerson(students, id) != nullptr) {
            cout << "Error: A student with this ID already exists.\n";
            return;
        }

        string name = getValidInput("Enter Name: ");
        string course = getValidInput("Enter Course (e.g., B.Tech CS): ");
        string dept = getValidInput("Enter Department (e.g., CS): ");

        // Create a new Student object on the heap (using 'new')
        Student* newStudent = new Student(id, name, course, dept);
        students.push_back(newStudent); // Add the pointer to our vector

        cout << "\nStudent added successfully!\n";
    }

    void displayAllStudents() {
        clearScreen();
        cout << "--- All Students ---\n\n";
        
        // Check if there are any students
        if (students.empty()) {
            cout << "No student records found.\n";
            return;
        }

        // Print table header
        cout << "------------------------------------------------------------------\n";
        cout << left;
        cout << "| " << setw(10) << "ID"
             << "| " << setw(20) << "Name"
             << "| " << setw(15) << "Department"
             << "| " << setw(15) << "Course" << " |" << endl;
        cout << "------------------------------------------------------------------\n";

        for (Person* p : students) {
            p->displayDetails();
        }
        cout << "------------------------------------------------------------------\n";
    }

    void editStudent() {
        clearScreen();
        cout << "--- Edit Student Details ---\n";
        string id = getValidInput("Enter Student ID to edit: ");

        Person* p = findPerson(students, id);
        if (p == nullptr) {
            cout << "Error: Student not found.\n";
            return;
        }

        Student* s = static_cast<Student*>(p);

        cout << "\nFound Student: " << s->getName() << ". Enter new details (leave blank to keep current):\n";
        
        string newName, newCourse, newDept;
        
        cout << "Enter new name (" << s->getName() << "): ";
        getline(cin, newName);
        cout << "Enter new course (" << s->getCourse() << "): ";
        getline(cin, newCourse);
        cout << "Enter new department (" << s->getDepartment() << "): ";
        getline(cin, newDept);

        // Update details only if new input was given
        if (!newName.empty()) s->setName(newName);
        if (!newCourse.empty()) s->setCourse(newCourse);
        if (!newDept.empty()) s->setDepartment(newDept);

        cout << "\nStudent details updated successfully!\n";
    }

    void deleteStudent() {
        clearScreen();
        cout << "--- Delete Student Record ---\n";
        string id = getValidInput("Enter Student ID to delete: ");

        for (int i = 0; i < students.size(); ++i) {
            if (students[i]->getID() == id) {
                
                cout << "Found Student: " << students[i]->getName() << endl;
                cout << "Are you sure you want to delete this record? (y/n): ";
                char choice;
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer

                if (choice == 'y' || choice == 'Y') {
                    delete students[i]; // IMPORTANT: Free the memory
                    students.erase(students.begin() + i); // Remove pointer from vector
                    cout << "Student record deleted successfully.\n";
                } else {
                    cout << "Deletion cancelled.\n";
                }
                return;
            }
        }
        cout << "Error: Student not found.\n";
    }

    // --- Teacher Management ---
    void addTeacher() {
        clearScreen();
        cout << "--- Add New Teacher ---\n";
        string id = getValidInput("Enter Teacher ID: ");

        if (findPerson(teachers, id) != nullptr) {
            cout << "Error: A teacher with this ID already exists.\n";
            return;
        }

        string name = getValidInput("Enter Name: ");
        string dept = getValidInput("Enter Department (e.g., CS): ");
        string spec = getValidInput("Enter Specialization (e.g., AI): ");

        Teacher* newTeacher = new Teacher(id, name, dept, spec);
        teachers.push_back(newTeacher);

        cout << "\nTeacher added successfully!\n";
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
             << "| " << setw(15) << "Department"
             << "| " << setw(15) << "Specialization" << " |" << endl;
        cout << "------------------------------------------------------------------\n";

        for (Person* p : teachers) {
            p->displayDetails();
        }
        cout << "------------------------------------------------------------------\n";
    }

    void editTeacher() {
        clearScreen();
        cout << "--- Edit Teacher Details ---\n";
        string id = getValidInput("Enter Teacher ID to edit: ");

        Person* p = findPerson(teachers, id);
        if (p == nullptr) {
            cout << "Error: Teacher not found.\n";
            return;
        }

        Teacher* t = static_cast<Teacher*>(p);

        cout << "\nFound Teacher: " << t->getName() << ". Enter new details (leave blank to keep current):\n";
        
        string newName, newSpec, newDept;
        
        cout << "Enter new name (" << t->getName() << "): ";
        getline(cin, newName);
        cout << "Enter new department (" << t->getDepartment() << "): ";
        getline(cin, newDept);
        cout << "Enter new specialization (" << t->getSpecialization() << "): ";
        getline(cin, newSpec);

        if (!newName.empty()) t->setName(newName);
        if (!newDept.empty()) t->setDepartment(newDept);
        if (!newSpec.empty()) t->setSpecialization(newSpec);

        cout << "\nTeacher details updated successfully!\n";
    }

    void deleteTeacher() {
        clearScreen();
        cout << "--- Delete Teacher Record ---\n";
        string id = getValidInput("Enter Teacher ID to delete: ");

        for (int i = 0; i < teachers.size(); ++i) {
            if (teachers[i]->getID() == id) {
                
                cout << "Found Teacher: " << teachers[i]->getName() << endl;
                cout << "Are you sure you want to delete this record? (y/n): ";
                char choice;
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (choice == 'y' || choice == 'Y') {
                    delete teachers[i];
                    teachers.erase(teachers.begin() + i);
                    cout << "Teacher record deleted successfully.\n";
                } else {
                    cout << "Deletion cancelled.\n";
                }
                return;
            }
        }
        cout << "Error: Teacher not found.\n";
    }
}; 
// --- Menu Functions ---

void studentMenu(College& college) {
    int choice;
    while (true) {
        clearScreen();
        cout << "--- Student Menu ---\n";
        cout << "1. Add New Student\n";
        cout << "2. View All Students\n";
        cout << "3. Edit Student Details\n";
        cout << "4. Delete Student\n";
        cout << "0. Back to Main Menu\n";
        cout << "\nEnter your choice: ";
        
        cin >> choice;
        // Basic input validation
        if (cin.fail()) {
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            choice = -1; // invalid choice
        } else {
             cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard rest of line
        }

        switch (choice) {
            case 1: college.addStudent(); break;
            case 2: college.displayAllStudents(); break;
            case 3: college.editStudent(); break;
            case 4: college.deleteStudent(); break;
            case 0: return; // Go back
            default: cout << "Invalid choice. Please try again.\n";
        }
        if (choice != 0) {
            pressEnterToContinue();
        }
    }
}

void teacherMenu(College& college) {
    int choice;
    while (true) {
        clearScreen();
        cout << "--- Teacher Menu ---\n";
        cout << "1. Add New Teacher\n";
        cout << "2. View All Teachers\n";
        cout << "3. Edit Teacher Details\n";
        cout << "4. Delete Teacher\n";
        cout << "0. Back to Main Menu\n";
        cout << "\nEnter your choice: ";
        
        cin >> choice;
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        } else {
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1: college.addTeacher(); break;
            case 2: college.displayAllTeachers(); break;
            case 3: college.editTeacher(); break;
            case 4: college.deleteTeacher(); break;
            case 0: return; // Go back
            default: cout << "Invalid choice. Please try again.\n";
        }
        if (choice != 0) {
            pressEnterToContinue();
        }
    }
}


// --- Main Function ---
int main() {
    College myCollege;

    myCollege.showFrontPage();

    int choice;
    while (true) {
        clearScreen();
        cout << "====================================\n";
        cout << "|        MAIN MENU                 |\n";
        cout << "====================================\n";
        cout << "1. Student Management\n";
        cout << "2. Teacher Management\n";
        cout << "3. View Departments & Fees\n";
        cout << "0. Exit Program\n";
        cout << "\nEnter your choice: ";

        cin >> choice;
        
        if (cin.fail()) {
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            choice = -1; // Set to an invalid choice
            
        } else {
            // Good practice: clear the input buffer after a successful cin >>
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }

        switch (choice) {
            case 1:
                studentMenu(myCollege);
                break;
            case 2:
                teacherMenu(myCollege);
                break;
            case 3:
                myCollege.displayDepartments();
                pressEnterToContinue();
                break;
            case 0:
                return 0;
            default:
                cout << "Invalid choice. Please press Enter to try again.\n";
                pressEnterToContinue();
        }
    }

    return 0; // Program should never reach here, but it's good practice
}