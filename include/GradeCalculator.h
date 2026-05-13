#ifndef GRADECALCULATOR_H
#define GRADECALCULATOR_H

#include <string>

// Abstract Strategy Interface for different grading schemes
class GradingStrategy {
public:
    virtual ~GradingStrategy() = default;
    virtual float calculatePercentage(float assignment, float midterm, float final, float project) const = 0;
    virtual std::string getStrategyName() const = 0;
};

// Concrete Strategy: Standard Weighted Average
class WeightedAverageStrategy : public GradingStrategy {
public:
    float calculatePercentage(float assignment, float midterm, float final, float project) const override;
    std::string getStrategyName() const override;
};

// Concrete Strategy: Adjusted Grading (with curve)
class AdjustedGradingStrategy : public GradingStrategy {
public:
    float calculatePercentage(float assignment, float midterm, float final, float project) const override;
    std::string getStrategyName() const override;
};

// ==================== SINGLETON PATTERN ====================
class GradeCalculator {
private:
    static GradeCalculator* instance;
    GradingStrategy* currentStrategy;

    // Private constructor for Singleton
    GradeCalculator();

public:
    // Delete copy constructor and assignment operator
    GradeCalculator(const GradeCalculator&) = delete;
    GradeCalculator& operator=(const GradeCalculator&) = delete;

    // Get singleton instance
    static GradeCalculator* getInstance();

    // Destructor
    ~GradeCalculator();

    // Strategy management
    void setGradingStrategy(GradingStrategy* strategy);
    GradingStrategy* getCurrentStrategy() const;

    // Grade calculation
    float calculatePercentage(float assignment, float midterm, float final, float project) const;
    std::string percentageToGrade(float percentage) const;
    float percentageToGPA(float percentage) const;
    std::string percentageToCategory(float percentage) const;

    // Validation
    bool isValidPercentage(float percentage) const;
    bool isValidMarks(float marks) const;

    // Utility methods
    void displayGradingTable() const;
    void displayAvailableStrategies() const;
    std::string getGradeDescription(const std::string& grade) const;
};

#endif
