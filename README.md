# Student Grade Management System

## Project Overview
A comprehensive C++ application for managing student grades, calculating GPA/CGPA, and generating academic reports. This project demonstrates professional software engineering practices including **Object-Oriented Programming (OOP)**, **SOLID principles**, and **Design Patterns**.

## Key Features

### ✨ Core Functionality
- **Student Management**: Add, update, delete, and view student information
- **Course Management**: Enroll students in courses with dynamic course limits
- **Grade Calculation**: Automatic GPA/CGPA calculation using University of Gujrat grading scale
- **Assessment Tracking**: Support for Assignments (20%), Mid-term (20%), Final Exam (40%), and Project (20%)
- **Report Generation**: Multiple report types including transcripts, semester summaries, and progress reports
- **Data Persistence**: Save/load student data with backup functionality

### 🎓 University of Gujrat Grading Scale
| Marks (%) | Grade | GPA | Category |
|-----------|-------|-----|----------|
| 84.5+ | A+ | 4.00 | Exceptional |
| 79.5-84.4 | A | 3.70 | Outstanding |
| 74.5-79.4 | B+ | 3.40 | Excellent |
| 69.5-74.4 | B | 3.00 | Very Good |
| 64.5-69.4 | B- | 2.50 | Good |
| 59.5-64.4 | C+ | 2.00 | Average |
| 54.5-59.4 | C | 1.50 | Satisfactory |
| 49.5-54.4 | D | 1.00 | Pass |
| <49.5 | F | 0.00 | Fail |

## Programming Concepts Demonstrated

### Object-Oriented Programming (OOP)
- ✓ Classes and Objects
- ✓ Encapsulation (Public/Private/Protected)
- ✓ Inheritance (Base and Derived Classes)
- ✓ Polymorphism (Virtual Functions, Method Overriding)
- ✓ Abstraction (Abstract Base Classes)
- ✓ Constructors and Destructors
- ✓ Operator Overloading

### SOLID Principles
- **S**ingle Responsibility: Each class has one reason to change
- **O**pen/Closed: Classes open for extension, closed for modification
- **L**iskov Substitution: Derived classes can substitute base classes
- **I**nterface Segregation: Client-specific interfaces
- **D**ependency Inversion: Depend on abstractions, not concretions

### Design Patterns
1. **Singleton Pattern** - GradeCalculator (ensures only one instance)
2. **Strategy Pattern** - Different grading strategies (Weighted Average, Adjusted)
3. **Factory Pattern** - ReportGenerator creates different report types
4. **Observer Pattern** - GradeObserver for grade notifications
5. **Facade Pattern** - ReportManager simplifies complex operations

## Project Structure
```
StudentGradeCalculator/
├── include/              # Header files
│   ├── Constants.h       # Grading constants and thresholds
│   ├── Course.h          # Course class definition
│   ├── Student.h         # Student class definition
│   ├── GradeCalculator.h # Singleton + Strategy pattern
│   ├── ReportGenerator.h # Factory pattern
│   ├── GradeObserver.h   # Observer pattern
│   └── FileManager.h     # File I/O management
├── src/                  # Implementation files
│   ├── main.cpp          # Menu-driven interface
│   ├── Course.cpp
│   ├── Student.cpp
│   ├── GradeCalculator.cpp
│   ├── ReportGenerator.cpp
│   ├── GradeObserver.cpp
│   └── FileManager.cpp
├── bin/                  # Compiled executable
├── data/                 # Student data storage
├── Makefile             # Build configuration
└── README.md            # This file
```

## Class Hierarchy & Relationships

### Core Classes

#### 1. **Course Class**
- Manages individual course information and grades
- Tracks: Assignment marks, Midterm marks, Final marks, Project marks
- Methods: Calculate percentage, get grade, get GPA points

#### 2. **Student Class**
- Contains multiple courses
- Calculates semester GPA and cumulative GPA (CGPA)
- Tracks: Roll Number, Name, Email, CGPA, Credit Hours

#### 3. **GradeCalculator (Singleton + Strategy)**
- Single instance for entire application
- Supports multiple grading strategies
- Converts percentage → Grade → GPA
- Uses University of Gujrat grading table

