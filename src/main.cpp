#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <windows.h>
#include "include/Student.h"
#include "include/Course.h"
#include "include/GradeCalculator.h"
#include "include/ReportGenerator.h"
#include "include/FileManager.h"
#include "include/GradeObserver.h"

using namespace std;

// Global variables
vector<Student> students;
FileManager fileManager("data/students.csv");

// Function prototypes
void displayMainMenu();
void displayStudentMenu();
void displayCourseMenu();
void displayReportMenu();
void displaySettingsMenu();

void addStudent();
void updateStudent();
void deleteStudent();
void listStudents();
void viewStudentDetails();

void addCourseToStudent();
void updateCourseMarks();
void removeCourseFromStudent();
void viewCoursesOfStudent();

void generateReport();
void generateAllReports();

void uogCGPACalculator();

void clearScreen();
void pause();
void displayHeader(const string& title);

// ==================== MAIN FUNCTION ====================
int main() {
    SetConsoleOutputCP(65001);
    cout << string(100, '=') << endl;
    cout << "WELCOME TO STUDENT GRADE CALCULATOR" << endl;
    cout << "University of Gujrat - GPA Management System" << endl;
    cout << "Author [SYED NOKHAIZ AL HASSAN]" << endl;
    cout << "APP DEVELOPER | University of Gujrat" << endl;
    cout << string(100, '=') << endl;

    // Initialize notifier
    GradeChangeNotifier::getInstance()->subscribeLowGradeAlert();
    GradeChangeNotifier::getInstance()->subscribePerformanceLogger();

    // Load existing data
    students = fileManager.loadStudents();

    int choice;
    bool running = true;

    while (running) {
        displayMainMenu();
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                clearScreen();
                displayStudentMenu();
                break;
            case 2:
                clearScreen();
                displayCourseMenu();
                break;
            case 3:
                clearScreen();
                displayReportMenu();
                break;
            case 4:
                clearScreen();
                displaySettingsMenu();
                break;
            case 5:
                clearScreen();
                uogCGPACalculator();
                break;
            case 6:
                fileManager.saveStudents(students);
                cout << "\n✓ All changes saved successfully!" << endl;
                running = false;
                break;
            case 0:
                cout << "\n✓ Exiting application. Thank you!" << endl;
                running = false;
                break;
            default:
                cout << "\n✗ Invalid choice! Please try again." << endl;
        }
        if (running) pause();
    }

    return 0;
}

// ==================== MENU FUNCTIONS ====================
void displayMainMenu() {
    cout << "\n" << string(100, '=') << endl;
    cout << "MAIN MENU" << endl;
    cout << string(100, '=') << endl;
    cout << "1. Student Management" << endl;
    cout << "2. Course Management" << endl;
    cout << "3. Generate Reports" << endl;
    cout << "4. Settings & Utilities" << endl;
    cout << "5. UOG CGPA Calculator" << endl;
    cout << "6. Save & Exit" << endl;
    cout << "0. Exit Without Saving" << endl;
    cout << string(100, '=') << endl;
}

void displayStudentMenu() {
    displayHeader("STUDENT MANAGEMENT");
    int choice;
    bool inMenu = true;

    while (inMenu) {
        cout << "\n1. Add New Student" << endl;
        cout << "2. Update Student Info" << endl;
        cout << "3. View Student Details" << endl;
        cout << "4. List All Students" << endl;
        cout << "5. Delete Student" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << string(50, '-') << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: addStudent(); break;
            case 2: updateStudent(); break;
            case 3: viewStudentDetails(); break;
            case 4: listStudents(); break;
            case 5: deleteStudent(); break;
            case 0: inMenu = false; break;
            default: cout << "✗ Invalid choice!" << endl;
        }
    }
}

void displayCourseMenu() {
    displayHeader("COURSE MANAGEMENT");
    int choice;
    bool inMenu = true;

    while (inMenu) {
        cout << "\n1. Add Course to Student" << endl;
        cout << "2. Enter Course Marks" << endl;
        cout << "3. View Student Courses" << endl;
        cout << "4. Remove Course" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << string(50, '-') << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: addCourseToStudent(); break;
            case 2: updateCourseMarks(); break;
            case 3: viewCoursesOfStudent(); break;
            case 4: removeCourseFromStudent(); break;
            case 0: inMenu = false; break;
            default: cout << "✗ Invalid choice!" << endl;
        }
    }
}

