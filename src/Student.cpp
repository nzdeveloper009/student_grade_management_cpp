#include "../include/Student.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <regex>

// ==================== CONSTRUCTORS ====================
Student::Student()
    : rollNo(""), name(""), email(""), currentCGPA(0.0f),
      totalCreditHoursPassed(0), semesterNumber(1) {}

Student::Student(std::string roll, std::string studentName, std::string studentEmail)
    : rollNo(roll), name(studentName), email(studentEmail),
      currentCGPA(0.0f), totalCreditHoursPassed(0), semesterNumber(1) {}

// ==================== SETTERS ====================
void Student::setRollNo(std::string roll) {
    rollNo = roll;
}

void Student::setName(std::string studentName) {
    name = studentName;
}

void Student::setEmail(std::string studentEmail) {
    if (isValidEmail(studentEmail)) {
        email = studentEmail;
    }
}

void Student::setCurrentCGPA(float cgpa) {
    if (cgpa >= 0.0f && cgpa <= 4.0f) {
        currentCGPA = cgpa;
    }
}

void Student::setTotalCreditHours(int hours) {
    if (hours >= 0) {
        totalCreditHoursPassed = hours;
    }
}

void Student::setSemesterNumber(int sem) {
    if (sem > 0) {
        semesterNumber = sem;
    }
}

// ==================== GETTERS ====================
std::string Student::getRollNo() const {
    return rollNo;
}

std::string Student::getName() const {
    return name;
}

std::string Student::getEmail() const {
    return email;
}

float Student::getCurrentCGPA() const {
    return currentCGPA;
}

int Student::getTotalCreditHours() const {
    return totalCreditHoursPassed;
}

int Student::getSemesterNumber() const {
    return semesterNumber;
}

int Student::getNumberOfCourses() const {
    return courses.size();
}

// ==================== COURSE MANAGEMENT ====================
void Student::addCourse(const Course& course) {
    if (courses.size() < MAX_COURSES_PER_STUDENT) {
        if (!isCourseCodeExists(course.getCourseCode())) {
            courses.push_back(course);
            std::cout << "✓ Course added successfully!" << std::endl;
        } else {
            std::cout << "✗ Course code already exists!" << std::endl;
        }
    } else {
        std::cout << "✗ Maximum courses limit reached!" << std::endl;
    }
}

void Student::removeCourse(int courseIndex) {
    if (courseIndex >= 0 && courseIndex < (int)courses.size()) {
        courses.erase(courses.begin() + courseIndex);
        std::cout << "✓ Course removed successfully!" << std::endl;
    } else {
        std::cout << "✗ Invalid course index!" << std::endl;
    }
}

Course& Student::getCourse(int courseIndex) {
    return courses.at(courseIndex);
}

const Course& Student::getCourse(int courseIndex) const {
    return courses.at(courseIndex);
}

void Student::displayAllCourses() const {
    if (courses.empty()) {
        std::cout << "\n✗ No courses enrolled!" << std::endl;
        return;
    }

    std::cout << "\n" << std::string(100, '=') << std::endl;
    std::cout << std::left << std::setw(8) << "No." << std::setw(12) << "Code"
              << std::setw(20) << "Name" << std::setw(8) << "Credit"
              << std::setw(12) << "Percentage" << std::setw(10) << "Grade"
              << std::setw(8) << "GPA" << std::setw(15) << "Category" << std::endl;
    std::cout << std::string(100, '-') << std::endl;

    for (int i = 0; i < (int)courses.size(); i++) {
        std::cout << std::left << std::setw(8) << (i + 1)
                  << std::setw(12) << courses[i].getCourseCode()
                  << std::setw(20) << courses[i].getCourseName()
                  << std::setw(8) << courses[i].getCreditHours()
                  << std::setw(12) << std::fixed << std::setprecision(2) << courses[i].calculatePercentage()
                  << std::setw(10) << courses[i].getGrade()
                  << std::setw(8) << courses[i].getGradePoint()
                  << std::setw(15) << courses[i].getCategory() << std::endl;
    }
    std::cout << std::string(100, '=') << std::endl;
}

