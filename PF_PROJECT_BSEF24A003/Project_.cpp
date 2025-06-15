#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_COURSES 10
#define MAX_SEMESTERS 8

// Convert grade (A, B+, etc.) to grade points
float gradeToPoint(char grade[]) {
    if (strcmp(grade, "A") == 0) return 4.0f;
    else if (strcmp(grade, "A-") == 0) return 3.7f;
    else if (strcmp(grade, "B+") == 0) return 3.3f;
    else if (strcmp(grade, "B") == 0) return 3.0f;
    else if (strcmp(grade, "B-") == 0) return 2.7f;
    else if (strcmp(grade, "C+") == 0) return 2.3f;
    else if (strcmp(grade, "C") == 0) return 2.0f;
    else if (strcmp(grade, "D") == 0) return 1.0f;
    else return 0.0f; // F or invalid grade
}

// Display welcome message
void welcomeScreen() {
    printf("\n=============================================\n");
    printf("         *** PUCIT CGPA CALCULATOR ***       \n");
    printf("=============================================\n");
    printf("       Developed with love using basics      \n");
    printf("=============================================\n");
}

// Calculate GPA for a semester
float calculateSemesterGPA(int numCourses, int credits[], float gradePoints[], int* totalCredits) {
    float weightedSum = 0.0f;
    *totalCredits = 0;

    for (int i = 0; i < numCourses; i++) {
        weightedSum += gradePoints[i] * credits[i];
        *totalCredits += credits[i];
    }

    return (float)(weightedSum / (*totalCredits)); // Cast to float to avoid truncation
}

int main() {
    int totalSemesters;
    float semesterGPA[MAX_SEMESTERS];
    int semesterCredits[MAX_SEMESTERS];

    float totalNumerator = 0.0f;
    int totalDenominator = 0;

    welcomeScreen();

    printf("\nEnter total number of semesters (max 8): ");
    scanf_s("%d", &totalSemesters);

    if (totalSemesters <= 0 || totalSemesters > MAX_SEMESTERS) {
        printf("Invalid number of semesters. Exiting.\n");
        return 1;
    }

    for (int i = 0; i < totalSemesters; i++) {
        printf("\n------ Semester %d ------\n", i + 1);

        int numCourses;
        printf("Enter number of courses: ");
        scanf_s("%d", &numCourses);

        if (numCourses <= 0 || numCourses > MAX_COURSES) {
            printf("Invalid number of courses. Try again.\n");
            i--;
            continue;
        }

        int credits[MAX_COURSES];
        float gradePoints[MAX_COURSES];
        char gradeInput[5]; // Enough for "B+" and null character

        for (int j = 0; j < numCourses; j++) {
            printf("\nCourse %d:\n", j + 1);

            printf("  Enter credit hours: ");
            scanf_s("%d", &credits[j]);

            printf("  Enter grade (A, B+, C, etc.): ");
            scanf_s("%s", gradeInput, 5);  // Fixed: manual buffer size instead of _countof

            // Convert to uppercase for safety
            for (int k = 0; gradeInput[k]; k++) {
                gradeInput[k] = toupper(gradeInput[k]);
            }

            gradePoints[j] = gradeToPoint(gradeInput);
            printf("  Grade point = %.1f\n", gradePoints[j]);
        }

        int semesterTotalCredits = 0;
        semesterGPA[i] = calculateSemesterGPA(numCourses, credits, gradePoints, &semesterTotalCredits);
        semesterCredits[i] = semesterTotalCredits;

        printf("\nSemester %d GPA: %.2f\n", i + 1, semesterGPA[i]);
    }

    // Calculate CGPA
    for (int i = 0; i < totalSemesters; i++) {
        totalNumerator += semesterGPA[i] * semesterCredits[i];
        totalDenominator += semesterCredits[i];
    }

    float finalCGPA = (float)(totalNumerator / totalDenominator);

    // Display final results
    printf("\n=============================================\n");
    printf("                 RESULTS                     \n");
    printf("=============================================\n");

    for (int i = 0; i < totalSemesters; i++) {
        printf("Semester %d GPA: %.2f (Credits: %d)\n", i + 1, semesterGPA[i], semesterCredits[i]);
    }

    printf("\nFinal CGPA after %d semesters: %.2f\n", totalSemesters, finalCGPA);
    printf("Keep working hard. You are doing great!\n");
    printf("=============================================\n");

    return 0;
}