void displayReportMenu() {
    displayHeader("REPORT GENERATION");
    int choice;
    bool inMenu = true;

    while (inMenu) {
        cout << "\n1. Generate Single Report" << endl;
        cout << "2. Generate All Reports for Student" << endl;
        cout << "3. View Grading Table" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << string(50, '-') << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: generateReport(); break;
            case 2: generateAllReports(); break;
            case 3:
                GradeCalculator::getInstance()->displayGradingTable();
                break;
            case 0: inMenu = false; break;
            default: cout << "✗ Invalid choice!" << endl;
        }
    }
}

void displaySettingsMenu() {
    displayHeader("SETTINGS & UTILITIES");
    int choice;
    bool inMenu = true;

    while (inMenu) {
        cout << "\n1. Change Grading Strategy" << endl;
        cout << "2. Create Backup" << endl;
        cout << "3. Restore from Backup" << endl;
        cout << "4. File Information" << endl;
        cout << "5. View Grading Strategies" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << string(50, '-') << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                cout << "\n1. Standard Weighted Average" << endl;
                cout << "2. Adjusted Grading (With Curve)" << endl;
                cout << "Enter strategy: ";
                cin >> choice;
                if (choice == 1) {
                    GradeCalculator::getInstance()->setGradingStrategy(new WeightedAverageStrategy());
                } else if (choice == 2) {
                    GradeCalculator::getInstance()->setGradingStrategy(new AdjustedGradingStrategy());
                }
                break;
            }
            case 2:
                fileManager.createBackup();
                break;
            case 3:
                fileManager.restoreFromBackup();
                break;
            case 4:
                fileManager.displayFileInfo();
                break;
            case 5:
                GradeCalculator::getInstance()->displayAvailableStrategies();
                break;
            case 0:
                inMenu = false;
                break;
            default:
                cout << "✗ Invalid choice!" << endl;
        }
    }
}

// ==================== STUDENT MANAGEMENT FUNCTIONS ====================
void addStudent() {
    displayHeader("ADD NEW STUDENT");

    string rollNo, name, email;
    cout << "Enter Roll Number: ";
    getline(cin, rollNo);
    cout << "Enter Student Name: ";
    getline(cin, name);
    cout << "Enter Email Address: ";
    getline(cin, email);

    Student newStudent(rollNo, name, email);

    cout << "Enter Current CGPA (0 if none): ";
    float cgpa;
    cin >> cgpa;
    newStudent.setCurrentCGPA(cgpa);

    cout << "Enter Total Credit Hours Passed (0 if first semester): ";
    int credits;
    cin >> credits;
    newStudent.setTotalCreditHours(credits);

    students.push_back(newStudent);
    cout << "\n✓ Student added successfully!" << endl;
}

void updateStudent() {
    if (students.empty()) {
        cout << "✗ No students found!" << endl;
        return;
    }

    displayHeader("UPDATE STUDENT INFO");
    string rollNo;
    cout << "Enter Roll Number to update: ";
    getline(cin, rollNo);

    for (auto& student : students) {
        if (student.getRollNo() == rollNo) {
            cout << "\nCurrent Information:" << endl;
            student.displayStudentInfo();

            cout << "\nEnter new email (press Enter to skip): ";
            string email;
            getline(cin, email);
            if (!email.empty()) {
                student.setEmail(email);
            }

            cout << "Enter updated CGPA: ";
            float cgpa;
            cin >> cgpa;
            student.setCurrentCGPA(cgpa);

            cout << "✓ Student updated successfully!" << endl;
            return;
        }
    }

    cout << "✗ Student not found!" << endl;
}

void deleteStudent() {
    if (students.empty()) {
        cout << "✗ No students found!" << endl;
        return;
    }

    displayHeader("DELETE STUDENT");
    string rollNo;
    cout << "Enter Roll Number to delete: ";
    getline(cin, rollNo);

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->getRollNo() == rollNo) {
            cout << "Deleting: " << it->getName() << endl;
            students.erase(it);
            cout << "✓ Student deleted successfully!" << endl;
            return;
        }
    }

    cout << "✗ Student not found!" << endl;
}

