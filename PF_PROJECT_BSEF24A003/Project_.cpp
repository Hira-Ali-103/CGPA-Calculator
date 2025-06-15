#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_COURSES 10
#define MAX_SEMESTERS 8

float gradeToPoint(char grade[]) {
    if (strcmp(grade, "A") == 0) return 4.0;
    else if (strcmp(grade, "A-") == 0) return 3.7;
    else if (strcmp(grade, "B+") == 0) return 3.3;
    else if (strcmp(grade, "B") == 0) return 3.0;
    else if (strcmp(grade, "B-") == 0) return 2.7;
    else if (strcmp(grade, "C+") == 0) return 2.3;
    else if (strcmp(grade, "C") == 0) return 2.0;
    else if (strcmp(grade, "C-") == 0) return 1.7;
    else if (strcmp(grade, "D+") == 0) return 1.3;
    else if (strcmp(grade, "D") == 0) return 1.0;
    else return 0.0;
}

void welcomeScreen() {
    printf("\n=============================================\n");
    printf("         *** PUCIT CGPA CALCULATOR ***       \n");
    printf("=============================================\n");
}


float calculateSemesterGPA(int numCourses, float credits[], float gradePoints[], float* totalCredits) {
    float weightedSum = 0.0;
    *totalCredits = 0;
    for (int i = 0; i < numCourses; i++) {
        weightedSum += gradePoints[i] * credits[i];
        *totalCredits += credits[i];  
    }
    return weightedSum / (*totalCredits);
}


int main() {
    int totalSemesters;
    float semesterGPA[MAX_SEMESTERS];
    float semesterCredits[MAX_SEMESTERS];


    float totalNumerator = 0.0;
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

        float credits[MAX_COURSES];
        float gradePoints[MAX_COURSES];
        char gradeInput[5];

        for (int j = 0; j < numCourses; j++) {
            printf("\nCourse %d:\n", j + 1);

            printf("  Enter credit hours: ");
            scanf_s("%f", &credits[j]);

            printf("  Enter grade (A, B+, A-, etc.): ");
            scanf_s("%s", gradeInput, 5);

            for (int k = 0; gradeInput[k]; k++) {
                gradeInput[k] = toupper(gradeInput[k]);
            }

            gradePoints[j] = gradeToPoint(gradeInput);
            printf("  Grade point = %.1f\n", gradePoints[j]);
        }

        float semesterTotalCredits = 0;
        semesterGPA[i] = calculateSemesterGPA(numCourses, credits, gradePoints, &semesterTotalCredits);
        semesterCredits[i] = semesterTotalCredits;


        printf("\nSemester %d GPA: %.2f\n", i + 1, semesterGPA[i]);
    }

    for (int i = 0; i < totalSemesters; i++) {
        totalNumerator += semesterGPA[i] * semesterCredits[i];
        totalDenominator += semesterCredits[i];
    }

    float finalCGPA = (float)(totalNumerator / totalDenominator);

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