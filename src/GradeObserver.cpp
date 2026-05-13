#include "../include/GradeObserver.h"
#include <iostream>
#include <iomanip>

// ==================== ALERT NOTIFICATION ====================
AlertNotification::AlertNotification(std::string name) : observerName(name) {}

void AlertNotification::update(const std::string& courseName, float gpa, const std::string& category) {
    std::cout << "\n" << std::string(70, '*') << std::endl;
    std::cout << "[" << observerName << "]" << std::endl;
    std::cout << std::string(70, '*') << std::endl;

    if (gpa < LOW_GRADE_THRESHOLD) {
        std::cout << "⚠️  WARNING - Low Grade Alert!" << std::endl;
        std::cout << "Course: " << courseName << std::endl;
        std::cout << "GPA: " << std::fixed << std::setprecision(2) << gpa << " (" << category << ")" << std::endl;
        std::cout << "Action: Please consider visiting your instructor for guidance." << std::endl;
    } else if (gpa >= HIGH_GRADE_THRESHOLD) {
        std::cout << "🎉 Congratulations! Excellent Performance!" << std::endl;
        std::cout << "Course: " << courseName << std::endl;
        std::cout << "GPA: " << std::fixed << std::setprecision(2) << gpa << " (" << category << ")" << std::endl;
        std::cout << "Keep up the great work!" << std::endl;
    }

    std::cout << std::string(70, '*') << std::endl;
}

// ==================== PERFORMANCE LOGGER ====================
PerformanceLogger::PerformanceLogger(std::string name) : observerName(name) {}

void PerformanceLogger::update(const std::string& courseName, float gpa, const std::string& category) {
    std::cout << "\n[LOG] " << observerName << " - Grade Update" << std::endl;
    std::cout << "  Course: " << courseName << std::endl;
    std::cout << "  GPA: " << std::fixed << std::setprecision(2) << gpa << std::endl;
    std::cout << "  Category: " << category << std::endl;
}

// ==================== GRADE SUBJECT ====================
GradeSubject::GradeSubject() {}

GradeSubject::~GradeSubject() {
    for (auto observer : observers) {
        delete observer;
    }
    observers.clear();
}

void GradeSubject::attach(Observer* observer) {
    if (observer != nullptr) {
        observers.push_back(observer);
    }
}

void GradeSubject::detach(Observer* observer) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == observer) {
            observers.erase(it);
            delete observer;
            break;
        }
    }
}

void GradeSubject::notify(const std::string& courseName, float gpa, const std::string& category) {
    for (auto observer : observers) {
        observer->update(courseName, gpa, category);
    }
}

// ==================== GRADE CHANGE NOTIFIER (SINGLETON) ====================
GradeChangeNotifier* GradeChangeNotifier::instance = nullptr;

GradeChangeNotifier::GradeChangeNotifier() {}

GradeChangeNotifier* GradeChangeNotifier::getInstance() {
    if (instance == nullptr) {
        instance = new GradeChangeNotifier();
    }
    return instance;
}

void GradeChangeNotifier::subscribeLowGradeAlert() {
    subject.attach(new AlertNotification("Low Grade Alert System"));
}

void GradeChangeNotifier::subscribePerformanceLogger() {
    subject.attach(new PerformanceLogger("Academic Performance Logger"));
}

void GradeChangeNotifier::notifyGradeUpdate(const std::string& courseName, float gpa, const std::string& category) {
    subject.notify(courseName, gpa, category);
}

void GradeChangeNotifier::checkAndNotify(const Course& course) {
    float gpa = course.getGradePoint();
    std::string category = course.getCategory();
    std::string courseName = course.getCourseName();

    if (gpa < LOW_GRADE_THRESHOLD || gpa >= HIGH_GRADE_THRESHOLD) {
        notifyGradeUpdate(courseName, gpa, category);
    }
}