void listStudents() {
    if (students.empty()) {
        cout << "\n✗ No students found!" << endl;
        return;
    }

    displayHeader("ALL STUDENTS");
    cout << left << setw(12) << "Roll No"
         << setw(25) << "Name"
         << setw(30) << "Email"
         << setw(10) << "CGPA"
         << setw(12) << "Courses" << endl;
    cout << string(90, '-') << endl;

    for (const auto& student : students) {
        cout << left << setw(12) << student.getRollNo()
             << setw(25) << student.getName()
             << setw(30) << student.getEmail()
             << setw(10) << fixed << setprecision(2) << student.getCurrentCGPA()
             << setw(12) << student.getNumberOfCourses() << endl;
    }
}

void viewStudentDetails() {
    if (students.empty()) {
        cout << "✗ No students found!" << endl;
        return;
    }

    string rollNo;
    cout << "Enter Roll Number: ";
    getline(cin, rollNo);

    for (auto& student : students) {
        if (student.getRollNo() == rollNo) {
            student.displayTranscript();
            return;
        }
    }

    cout << "✗ Student not found!" << endl;
}

// ==================== COURSE MANAGEMENT FUNCTIONS ====================
void addCourseToStudent() {
    if (students.empty()) {
        cout << "✗ No students found!" << endl;
        return;
    }

    displayHeader("ADD COURSE TO STUDENT");
    string rollNo;
    cout << "Enter Student Roll Number: ";
    getline(cin, rollNo);

    for (auto& student : students) {
        if (student.getRollNo() == rollNo) {
            string code, name;
            int credits;

            cout << "Enter Course Code: ";
            getline(cin, code);
            cout << "Enter Course Name: ";
            getline(cin, name);
            cout << "Enter Credit Hours (1-5): ";
            cin >> credits;
            cin.ignore();

            Course newCourse(code, name, credits);
            student.addCourse(newCourse);
            return;
        }
    }

    cout << "✗ Student not found!" << endl;
}

void updateCourseMarks() {
    if (students.empty()) {
        cout << "✗ No students found!" << endl;
        return;
    }

    displayHeader("ENTER COURSE MARKS");
    string rollNo;
    cout << "Enter Student Roll Number: ";
    getline(cin, rollNo);

    for (auto& student : students) {
        if (student.getRollNo() == rollNo) {
            if (student.getNumberOfCourses() == 0) {
                cout << "X No courses enrolled!" << endl;
                return;
            }

            student.displayAllCourses();

            cout << "\nEnter Course Code: ";
            string courseCode;
            getline(cin, courseCode);

            int idx = student.findCourseByCode(courseCode);
            if (idx == -1) {
                cout << "X Course not found!" << endl;
                return;
            }

            Course& course = student.getCourse(idx);
            float assignment, midterm, final, project;

            cout << "Enter Assignment/Quiz Marks (0-100): ";
            cin >> assignment;
            cout << "Enter Midterm Exam Marks (0-100): ";
            cin >> midterm;
            cout << "Enter Final Exam Marks (0-100): ";
            cin >> final;
            cout << "Enter Project Work Marks (0-100): ";
            cin >> project;
            cin.ignore();

            course.setAssignmentMarks(assignment);
            course.setMidtermMarks(midterm);
            course.setFinalMarks(final);
            course.setProjectMarks(project);
            course.setCompleted(true);

            cout << "\n✓ Marks entered successfully!" << endl;
            course.displayGradeInfo();

            // Trigger notifications
            GradeChangeNotifier::getInstance()->checkAndNotify(course);
            return;
        }
    }

    cout << "✗ Student not found!" << endl;
}