#### 4. **ReportGenerator (Factory Pattern)**
- Creates different types of reports
- Report Types:
  - TranscriptReport
  - SemesterGradeReport
  - CGPAProgressReport
  - DetailedAnalysisReport

#### 5. **GradeObserver (Observer Pattern)**
- Notifies on low grades (GPA < 2.0)
- Celebrates high grades (GPA ≥ 3.7)
- AlertNotification & PerformanceLogger observers

#### 6. **FileManager**
- Saves/loads student data to CSV
- Backup and restore functionality
- Directory management

## Compilation & Execution

### Prerequisites
- C++17 compatible compiler (g++, clang, MSVC)
- Standard C++ library with filesystem support

### Using Makefile
```bash
cd ProjectFolder
make all      # Compile the project
make run      # Compile and run
make clean    # Remove build artifacts
```

### Manual Compilation (g++)
```bash
g++ -std=c++17 -Wall -I. src/main.cpp src/Course.cpp src/Student.cpp \
    src/GradeCalculator.cpp src/ReportGenerator.cpp src/GradeObserver.cpp \
    src/FileManager.cpp -o bin/StudentGradeCalculator -lstdc++fs
```

### Running the Application
```bash
./bin/StudentGradeCalculator        # Linux/Mac
bin\StudentGradeCalculator.exe      # Windows
```

## Usage Guide

### Main Menu Options
1. **Student Management** - Add, update, delete, view students
2. **Course Management** - Manage courses and enter marks
3. **Generate Reports** - Create academic reports
4. **Settings & Utilities** - Change grading strategy, backup data
5. **Save & Exit** - Save all changes and exit
0. **Exit Without Saving** - Exit without saving

### Workflow Example
1. Add a new student with Roll Number, Name, Email
2. Enter optional CGPA and credit hours from previous semesters
3. Add courses (up to 10 per student)
4. Enter assessment marks for each course
5. Generate reports (transcript, grade report, CGPA progress)
6. Save all data to file

## Assessment Component Calculation
```
Total Marks = (Assignment × 20%) + (Midterm × 20%) + 
              (Final Exam × 40%) + (Project Work × 20%)
```

## Example Calculation
```
Assignment: 85/100
Midterm: 78/100
Final Exam: 92/100
Project: 88/100

Total = (85 × 0.20) + (78 × 0.20) + (92 × 0.40) + (88 × 0.20)
      = 17 + 15.6 + 36.8 + 17.6
      = 87% → Grade: A (GPA: 3.70) → Outstanding
```

## Data Persistence

### File Format
Student data is stored in CSV format with pipe (|) delimiters:
```
RollNo|Name|Email|Semester|CGPA|CreditHours|NumCourses|CourseData...
```

### Backup & Restore
- Automatic backup creation: `students.csv.backup`
- Restore lost data from backup file
- Located in `data/` directory

## Command Reference

### For Students
```
add new student      → Enroll a new student
update student       → Modify student information
view courses         → See enrolled courses and grades
generate report      → Download academic transcript
```

### For Administrators
```
list all students    → View all enrolled students
backup data          → Create data backup
restore backup       → Recover from backup
change grading       → Switch grading strategy
```

## Error Handling
- Input validation for all numerical values
- Email format validation
- Course code uniqueness checking
- File I/O error handling with user feedback
- Memory management with proper cleanup

## System Requirements
- **OS**: Windows, Linux, macOS
- **Compiler**: GCC 7+, Clang 5+, MSVC 2017+
- **RAM**: 50 MB minimum
- **Storage**: 10 MB for executable and data

## Future Enhancements
- GUI version using Qt or wxWidgets
- Database integration (SQLite, MySQL)
- Web interface using web technologies
- Mobile app for student access
- Automated email notifications
- Grade prediction analytics

## Author
[SYED NOKHAIZ AL HASSAN] - APP DEVELOEPER - UNIVERSITY OF GUJRAT

## License
Educational Use Only

MIT License

Copyright (c) 2026 Syed Nokhaiz Al Hassan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Support
For questions or issues, refer to the included documentation files:
- `Project_Documentation.docx` - Detailed explanation
- `Project_Presentation.pptx` - Visual presentation
---

**Happy Learning! 🎓**
