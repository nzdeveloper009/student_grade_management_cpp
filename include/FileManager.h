#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "Student.h"

class FileManager {
private:
    std::string filePath;

    // Helper methods
    std::string studentToCSV(const Student& student) const;
    Student csvToStudent(const std::string& line) const;
    bool directoryExists(const std::string& path) const;
    void createDirectory(const std::string& path) const;

public:
    FileManager(std::string path = "data/students.csv");

    // File operations
    bool saveStudents(const std::vector<Student>& students) const;
    std::vector<Student> loadStudents() const;
    bool saveStudent(const Student& student, bool append = true) const;
    bool deleteStudentRecord(const std::string& rollNo);

    // File utilities
    bool fileExists() const;
    void createBackup() const;
    bool restoreFromBackup();
    void clearData() const;
    int getRecordCount() const;

    // Setters and Getters
    void setFilePath(std::string path);
    std::string getFilePath() const;

    // Display methods
    void displayFileInfo() const;
};

#endif
