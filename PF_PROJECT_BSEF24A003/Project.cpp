#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Max limits
#define MAX_COURSES 10
#define MAX_SEMESTERS 8

// Function to convert letter grade to grade point
float gradeToPoint(char grade[]) {
    if (strcmp(grade, "A") == 0) return 4.0;
    else if (strcmp(grade, "A-") == 0) return 3.7;
    else if (strcmp(grade, "B+") == 0) return 3.3;
    else if (strcmp(grade, "B") == 0) return 3.0;
    else if (strcmp(grade, "B-") == 0) return 2.7;
    else if (strcmp(grade, "C+") == 0) return 2.3;
    else if (strcmp(grade, "C") == 0) return 2.0;
    else if (strcmp(grade, "D") == 0) return 1.0;
    else return 0.0; // F or invalid
}

void welcomeScreen() {
    printf("\n=============================================\n");
    printf("          *** PUCIT CGPA CALCULATOR ***      \n");
    printf("=============================================\n");
    printf("      Developed with ❤ using only basics     \n");
    printf("=============================================\n");
}

// Function to calculate GPA for one semester
float calculateSemesterGPA(int numCourses, int credits[], float gradePoints[], int* totalCredits) {
    float weightedSum = 0;
    int i;

    *totalCredits = 0;
    for (i = 0; i < numCourses; i++) {
        weightedSum += gradePoints[i] * credits[i];
        *totalCredits += credits[i];
    }

    return weightedSum / (*totalCredits);
}

int main() {
    int i, j, totalSemesters;
    int numCourses, credit;
    char gradeInput[5];
    float gradePoint;

    float semesterGPA[MAX_SEMESTERS];
    int semesterCredits[MAX_SEMESTERS];
    float totalCGPA_numerator = 0;
    int totalCGPA_denominator = 0;

    welcomeScreen();

    printf("\nEnter total number of semesters you want to enter (max 8): ");
    scanf_s("%d", &totalSemesters);

    if (totalSemesters <= 0 || totalSemesters > MAX_SEMESTERS) {
        printf("Invalid number of semesters. Exiting program.\n");
        return 0;
    }

    for (i = 0; i < totalSemesters; i++) {
        printf("\n---- Semester %d ----\n", i + 1);
        printf("Enter number of courses: ");
        scanf_s("%d", &numCourses);

        if (numCourses <= 0 || numCourses > MAX_COURSES) {
            printf("Invalid number of courses. Try again.\n");
            i--;
            continue;
        }

        int credits[MAX_COURSES];
        float gradePoints[MAX_COURSES];

        for (j = 0; j < numCourses; j++) {
            printf("Course %d:\n", j + 1);

            printf("  Enter credit hours: ");
            scanf_s("%d", &credit);
            credits[j] = credit;

            printf("  Enter grade (e.g., A, B+, C): ");
            scanf_s("%s", gradeInput);

            // Convert to uppercase for comparison
            for (int k = 0; gradeInput[k]; k++) {
                gradeInput[k] = toupper(gradeInput[k]);
            }

            gradePoint = gradeToPoint(gradeInput);
            gradePoints[j] = gradePoint;

            printf("  Grade Point = %.1f\n", gradePoint);
        }

        int semesterTotalCredits = 0;
        semesterGPA[i] = calculateSemesterGPA(numCourses, credits, gradePoints, &semesterTotalCredits);
        semesterCredits[i] = semesterTotalCredits;

        printf("\n✅ GPA for Semester %d: %.2f\n", i + 1, semesterGPA[i]);
    }

    for (i = 0; i < totalSemesters; i++) {
        totalCGPA_numerator += semesterGPA[i] * semesterCredits[i];
        totalCGPA_denominator += semesterCredits[i];
    }

    float finalCGPA = totalCGPA_numerator / totalCGPA_denominator;

    // Display results
    printf("\n=============================================\n");
    printf("               📊 RESULT SUMMARY              \n");
    printf("=============================================\n");

    for (i = 0; i < totalSemesters; i++) {
        printf("Semester %d GPA: %.2f (Credits: %d)\n", i + 1, semesterGPA[i], semesterCredits[i]);
    }

    printf("\n🎓 Final CGPA after %d semesters: %.2f\n", totalSemesters, finalCGPA);
    printf("Keep working hard. Success is near! 💪\n");
    printf("=============================================\n");

    return 0;
}
