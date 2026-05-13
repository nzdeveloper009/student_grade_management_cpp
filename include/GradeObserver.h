#ifndef GRADEOBSERVER_H
#define GRADEOBSERVER_H

#include <string>
#include <vector>
#include "Course.h"
#include "Constants.h"

// Observer Interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& courseName, float gpa, const std::string& category) = 0;
};

// Concrete Observer: Alert Notification
class AlertNotification : public Observer {
private:
    std::string observerName;

public:
    AlertNotification(std::string name = "Grade Alert System");
    void update(const std::string& courseName, float gpa, const std::string& category) override;
};

// Concrete Observer: Performance Logger
class PerformanceLogger : public Observer {
private:
    std::string observerName;

public:
    PerformanceLogger(std::string name = "Performance Logger");
    void update(const std::string& courseName, float gpa, const std::string& category) override;
};

// ==================== SUBJECT (Observable) ====================
class GradeSubject {
private:
    std::vector<Observer*> observers;

public:
    GradeSubject();
    ~GradeSubject();

    // Observer management
    void attach(Observer* observer);
    void detach(Observer* observer);
    void notify(const std::string& courseName, float gpa, const std::string& category);
};

// Grade Change Notifier
class GradeChangeNotifier {
private:
    static GradeChangeNotifier* instance;
    GradeSubject subject;

    GradeChangeNotifier();

public:
    static GradeChangeNotifier* getInstance();
    GradeChangeNotifier(const GradeChangeNotifier&) = delete;
    GradeChangeNotifier& operator=(const GradeChangeNotifier&) = delete;

    void subscribeLowGradeAlert();
    void subscribePerformanceLogger();
    void notifyGradeUpdate(const std::string& courseName, float gpa, const std::string& category);
    void checkAndNotify(const Course& course);
};

#endif
