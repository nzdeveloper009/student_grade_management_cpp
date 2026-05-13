#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <string>
#include "Student.h"

// Abstract Report Interface
class Report {
public:
    virtual ~Report() = default;
    virtual void generate(const Student& student) const = 0;
    virtual std::string getReportType() const = 0;
};

// Concrete Report: Academic Transcript
class TranscriptReport : public Report {
public:
    void generate(const Student& student) const override;
    std::string getReportType() const override;
};

// Concrete Report: Semester Grade Report
class SemesterGradeReport : public Report {
public:
    void generate(const Student& student) const override;
    std::string getReportType() const override;
};

// Concrete Report: CGPA Progress Report
class CGPAProgressReport : public Report {
public:
    void generate(const Student& student) const override;
    std::string getReportType() const override;
};

// Concrete Report: Detailed Course Analysis
class DetailedAnalysisReport : public Report {
public:
    void generate(const Student& student) const override;
    std::string getReportType() const override;
};

// ==================== FACTORY PATTERN ====================
class ReportFactory {
public:
    enum ReportType {
        TRANSCRIPT,
        SEMESTER_GRADE,
        CGPA_PROGRESS,
        DETAILED_ANALYSIS
    };

    static Report* createReport(ReportType type);
    static void displayAvailableReports();
};

// Report Manager (Facade)
class ReportManager {
public:
    static void generateAndDisplayReport(const Student& student, ReportFactory::ReportType type);
    static void generateAllReports(const Student& student);
};

#endif