void removeCourseFromStudent() {
    if (students.empty()) {
        cout << "✗ No students found!" << endl;
        return;
    }

    string rollNo;
    cout << "Enter Student Roll Number: ";
    getline(cin, rollNo);

    for (auto& student : students) {
        if (student.getRollNo() == rollNo) {
            if (student.getNumberOfCourses() == 0) {
                cout << "✗ No courses enrolled!" << endl;
                return;
            }

            student.displayAllCourses();
            cout << "Enter course number to remove: ";
            int idx;
            cin >> idx;
            cin.ignore();

            if (idx > 0 && idx <= student.getNumberOfCourses()) {
                student.removeCourse(idx - 1);
            } else {
                cout << "✗ Invalid course number!" << endl;
            }
            return;
        }
    }

    cout << "✗ Student not found!" << endl;
}

void viewCoursesOfStudent() {
    if (students.empty()) {
        cout << "✗ No students found!" << endl;
        return;
    }

    string rollNo;
    cout << "Enter Student Roll Number: ";
    getline(cin, rollNo);

    for (auto& student : students) {
        if (student.getRollNo() == rollNo) {
            student.displayAllCourses();
            return;
        }
    }

    cout << "✗ Student not found!" << endl;
}

// ==================== REPORT FUNCTIONS ====================
void generateReport() {
    if (students.empty()) {
        cout << "✗ No students found!" << endl;
        return;
    }

    string rollNo;
    cout << "Enter Student Roll Number: ";
    getline(cin, rollNo);

    for (auto& student : students) {
        if (student.getRollNo() == rollNo) {
            ReportFactory::displayAvailableReports();
            cout << "Enter report type (1-4): ";
            int type;
            cin >> type;
            cin.ignore();

            ReportManager::generateAndDisplayReport(student, (ReportFactory::ReportType)(type - 1));
            return;
        }
    }

    cout << "✗ Student not found!" << endl;
}

void generateAllReports() {
    if (students.empty()) {
        cout << "✗ No students found!" << endl;
        return;
    }

    string rollNo;
    cout << "Enter Student Roll Number: ";
    getline(cin, rollNo);

    for (auto& student : students) {
        if (student.getRollNo() == rollNo) {
            ReportManager::generateAllReports(student);
            return;
        }
    }

    cout << "✗ Student not found!" << endl;
}

