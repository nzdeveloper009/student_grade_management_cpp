#include "../include/Course.h"
#include "../include/GradeCalculator.h"
#include <iostream>
#include <iomanip>

// ==================== CONSTRUCTORS ====================
Course::Course()
    : courseCode(""), courseName(""), creditHours(0),
      assignmentMarks(0), midtermMarks(0), finalMarks(0),
      projectMarks(0), isCompleted(false) {}

Course::Course(std::string code, std::string name, int credits)
    : courseCode(code), courseName(name), creditHours(credits),
      assignmentMarks(0), midtermMarks(0), finalMarks(0),
      projectMarks(0), isCompleted(false) {}

// ==================== SETTERS ====================
void Course::setCourseCode(std::string code) {
    courseCode = code;
}

void Course::setCourseName(std::string name) {
    courseName = name;
}

void Course::setCreditHours(int hours) {
    if (hours >= MIN_CREDIT_HOURS && hours <= MAX_CREDIT_HOURS) {
        creditHours = hours;
    }
}

void Course::setAssignmentMarks(float marks) {
    if (isValidMarks(marks)) {
        assignmentMarks = marks;
    }
}

void Course::setMidtermMarks(float marks) {
    if (isValidMarks(marks)) {
        midtermMarks = marks;
    }
}

void Course::setFinalMarks(float marks) {
    if (isValidMarks(marks)) {
        finalMarks = marks;
    }
}

void Course::setProjectMarks(float marks) {
    if (isValidMarks(marks)) {
        projectMarks = marks;
    }
}

void Course::setCompleted(bool status) {
    isCompleted = status;
}

// ==================== GETTERS ====================
std::string Course::getCourseCode() const {
    return courseCode;
}

std::string Course::getCourseName() const {
    return courseName;
}

int Course::getCreditHours() const {
    return creditHours;
}

float Course::getAssignmentMarks() const {
    return assignmentMarks;
}

float Course::getMidtermMarks() const {
    return midtermMarks;
}

float Course::getFinalMarks() const {
    return finalMarks;
}

float Course::getProjectMarks() const {
    return projectMarks;
}

bool Course::getCompleted() const {
    return isCompleted;
}

// ==================== CORE METHODS ====================
float Course::calculateTotalMarks() const {
    GradeCalculator* calc = GradeCalculator::getInstance();
    return calc->calculatePercentage(assignmentMarks, midtermMarks, finalMarks, projectMarks);
}

float Course::calculatePercentage() const {
    return calculateTotalMarks();
}

std::string Course::getGrade() const {
    GradeCalculator* calc = GradeCalculator::getInstance();
    return calc->percentageToGrade(calculateTotalMarks());
}

float Course::getGradePoint() const {
    GradeCalculator* calc = GradeCalculator::getInstance();
    return calc->percentageToGPA(calculateTotalMarks());
}

std::string Course::getCategory() const {
    GradeCalculator* calc = GradeCalculator::getInstance();
    return calc->percentageToCategory(calculateTotalMarks());
}

// ==================== DISPLAY METHODS ====================
void Course::displayCourseInfo() const {
    std::cout << "\n" << std::string(70, '-') << std::endl;
    std::cout << "Course Code       : " << courseCode << std::endl;
    std::cout << "Course Name       : " << courseName << std::endl;
    std::cout << "Credit Hours      : " << creditHours << std::endl;
    std::cout << "Status            : " << (isCompleted ? "Completed" : "In Progress") << std::endl;
}

void Course::displayGradeInfo() const {
    std::cout << "\nGrade Information:" << std::endl;
    std::cout << "  Assignment Marks  : " << std::fixed << std::setprecision(2) << assignmentMarks << std::endl;
    std::cout << "  Midterm Marks     : " << midtermMarks << std::endl;
    std::cout << "  Final Marks       : " << finalMarks << std::endl;
    std::cout << "  Project Marks     : " << projectMarks << std::endl;
    std::cout << "  ---" << std::endl;
    std::cout << "  Total Percentage  : " << calculatePercentage() << "%" << std::endl;
    std::cout << "  Grade             : " << getGrade() << std::endl;
    std::cout << "  GPA               : " << getGradePoint() << std::endl;
    std::cout << "  Category          : " << getCategory() << std::endl;
    std::cout << std::string(70, '-') << std::endl;
}

// ==================== VALIDATION METHODS ====================
bool Course::isValidMarks(float marks) const {
    return marks >= MIN_ASSIGNMENT_MARKS && marks <= MAX_ASSIGNMENT_MARKS;
}

bool Course::isAllMarksEntered() const {
    return assignmentMarks > 0 && midtermMarks > 0 && finalMarks > 0 && projectMarks > 0;
}
