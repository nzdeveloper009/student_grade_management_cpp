#include "../include/GradeCalculator.h"
#include "../include/Constants.h"
#include <iostream>
#include <iomanip>
#include <cmath>

// ==================== STRATEGY IMPLEMENTATIONS ====================
float WeightedAverageStrategy::calculatePercentage(float assignment, float midterm, float final, float project) const {
    return (assignment * ASSIGNMENT_WEIGHT +
            midterm * MIDTERM_WEIGHT +
            final * FINAL_WEIGHT +
            project * PROJECT_WEIGHT);
}

std::string WeightedAverageStrategy::getStrategyName() const {
    return "Weighted Average (Standard)";
}

float AdjustedGradingStrategy::calculatePercentage(float assignment, float midterm, float final, float project) const {
    float basePercentage = (assignment * ASSIGNMENT_WEIGHT +
                           midterm * MIDTERM_WEIGHT +
                           final * FINAL_WEIGHT +
                           project * PROJECT_WEIGHT);
    // Add 5% curve if final exam is above 80
    if (final > 80.0f) {
        return std::min(basePercentage + 5.0f, 100.0f);
    }
    return basePercentage;
}

std::string AdjustedGradingStrategy::getStrategyName() const {
    return "Adjusted Grading (With Curve)";
}

// ==================== SINGLETON IMPLEMENTATION ====================
GradeCalculator* GradeCalculator::instance = nullptr;

GradeCalculator::GradeCalculator() : currentStrategy(nullptr) {
    currentStrategy = new WeightedAverageStrategy();
}

GradeCalculator* GradeCalculator::getInstance() {
    if (instance == nullptr) {
        instance = new GradeCalculator();
    }
    return instance;
}

GradeCalculator::~GradeCalculator() {
    if (currentStrategy != nullptr) {
        delete currentStrategy;
    }
}

void GradeCalculator::setGradingStrategy(GradingStrategy* strategy) {
    if (currentStrategy != nullptr) {
        delete currentStrategy;
    }
    currentStrategy = strategy;
    std::cout << "✓ Grading strategy changed to: " << currentStrategy->getStrategyName() << std::endl;
}

GradingStrategy* GradeCalculator::getCurrentStrategy() const {
    return currentStrategy;
}

// ==================== GRADE CALCULATION ====================
float GradeCalculator::calculatePercentage(float assignment, float midterm, float final, float project) const {
    if (currentStrategy == nullptr) {
        return 0.0f;
    }
    return currentStrategy->calculatePercentage(assignment, midterm, final, project);
}

std::string GradeCalculator::percentageToGrade(float percentage) const {
    if (percentage >= GRADE_AP_MIN) return "A+";
    if (percentage >= GRADE_A_MIN) return "A";
    if (percentage >= GRADE_BP_MIN) return "B+";
    if (percentage >= GRADE_B_MIN) return "B";
    if (percentage >= GRADE_BM_MIN) return "B-";
    if (percentage >= GRADE_CP_MIN) return "C+";
    if (percentage >= GRADE_C_MIN) return "C";
    if (percentage >= GRADE_D_MIN) return "D";
    return "F";
}

float GradeCalculator::percentageToGPA(float percentage) const {
    if (percentage >= GRADE_AP_MIN) return GPA_AP;
    if (percentage >= GRADE_A_MIN) return GPA_A;
    if (percentage >= GRADE_BP_MIN) return GPA_BP;
    if (percentage >= GRADE_B_MIN) return GPA_B;
    if (percentage >= GRADE_BM_MIN) return GPA_BM;
    if (percentage >= GRADE_CP_MIN) return GPA_CP;
    if (percentage >= GRADE_C_MIN) return GPA_C;
    if (percentage >= GRADE_D_MIN) return GPA_D;
    return GPA_F;
}