// ==================== UOG CGPA CALCULATOR ====================
void uogCGPACalculator() {
    displayHeader("UOG CGPA CALCULATOR - University of Gujrat");

    // Grade reference table
    cout << "\nGrade Point Reference (University of Gujrat):" << endl;
    cout << string(40, '-') << endl;
    cout << left << setw(10) << "Grade" << setw(15) << "Grade Points" << endl;
    cout << string(40, '-') << endl;
    cout << left << setw(10) << "A+"  << setw(15) << "4.00" << endl;
    cout << left << setw(10) << "A"   << setw(15) << "3.70" << endl;
    cout << left << setw(10) << "B+"  << setw(15) << "3.40" << endl;
    cout << left << setw(10) << "B"   << setw(15) << "3.00" << endl;
    cout << left << setw(10) << "B-"  << setw(15) << "2.50" << endl;
    cout << left << setw(10) << "C+"  << setw(15) << "2.00" << endl;
    cout << left << setw(10) << "C"   << setw(15) << "1.50" << endl;
    cout << left << setw(10) << "D"   << setw(15) << "1.00" << endl;
    cout << left << setw(10) << "F"   << setw(15) << "0.00" << endl;
    cout << string(40, '-') << endl;

    // Optional previous CGPA
    float prevCGPA = 0.0f;
    int prevCreditHours = 0;

    cout << "\nEnter current CGPA (press Enter to skip if 1st semester): ";
    string cgpaInput;
    getline(cin, cgpaInput);
    if (!cgpaInput.empty()) {
        try { prevCGPA = stof(cgpaInput); } catch (...) { prevCGPA = 0.0f; }
        if (prevCGPA > 0.0f) {
            cout << "Enter total credit hours completed so far: ";
            cin >> prevCreditHours;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Number of courses
    int numCourses = 0;
    cout << "\nEnter number of courses this semester: ";
    cin >> numCourses;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (numCourses <= 0) {
        cout << "✗ Invalid number of courses!" << endl;
        return;
    }

    // Helper: grade letter -> grade points
    auto gradeToPoints = [](const string& g) -> float {
        if (g == "A+") return GPA_AP;
        if (g == "A")  return GPA_A;
        if (g == "B+") return GPA_BP;
        if (g == "B")  return GPA_B;
        if (g == "B-") return GPA_BM;
        if (g == "C+") return GPA_CP;
        if (g == "C")  return GPA_C;
        if (g == "D")  return GPA_D;
        return GPA_F;
    };

    struct CourseEntry { string name, grade; float gradePoints; int credits; };
    vector<CourseEntry> courses;
    float totalGradePoints = 0.0f;
    int totalCredits = 0;

    for (int i = 0; i < numCourses; i++) {
        CourseEntry entry;
        cout << "\n--- Course " << (i + 1) << " ---" << endl;

        cout << "Course Name (press Enter to skip): ";
        getline(cin, entry.name);
        if (entry.name.empty()) entry.name = "Course " + to_string(i + 1);

        cout << "Enter Grade (A+/A/B+/B/B-/C+/C/D/F): ";
        getline(cin, entry.grade);
        for (char& c : entry.grade) c = toupper(c);

        entry.gradePoints = gradeToPoints(entry.grade);
        cout << "  -> Grade Points: " << fixed << setprecision(2) << entry.gradePoints << endl;

        cout << "Enter Credit Hours (1-5): ";
        cin >> entry.credits;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (entry.credits < 1) entry.credits = 1;
        if (entry.credits > 5) entry.credits = 5;

        float contribution = entry.gradePoints * entry.credits;
        cout << "  -> Contribution: " << fixed << setprecision(2) << entry.gradePoints
             << " x " << entry.credits << " = " << contribution << endl;

        totalGradePoints += contribution;
        totalCredits += entry.credits;
        courses.push_back(entry);
    }

    // Summary table
    cout << "\n" << string(100, '=') << endl;
    cout << "SEMESTER SUMMARY" << endl;
    cout << string(100, '=') << endl;
    cout << left << setw(25) << "Course" << setw(8) << "Grade"
         << setw(14) << "Grd Points" << setw(10) << "Credits"
         << setw(14) << "Contribution" << endl;
    cout << string(71, '-') << endl;

    for (const auto& c : courses) {
        float contrib = c.gradePoints * c.credits;
        cout << left << setw(25) << c.name << setw(8) << c.grade
             << setw(14) << fixed << setprecision(2) << c.gradePoints
             << setw(10) << c.credits
             << setw(14) << fixed << setprecision(2) << contrib << endl;
    }

    cout << string(71, '-') << endl;
    cout << left << setw(25) << "TOTALS" << setw(8) << "" << setw(14) << ""
         << setw(10) << totalCredits
         << setw(14) << fixed << setprecision(2) << totalGradePoints << endl;

    float semGPA = totalCredits > 0 ? totalGradePoints / totalCredits : 0.0f;
    cout << "\nSemester GPA : " << fixed << setprecision(2) << semGPA << endl;

    if (prevCGPA > 0.0f && prevCreditHours > 0) {
        float prevGP   = prevCGPA * prevCreditHours;
        float cumGP    = prevGP + totalGradePoints;
        int   cumCred  = prevCreditHours + totalCredits;
        float newCGPA  = cumCred > 0 ? cumGP / cumCred : semGPA;

        cout << "\nCGPA Calculation:" << endl;
        cout << "  Previous : CGPA " << fixed << setprecision(2) << prevCGPA
             << " x " << prevCreditHours << " credits = "
             << fixed << setprecision(2) << prevGP << " grade points" << endl;
        cout << "  Current  : GPA  " << fixed << setprecision(2) << semGPA
             << " x " << totalCredits << " credits = "
             << fixed << setprecision(2) << totalGradePoints << " grade points" << endl;
        cout << "  Updated CGPA = " << fixed << setprecision(2) << cumGP
             << " / " << cumCred << " = " << fixed << setprecision(2) << newCGPA << endl;
    } else {
        cout << "CGPA         : " << fixed << setprecision(2) << semGPA
             << " (1st Semester)" << endl;
    }

    cout << string(100, '=') << endl;
}

// ==================== UTILITY FUNCTIONS ====================
void clearScreen() {
    system("cls");
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

void displayHeader(const string& title) {
    cout << "\n" << string(100, '=') << endl;
    cout << title << endl;
    cout << string(100, '=') << endl;
}
