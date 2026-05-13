#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

// ==================== GRADING SCALE (University of Gujrat) ====================
// Grade thresholds in percentages
const float GRADE_AP_MIN = 84.5f;  // A+
const float GRADE_A_MIN = 79.5f;   // A
const float GRADE_BP_MIN = 74.5f;  // B+
const float GRADE_B_MIN = 69.5f;   // B
const float GRADE_BM_MIN = 64.5f;  // B-
const float GRADE_CP_MIN = 59.5f;  // C+
const float GRADE_C_MIN = 54.5f;   // C
const float GRADE_D_MIN = 49.5f;   // D
const float GRADE_F_MIN = 0.0f;    // F

// GPA Points for each grade
const float GPA_AP = 4.00f;
const float GPA_A = 3.70f;
const float GPA_BP = 3.40f;
const float GPA_B = 3.00f;
const float GPA_BM = 2.50f;
const float GPA_CP = 2.00f;
const float GPA_C = 1.50f;
const float GPA_D = 1.00f;
const float GPA_F = 0.00f;

// ==================== ASSESSMENT WEIGHTS ====================
const float ASSIGNMENT_WEIGHT = 0.20f;  // 20%
const float MIDTERM_WEIGHT = 0.20f;     // 20%
const float FINAL_WEIGHT = 0.40f;       // 40%
const float PROJECT_WEIGHT = 0.20f;     // 20%

// ==================== VALIDATION LIMITS ====================
const int MAX_STUDENTS = 500;
const int MAX_COURSES_PER_STUDENT = 10;
const int MIN_ASSIGNMENT_MARKS = 0;
const int MAX_ASSIGNMENT_MARKS = 100;
const int MIN_EXAM_MARKS = 0;
const int MAX_EXAM_MARKS = 100;
const int MIN_CREDIT_HOURS = 1;
const int MAX_CREDIT_HOURS = 5;

// ==================== NOTIFICATION THRESHOLDS ====================
const float LOW_GRADE_THRESHOLD = 2.0f;  // Alert if GPA < 2.0 (C+)
const float HIGH_GRADE_THRESHOLD = 3.7f; // Celebration if GPA >= 3.7 (A)

// ==================== FILE PATHS ====================
const std::string DATA_FILE = "data/students.csv";
const std::string BACKUP_FILE = "data/backup.csv";

#endif