std::string GradeCalculator::percentageToCategory(float percentage) const {
    if (percentage >= GRADE_AP_MIN) return "Exceptional";
    if (percentage >= GRADE_A_MIN) return "Outstanding";
    if (percentage >= GRADE_BP_MIN) return "Excellent";
    if (percentage >= GRADE_B_MIN) return "Very Good";
    if (percentage >= GRADE_BM_MIN) return "Good";
    if (percentage >= GRADE_CP_MIN) return "Average";
    if (percentage >= GRADE_C_MIN) return "Satisfactory";
    if (percentage >= GRADE_D_MIN) return "Pass";
    return "Fail";
}

// ==================== VALIDATION ====================
bool GradeCalculator::isValidPercentage(float percentage) const {
    return percentage >= 0.0f && percentage <= 100.0f;
}

bool GradeCalculator::isValidMarks(float marks) const {
    return marks >= 0.0f && marks <= 100.0f;
}

// ==================== DISPLAY METHODS ====================
void GradeCalculator::displayGradingTable() const {
    std::cout << "\n" << std::string(90, '=') << std::endl;
    std::cout << "UNIVERSITY OF GUJRAT - GRADING SCALE" << std::endl;
    std::cout << std::string(90, '=') << std::endl;
    std::cout << std::left << std::setw(20) << "Marks (%)"
              << std::setw(15) << "Grade"
              << std::setw(15) << "GPA"
              << std::setw(20) << "Category" << std::endl;
    std::cout << std::string(90, '-') << std::endl;

    std::cout << std::left << std::setw(20) << "84.5 and above"
              << std::setw(15) << "A+"
              << std::setw(15) << "4.00"
              << std::setw(20) << "Exceptional" << std::endl;

    std::cout << std::left << std::setw(20) << "79.5 - 84.4"
              << std::setw(15) << "A"
              << std::setw(15) << "3.70"
              << std::setw(20) << "Outstanding" << std::endl;

    std::cout << std::left << std::setw(20) << "74.5 - 79.4"
              << std::setw(15) << "B+"
              << std::setw(15) << "3.40"
              << std::setw(20) << "Excellent" << std::endl;

    std::cout << std::left << std::setw(20) << "69.5 - 74.4"
              << std::setw(15) << "B"
              << std::setw(15) << "3.00"
              << std::setw(20) << "Very Good" << std::endl;

    std::cout << std::left << std::setw(20) << "64.5 - 69.4"
              << std::setw(15) << "B-"
              << std::setw(15) << "2.50"
              << std::setw(20) << "Good" << std::endl;

    std::cout << std::left << std::setw(20) << "59.5 - 64.4"
              << std::setw(15) << "C+"
              << std::setw(15) << "2.00"
              << std::setw(20) << "Average" << std::endl;

    std::cout << std::left << std::setw(20) << "54.5 - 59.4"
              << std::setw(15) << "C"
              << std::setw(15) << "1.50"
              << std::setw(20) << "Satisfactory" << std::endl;

    std::cout << std::left << std::setw(20) << "49.5 - 54.4"
              << std::setw(15) << "D"
              << std::setw(15) << "1.00"
              << std::setw(20) << "Pass" << std::endl;

    std::cout << std::left << std::setw(20) << "Below 49.5"
              << std::setw(15) << "F"
              << std::setw(15) << "0.00"
              << std::setw(20) << "Fail" << std::endl;

    std::cout << std::string(90, '=') << std::endl;
}

void GradeCalculator::displayAvailableStrategies() const {
    std::cout << "\nAvailable Grading Strategies:" << std::endl;
    std::cout << "  1. Weighted Average (Standard)" << std::endl;
    std::cout << "  2. Adjusted Grading (With Curve)" << std::endl;
}

std::string GradeCalculator::getGradeDescription(const std::string& grade) const {
    if (grade == "A+") return "Exceptional performance";
    if (grade == "A") return "Outstanding performance";
    if (grade == "B+") return "Excellent performance";
    if (grade == "B") return "Very Good performance";
    if (grade == "B-") return "Good performance";
    if (grade == "C+") return "Average performance";
    if (grade == "C") return "Satisfactory performance";
    if (grade == "D") return "Passing performance";
    return "Failing performance";
}
