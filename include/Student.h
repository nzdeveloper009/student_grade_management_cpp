#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Course.h"

class Student {
private:
    std::string rollNo;
    std::string name;
    std::string email;
    std::vector<Course> courses;
    float currentCGPA;
    int totalCreditHoursPassed;
    int semesterNumber;

public:
    // Constructors
    Student();
    Student(std::string roll, std::string studentName, std::string studentEmail);

    // Setters (Encapsulation)
    void setRollNo(std::string roll);
    void setName(std::string studentName);
    void setEmail(std::string studentEmail);
    void setCurrentCGPA(float cgpa);
    void setTotalCreditHours(int hours);
    void setSemesterNumber(int sem);

    // Getters (Encapsulation)
    std::string getRollNo() const;
    std::string getName() const;
    std::string getEmail() const;
    float getCurrentCGPA() const;
    int getTotalCreditHours() const;
    int getSemesterNumber() const;
    int getNumberOfCourses() const;

    // Course Management
    void addCourse(const Course& course);
    void removeCourse(int courseIndex);
    Course& getCourse(int courseIndex);
    const Course& getCourse(int courseIndex) const;
    void displayAllCourses() const;

    // GPA Calculation Methods
    float calculateSemesterGPA() const;
    float calculateCGPA() const;
    float calculateTotalGradePoints() const;
    float calculateTotalCreditHours() const;

    // Display Methods
    void displayStudentInfo() const;
    void displayTranscript() const;
    void displaySemesterSummary() const;
    void displayDetailedReport() const;

    // Validation Methods
    bool isValidEmail(const std::string& email) const;
    bool isCourseCodeExists(const std::string& code) const;

    // Utility Methods
    int findCourseByCode(const std::string& code) const;
    void clearAllCourses();
};

#endif
