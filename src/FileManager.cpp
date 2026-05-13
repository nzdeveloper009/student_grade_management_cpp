#include "../include/FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

// ==================== CONSTRUCTORS ====================
FileManager::FileManager(std::string path) : filePath(path) {
    if (!directoryExists("data")) {
        createDirectory("data");
    }
}

// ==================== FILE OPERATIONS ====================
bool FileManager::saveStudents(const std::vector<Student>& students) const {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "✗ Error: Cannot open file for writing!" << std::endl;
        return false;
    }

    for (const auto& student : students) {
        file << studentToCSV(student);
    }

    file.close();
    std::cout << "✓ Saved " << students.size() << " student(s) to file." << std::endl;
    return true;
}

std::vector<Student> FileManager::loadStudents() const {
    std::vector<Student> students;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "✗ File not found or cannot be opened." << std::endl;
        return students;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            students.push_back(csvToStudent(line));
        }
    }

    file.close();
    std::cout << "✓ Loaded " << students.size() << " student(s) from file." << std::endl;
    return students;
}

bool FileManager::saveStudent(const Student& student, bool append) const {
    std::ios_base::openmode mode = append ? std::ios::app : std::ios::out;
    std::ofstream file(filePath, mode);

    if (!file.is_open()) {
        std::cerr << "✗ Error: Cannot open file for writing!" << std::endl;
        return false;
    }

    file << studentToCSV(student);
    file.close();
    std::cout << "✓ Student saved successfully." << std::endl;
    return true;
}

bool FileManager::deleteStudentRecord(const std::string& rollNo) {
    std::vector<Student> students = loadStudents();
    auto it = std::remove_if(students.begin(), students.end(),
                             [&](const Student& s) { return s.getRollNo() == rollNo; });

    if (it == students.end()) {
        std::cout << "✗ Student not found!" << std::endl;
        return false;
    }

    students.erase(it, students.end());
    return saveStudents(students);
}

// ==================== FILE UTILITIES ====================
bool FileManager::fileExists() const {
    std::ifstream file(filePath);
    return file.good();
}

void FileManager::createBackup() const {
    try {
        if (fileExists()) {
            fs::copy(filePath, filePath + ".backup", fs::copy_options::overwrite_existing);
            std::cout << "✓ Backup created successfully." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "✗ Backup failed: " << e.what() << std::endl;
    }
}

bool FileManager::restoreFromBackup() {
    try {
        if (fs::exists(filePath + ".backup")) {
            fs::copy(filePath + ".backup", filePath, fs::copy_options::overwrite_existing);
            std::cout << "✓ Restored from backup successfully." << std::endl;
            return true;
        }
    } catch (const std::exception& e) {
        std::cerr << "✗ Restore failed: " << e.what() << std::endl;
    }
    return false;
}

void FileManager::clearData() const {
    std::ofstream file(filePath, std::ios::trunc);
    file.close();
    std::cout << "✓ Data cleared successfully." << std::endl;
}

int FileManager::getRecordCount() const {
    std::ifstream file(filePath);
    if (!file.is_open()) return 0;

    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) count++;
    }
    file.close();
    return count;
}

// ==================== SETTERS AND GETTERS ====================
void FileManager::setFilePath(std::string path) {
    filePath = path;
}

std::string FileManager::getFilePath() const {
    return filePath;
}

// ==================== HELPER METHODS ====================
std::string FileManager::studentToCSV(const Student& student) const {
    std::stringstream ss;
    ss << student.getRollNo() << "|"
       << student.getName() << "|"
       << student.getEmail() << "|"
       << student.getSemesterNumber() << "|"
       << student.getCurrentCGPA() << "|"
       << student.getTotalCreditHours() << "|"
       << student.getNumberOfCourses() << "|";

    for (int i = 0; i < student.getNumberOfCourses(); i++) {
        const Course& course = student.getCourse(i);
        ss << course.getCourseCode() << ":"
           << course.getCourseName() << ":"
           << course.getCreditHours() << ":"
           << course.getAssignmentMarks() << ":"
           << course.getMidtermMarks() << ":"
           << course.getFinalMarks() << ":"
           << course.getProjectMarks() << ";";
    }
    ss << "\n";
    return ss.str();
}

Student FileManager::csvToStudent(const std::string& line) const {
    std::stringstream ss(line);
    std::string rollNo, name, email, semStr, cgpaStr, creditStr, courseCountStr;

    std::getline(ss, rollNo, '|');
    std::getline(ss, name, '|');
    std::getline(ss, email, '|');
    std::getline(ss, semStr, '|');
    std::getline(ss, cgpaStr, '|');
    std::getline(ss, creditStr, '|');
    std::getline(ss, courseCountStr, '|');

    Student student(rollNo, name, email);
    student.setSemesterNumber(std::stoi(semStr));
    student.setCurrentCGPA(std::stof(cgpaStr));
    student.setTotalCreditHours(std::stoi(creditStr));

    std::string coursesStr;
    std::getline(ss, coursesStr);

    std::stringstream coursesSS(coursesStr);
    std::string courseData;
    while (std::getline(coursesSS, courseData, ';')) {
        if (!courseData.empty()) {
            std::stringstream courseSS(courseData);
            std::string code, name, credits, assignment, midterm, final, project;

            std::getline(courseSS, code, ':');
            std::getline(courseSS, name, ':');
            std::getline(courseSS, credits, ':');
            std::getline(courseSS, assignment, ':');
            std::getline(courseSS, midterm, ':');
            std::getline(courseSS, final, ':');
            std::getline(courseSS, project, ':');

            Course course(code, name, std::stoi(credits));
            course.setAssignmentMarks(std::stof(assignment));
            course.setMidtermMarks(std::stof(midterm));
            course.setFinalMarks(std::stof(final));
            course.setProjectMarks(std::stof(project));

            student.addCourse(course);
        }
    }

    return student;
}

bool FileManager::directoryExists(const std::string& path) const {
    return fs::exists(path) && fs::is_directory(path);
}

void FileManager::createDirectory(const std::string& path) const {
    try {
        fs::create_directory(path);
    } catch (const std::exception& e) {
        std::cerr << "Error creating directory: " << e.what() << std::endl;
    }
}

// ==================== DISPLAY METHODS ====================
void FileManager::displayFileInfo() const {
    std::cout << "\nFile Information:" << std::endl;
    std::cout << "Path: " << filePath << std::endl;
    std::cout << "Exists: " << (fileExists() ? "Yes" : "No") << std::endl;
    std::cout << "Records: " << getRecordCount() << std::endl;
}
