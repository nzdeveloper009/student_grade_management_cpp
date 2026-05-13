#ifndef COURSE_H
#define COURSE_H

#include <string>
#include "Constants.h"

class Course {
private:
    std::string courseCode;
    std::string courseName;
    int creditHours;
    float assignmentMarks;
    float midtermMarks;
    float finalMarks;
    float projectMarks;
    bool isCompleted;

public:
    // Constructors
    Course();
    Course(std::string code, std::string name, int credits);

    // Setters (Encapsulation)
    void setCourseCode(std::string code);
    void setCourseName(std::string name);
    void setCreditHours(int hours);
    void setAssignmentMarks(float marks);
    void setMidtermMarks(float marks);
    void setFinalMarks(float marks);
    void setProjectMarks(float marks);
    void setCompleted(bool status);

    // Getters (Encapsulation)
    std::string getCourseCode() const;
    std::string getCourseName() const;
    int getCreditHours() const;
    float getAssignmentMarks() const;
    float getMidtermMarks() const;
    float getFinalMarks() const;
    float getProjectMarks() const;
    bool getCompleted() const;

    // Core Methods
    float calculateTotalMarks() const;
    float calculatePercentage() const;
    std::string getGrade() const;
    float getGradePoint() const;
    std::string getCategory() const;

    // Display Methods
    void displayCourseInfo() const;
    void displayGradeInfo() const;

    // Utility Methods
    bool isValidMarks(float marks) const;
    bool isAllMarksEntered() const;
};

#endif
