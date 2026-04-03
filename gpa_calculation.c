#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// -------------------------------------------------------
// Structure to store one course entry
// -------------------------------------------------------
typedef struct {
    char grade;       // Letter grade: A, B, C, D, F
    int  hours;       // Credit hours for the course
    char semester[10];// Semester: FALL, SPRING, SUMMER
    int  year;        // Year (e.g., 2025)
} Course;

// -------------------------------------------------------
// Convert a letter grade to grade points (4.0 scale)
// A=4.0, B=3.0, C=2.0, D=1.0, F=0.0
// -------------------------------------------------------
double gradeToPoints(char grade) {
    switch (toupper(grade)) {
        case 'A': return 4.0;
        case 'B': return 3.0;
        case 'C': return 2.0;
        case 'D': return 1.0;
        case 'F': return 0.0;
        default:  return -1.0; // Invalid grade
    }
}

// -------------------------------------------------------
// Convert semester string to uppercase for consistency
// -------------------------------------------------------
void toUpperStr(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = toupper(str[i]);
}

// -------------------------------------------------------
// Check if semester is valid (FALL, SPRING, or SUMMER)
// -------------------------------------------------------
int validSemester(char *sem) {
    return (strcmp(sem, "FALL")   == 0 ||
            strcmp(sem, "SPRING") == 0 ||
            strcmp(sem, "SUMMER") == 0);
}

// -------------------------------------------------------
// Check if year is reasonable (between 1900 and 2100)
// -------------------------------------------------------
int validYear(int year) {
    return (year >= 1900 && year <= 2100);
}

// -------------------------------------------------------
// Main function
// -------------------------------------------------------
int main() {
    // Array to store up to 100 courses (dynamic would be better,
    // but this keeps it simple for beginners)
    Course courses[100];
    int count = 0; // Number of courses entered

    printf("----> To quit entering grades, enter a blank line.\n");

    // -------------------------------------------------------
    // Loop to keep accepting course entries from the user
    // -------------------------------------------------------
    while (count < 100) {
        printf("Enter a letter grade and hours for a course with its year and semester: ");

        // Read the entire line of input
        char line[200];
        if (fgets(line, sizeof(line), stdin) == NULL) break;

        // If user just pressed Enter (blank line), stop
        if (line[0] == '\n' || line[0] == '\r') break;

        // Try to parse the input into grade, hours, semester, year
        char grade[5], semester[20];
        int hours, year;

        int parsed = sscanf(line, "%4s %d %19s %d", grade, &hours, semester, &year);

        // Validate: must have all 4 fields
        if (parsed != 4) {
            printf("  [!] Invalid input. Please enter like: A 3 FALL 2025\n");
            continue;
        }

        // Validate grade (must be single letter A-F)
        if (strlen(grade) != 1 || gradeToPoints(grade[0]) < 0) {
            printf("  [!] Invalid grade '%s'. Use A, B, C, D, or F.\n", grade);
            continue;
        }

        // Validate hours (must be positive)
        if (hours <= 0) {
            printf("  [!] Credit hours must be a positive number.\n");
            continue;
        }

        // Validate semester
        toUpperStr(semester);
        if (!validSemester(semester)) {
            printf("  [!] Invalid semester '%s'. Use FALL, SPRING, or SUMMER.\n", semester);
            continue;
        }

        // Validate year
        if (!validYear(year)) {
            printf("  [!] Invalid year '%d'. Please enter a year between 1900 and 2100.\n", year);
            continue;
        }

        // Store the valid course
        courses[count].grade = toupper(grade[0]);
        courses[count].hours = hours;
        strcpy(courses[count].semester, semester);
        courses[count].year = year;
        count++;
    }

    // -------------------------------------------------------
    // If no courses were entered, exit gracefully
    // -------------------------------------------------------
    if (count == 0) {
        printf("\nNo courses entered. Goodbye!\n");
        return 0;
    }

    // -------------------------------------------------------
    // Display the unofficial transcript
    // -------------------------------------------------------
    printf("\n-------------------------------------\n");
    printf("Unofficial Transcript\n");

    // We need to find all unique semester+year combinations
    // and print GPA for each one
    char printed[100][20]; // Track which semester+year we already printed
    int printedYears[100];
    int printedCount = 0;

    // Loop through all courses to find unique semesters
    for (int i = 0; i < count; i++) {
        int alreadyPrinted = 0;

        // Check if we already printed this semester+year
        for (int j = 0; j < printedCount; j++) {
            if (strcmp(printed[j], courses[i].semester) == 0 &&
                printedYears[j] == courses[i].year) {
                alreadyPrinted = 1;
                break;
            }
        }

        if (alreadyPrinted) continue;

        // Mark this semester+year as printed
        strcpy(printed[printedCount], courses[i].semester);
        printedYears[printedCount] = courses[i].year;
        printedCount++;

        // Calculate GPA for this semester
        double totalPoints = 0.0;
        int totalHours = 0;

        for (int j = 0; j < count; j++) {
            if (strcmp(courses[j].semester, courses[i].semester) == 0 &&
                courses[j].year == courses[i].year) {
                totalPoints += gradeToPoints(courses[j].grade) * courses[j].hours;
                totalHours  += courses[j].hours;
            }
        }

        double semGPA = (totalHours > 0) ? (totalPoints / totalHours) : 0.0;
        printf("%-6s %d (%d hours) %.3f\n",
               courses[i].semester, courses[i].year, totalHours, semGPA);
    }

    // -------------------------------------------------------
    // Calculate and display overall GPA
    // -------------------------------------------------------
    double overallPoints = 0.0;
    int overallHours = 0;

    for (int i = 0; i < count; i++) {
        overallPoints += gradeToPoints(courses[i].grade) * courses[i].hours;
        overallHours  += courses[i].hours;
    }

    double overallGPA = (overallHours > 0) ? (overallPoints / overallHours) : 0.0;

    printf("\n--\n");
    printf("Total credit hours: %d\n", overallHours);
    printf("Overall GPA: %.3f\n", overallGPA);
    printf("-------------------------------------\n");

    return 0;
}