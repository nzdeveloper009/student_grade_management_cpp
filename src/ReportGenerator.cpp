#include "../include/ReportGenerator.h"
#include "../include/GradeCalculator.h"
#include <iostream>
#include <iomanip>

// ==================== TRANSCRIPT REPORT ====================
void TranscriptReport::generate(const Student& student) const {
    std::cout << "\n" << std::string(100, '=') << std::endl;
    std::cout << "ACADEMIC TRANSCRIPT - UNIVERSITY OF GUJRAT" << std::endl;
    std::cout << std::string(100, '=') << std::endl;

    student.displayStudentInfo();
    student.displayAllCourses();

    std::cout << "\nTRANSCRIPT SUMMARY:" << std::endl;
    std::cout << std::string(100, '-') << std::endl;
    std::cout << "Semester GPA             : " << std::fixed << std::setprecision(3) << student.calculateSemesterGPA() << std::endl;
    std::cout << "Previous CGPA            : " << student.getCurrentCGPA() << std::endl;
    std::cout << "Previous Credit Hours    : " << student.getTotalCreditHours() << std::endl;
    std::cout << "Updated CGPA             : " << student.calculateCGPA() << std::endl;
    std::cout << std::string(100, '=') << std::endl;
}

std::string TranscriptReport::getReportType() const {
    return "Academic Transcript";
}

// ==================== SEMESTER GRADE REPORT ====================
void SemesterGradeReport::generate(const Student& student) const {
    std::cout << "\n" << std::string(100, '=') << std::endl;
    std::cout << "SEMESTER " << student.getSemesterNumber() << " GRADE REPORT" << std::endl;
    std::cout << "Student: " << student.getName() << " (" << student.getRollNo() << ")" << std::endl;
    std::cout << std::string(100, '=') << std::endl;

    if (student.getNumberOfCourses() == 0) {
        std::cout << "No courses enrolled for this semester." << std::endl;
        std::cout << std::string(100, '=') << std::endl;
        return;
    }

    std::cout << std::left << std::setw(8) << "No."
              << std::setw(12) << "Code"
              << std::setw(25) << "Name"
              << std::setw(8) << "Marks"
              << std::setw(10) << "Grade"
              << std::setw(8) << "GPA"
              << std::setw(15) << "Category" << std::endl;
    std::cout << std::string(100, '-') << std::endl;

    float totalGradePoints = 0.0f;
    float totalCredits = 0.0f;

    for (int i = 0; i < student.getNumberOfCourses(); i++) {
        const Course& course = student.getCourse(i);
        totalGradePoints += course.getGradePoint() * course.getCreditHours();
        totalCredits += course.getCreditHours();

        std::cout << std::left << std::setw(8) << (i + 1)
                  << std::setw(12) << course.getCourseCode()
                  << std::setw(25) << course.getCourseName()
                  << std::setw(8) << std::fixed << std::setprecision(1) << course.calculatePercentage()
                  << std::setw(10) << course.getGrade()
                  << std::setw(8) << course.getGradePoint()
                  << std::setw(15) << course.getCategory() << std::endl;
    }

    std::cout << std::string(100, '-') << std::endl;
    float semesterGPA = (totalCredits > 0) ? (totalGradePoints / totalCredits) : 0.0f;
    std::cout << std::right << std::setw(73) << "Semester GPA: " << std::fixed << std::setprecision(3) << semesterGPA << std::endl;
    std::cout << std::string(100, '=') << std::endl;
}

std::string SemesterGradeReport::getReportType() const {
    return "Semester Grade Report";
}

// ==================== CGPA PROGRESS REPORT ====================
void CGPAProgressReport::generate(const Student& student) const {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "CGPA PROGRESS REPORT" << std::endl;
    std::cout << "Student: " << student.getName() << std::endl;
    std::cout << std::string(80, '=') << std::endl;

    std::cout << std::left << std::setw(30) << "Previous CGPA:"
              << std::fixed << std::setprecision(3) << student.getCurrentCGPA() << std::endl;
    std::cout << std::left << std::setw(30) << "Previous Credit Hours:"
              << student.getTotalCreditHours() << std::endl;
    std::cout << std::left << std::setw(30) << "Semester GPA:"
              << std::fixed << std::setprecision(3) << student.calculateSemesterGPA() << std::endl;
    std::cout << std::left << std::setw(30) << "Semester Credit Hours:"
              << (int)student.calculateTotalCreditHours() << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    std::cout << std::left << std::setw(30) << "Updated CGPA:"
              << std::fixed << std::setprecision(3) << student.calculateCGPA() << std::endl;

    float previousCGPA = student.getCurrentCGPA();
    float newCGPA = student.calculateCGPA();
    float difference = newCGPA - previousCGPA;

    if (difference > 0) {
        std::cout << std::left << std::setw(30) << "Change (↑):"
                  << std::fixed << std::setprecision(3) << difference << " [IMPROVED]" << std::endl;
    } else if (difference < 0) {
        std::cout << std::left << std::setw(30) << "Change (↓):"
                  << std::fixed << std::setprecision(3) << difference << " [DECLINED]" << std::endl;
    } else {
        std::cout << std::left << std::setw(30) << "Change:"
                  << "[NO CHANGE]" << std::endl;
    }

    std::cout << std::string(80, '=') << std::endl;
}