// ==================== GPA CALCULATION ====================
float Student::calculateSemesterGPA() const {
    if (courses.empty()) {
        return 0.0f;
    }

    float totalGradePoints = 0.0f;
    float totalCredits = 0.0f;

    for (const auto& course : courses) {
        totalGradePoints += course.getGradePoint() * course.getCreditHours();
        totalCredits += course.getCreditHours();
    }

    return totalCredits > 0 ? totalGradePoints / totalCredits : 0.0f;
}

float Student::calculateTotalGradePoints() const {
    float totalPoints = 0.0f;
    for (const auto& course : courses) {
        totalPoints += course.getGradePoint() * course.getCreditHours();
    }
    return totalPoints;
}

float Student::calculateTotalCreditHours() const {
    float totalCredits = 0.0f;
    for (const auto& course : courses) {
        if (course.getCompleted()) {
            totalCredits += course.getCreditHours();
        }
    }
    return totalCredits;
}

float Student::calculateCGPA() const {
    float totalCredits = totalCreditHoursPassed + calculateTotalCreditHours();
    if (totalCredits == 0) {
        return calculateSemesterGPA();
    }

    float totalGradePoints = (currentCGPA * totalCreditHoursPassed) + calculateTotalGradePoints();
    return totalGradePoints / totalCredits;
}

// ==================== DISPLAY METHODS ====================
void Student::displayStudentInfo() const {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "STUDENT INFORMATION" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    std::cout << "Roll Number       : " << rollNo << std::endl;
    std::cout << "Name              : " << name << std::endl;
    std::cout << "Email             : " << email << std::endl;
    std::cout << "Semester          : " << semesterNumber << std::endl;
    std::cout << "Courses Enrolled  : " << courses.size() << std::endl;
    std::cout << std::string(70, '=') << std::endl;
}

void Student::displayTranscript() const {
    displayStudentInfo();
    displayAllCourses();

    std::cout << "\nACHIEVEMENTS SUMMARY:" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    std::cout << "Semester GPA      : " << std::fixed << std::setprecision(3) << calculateSemesterGPA() << std::endl;
    std::cout << "Current CGPA      : " << currentCGPA << std::endl;
    std::cout << "Cumulative GPA    : " << calculateCGPA() << std::endl;
    std::cout << std::string(70, '=') << std::endl;
}

void Student::displaySemesterSummary() const {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "SEMESTER " << semesterNumber << " SUMMARY - " << name << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    std::cout << "Total Courses     : " << courses.size() << std::endl;
    std::cout << "Semester GPA      : " << std::fixed << std::setprecision(3) << calculateSemesterGPA() << std::endl;

    if (!courses.empty()) {
        std::cout << "\nCourse Breakdown:" << std::endl;
        displayAllCourses();
    }
    std::cout << std::string(70, '=') << std::endl;
}

void Student::displayDetailedReport() const {
    displayTranscript();
    std::cout << "\nDETAILED ANALYSIS:" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    for (int i = 0; i < (int)courses.size(); i++) {
        std::cout << "\n[Course " << (i + 1) << "]" << std::endl;
        courses[i].displayCourseInfo();
        courses[i].displayGradeInfo();
    }
}

// ==================== VALIDATION METHODS ====================
bool Student::isValidEmail(const std::string& email) const {
    std::regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, emailPattern);
}

bool Student::isCourseCodeExists(const std::string& code) const {
    for (const auto& course : courses) {
        if (course.getCourseCode() == code) {
            return true;
        }
    }
    return false;
}

// ==================== UTILITY METHODS ====================
int Student::findCourseByCode(const std::string& code) const {
    for (int i = 0; i < (int)courses.size(); i++) {
        if (courses[i].getCourseCode() == code) {
            return i;
        }
    }
    return -1;
}

void Student::clearAllCourses() {
    courses.clear();
    std::cout << "✓ All courses cleared!" << std::endl;
}