std::string CGPAProgressReport::getReportType() const {
    return "CGPA Progress Report";
}

// ==================== DETAILED ANALYSIS REPORT ====================
void DetailedAnalysisReport::generate(const Student& student) const {
    std::cout << "\n" << std::string(100, '=') << std::endl;
    std::cout << "DETAILED COURSE ANALYSIS REPORT" << std::endl;
    std::cout << "Student: " << student.getName() << " (" << student.getRollNo() << ")" << std::endl;
    std::cout << "Semester: " << student.getSemesterNumber() << std::endl;
    std::cout << std::string(100, '=') << std::endl;

    if (student.getNumberOfCourses() == 0) {
        std::cout << "No courses enrolled for this semester." << std::endl;
        std::cout << std::string(100, '=') << std::endl;
        return;
    }

    for (int i = 0; i < student.getNumberOfCourses(); i++) {
        const Course& course = student.getCourse(i);

        std::cout << "\n[Course " << (i + 1) << "/" << student.getNumberOfCourses() << "]" << std::endl;
        std::cout << std::string(100, '-') << std::endl;
        std::cout << "Code              : " << course.getCourseCode() << std::endl;
        std::cout << "Name              : " << course.getCourseName() << std::endl;
        std::cout << "Credit Hours      : " << course.getCreditHours() << std::endl;

        std::cout << "\nAssessment Breakdown:" << std::endl;
        std::cout << "  Assignment/Quiz : " << std::fixed << std::setprecision(1)
                  << course.getAssignmentMarks() << "/100 (20%)" << std::endl;
        std::cout << "  Midterm Exam    : " << course.getMidtermMarks() << "/100 (20%)" << std::endl;
        std::cout << "  Final Exam      : " << course.getFinalMarks() << "/100 (40%)" << std::endl;
        std::cout << "  Project Work    : " << course.getProjectMarks() << "/100 (20%)" << std::endl;

        std::cout << "\nFinal Grades:" << std::endl;
        std::cout << "  Overall Score   : " << std::fixed << std::setprecision(2) << course.calculatePercentage() << "%" << std::endl;
        std::cout << "  Grade           : " << course.getGrade() << std::endl;
        std::cout << "  GPA Points      : " << course.getGradePoint() << std::endl;
        std::cout << "  Category        : " << course.getCategory() << std::endl;
    }

    std::cout << "\n" << std::string(100, '=') << std::endl;
    std::cout << "OVERALL PERFORMANCE:" << std::endl;
    std::cout << "Semester GPA        : " << std::fixed << std::setprecision(3) << student.calculateSemesterGPA() << std::endl;
    std::cout << "CGPA                : " << student.calculateCGPA() << std::endl;
    std::cout << std::string(100, '=') << std::endl;
}

std::string DetailedAnalysisReport::getReportType() const {
    return "Detailed Course Analysis";
}

// ==================== FACTORY PATTERN ====================
Report* ReportFactory::createReport(ReportType type) {
    switch (type) {
        case TRANSCRIPT:
            return new TranscriptReport();
        case SEMESTER_GRADE:
            return new SemesterGradeReport();
        case CGPA_PROGRESS:
            return new CGPAProgressReport();
        case DETAILED_ANALYSIS:
            return new DetailedAnalysisReport();
        default:
            return new SemesterGradeReport();
    }
}

void ReportFactory::displayAvailableReports() {
    std::cout << "\nAvailable Reports:" << std::endl;
    std::cout << "  1. Academic Transcript" << std::endl;
    std::cout << "  2. Semester Grade Report" << std::endl;
    std::cout << "  3. CGPA Progress Report" << std::endl;
    std::cout << "  4. Detailed Course Analysis" << std::endl;
}

// ==================== REPORT MANAGER ====================
void ReportManager::generateAndDisplayReport(const Student& student, ReportFactory::ReportType type) {
    Report* report = ReportFactory::createReport(type);
    report->generate(student);
    delete report;
}

void ReportManager::generateAllReports(const Student& student) {
    std::cout << "\n" << std::string(100, '*') << std::endl;
    std::cout << "GENERATING ALL REPORTS FOR: " << student.getName() << std::endl;
    std::cout << std::string(100, '*') << std::endl;

    ReportManager::generateAndDisplayReport(student, ReportFactory::TRANSCRIPT);
    ReportManager::generateAndDisplayReport(student, ReportFactory::SEMESTER_GRADE);
    ReportManager::generateAndDisplayReport(student, ReportFactory::CGPA_PROGRESS);
    ReportManager::generateAndDisplayReport(student, ReportFactory::DETAILED_ANALYSIS);

    std::cout << "\n" << std::string(100, '*') << std::endl;
    std::cout << "ALL REPORTS GENERATED SUCCESSFULLY" << std::endl;
    std::cout << std::string(100, '*') << std::endl;
}
