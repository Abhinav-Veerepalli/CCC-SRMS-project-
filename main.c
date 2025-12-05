

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUD_FILE "students.txt"
#define CRE_FILE  "credentials.txt"

char currentUser[50];
char currentRole[20];

int login() {
    char fileUser[50], filePass[50], fileRole[20];
    char inUser[50], inPass[50];

    printf("USERNAME: ");
    scanf("%s", inUser);
    printf("PASSWORD: ");
    scanf("%s", inPass);

    FILE *fp = fopen(CRE_FILE, "r");
    if (!fp) {
        printf("Credential file missing!\n");
        return 0;
    }

    while (fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) == 3) {
        if (strcmp(inUser, fileUser) == 0 && strcmp(inPass, filePass) == 0) {
            strcpy(currentUser, fileUser);
            strcpy(currentRole, fileRole);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void addStudent() {
    int roll;
    char name[50];
    float mark;

    printf("Roll: ");
    scanf("%d", &roll);
    printf("Name: ");
    scanf(" %[^\n]", name);
    printf("Mark: ");
    scanf("%f", &mark);

    FILE *fp = fopen(STUD_FILE, "a");
    fprintf(fp, "%d %s %.2f\n", roll, name, mark);
    fclose(fp);

    printf("Student added!\n");
}

void displayStudents() {
    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) {
        printf("No student file found!\n");
        return;
    }

    int roll;
    char name[50];
    float mark;

    printf("\nRoll\tName\tMark\n");
    printf("-------------------------\n");

    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        printf("%d\t%s\t%.2f\n", roll, name, mark);
    }

    fclose(fp);
}

void searchStudent() {
    int targetRoll, roll;
    char name[50];
    float mark;

    printf("Enter roll to search: ");
    scanf("%d", &targetRoll);

    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) {
        printf("No data found!\n");
        return;
    }

    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        if (roll == targetRoll) {
            printf("Found: %d %s %.2f\n", roll, name, mark);
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    printf("Student not found!\n");
}

void deleteStudent() {
    int delRoll, roll, found = 0;
    char name[50];
    float mark;

    printf("Enter roll to delete: ");
    scanf("%d", &delRoll);

    FILE *fp = fopen(STUD_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        if (roll != delRoll) {
            fprintf(temp, "%d %s %.2f\n", roll, name, mark);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found) printf("Student deleted!\n");
    else printf("Roll not found!\n");
}

void updateStudent() {
    int updateRoll, roll, found = 0;
    char name[50], newName[50];
    float mark, newMark;

    printf("Enter roll to update: ");
    scanf("%d", &updateRoll);

    FILE *fp = fopen(STUD_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        if (roll == updateRoll) {
            found = 1;
            printf("New Name: ");
            scanf(" %[^\n]", newName);
            printf("New Mark: ");
            scanf("%f", &newMark);
            fprintf(temp, "%d %s %.2f\n", roll, newName, newMark);
        } else {
            fprintf(temp, "%d %s %.2f\n", roll, name, mark);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found) printf("Student updated!\n");
    else printf("Roll not found!\n");
}

void adminMenu() {
    int c;
    while (1) {
        printf("\nADMIN MENU\n");
        printf("1. Add\n2. Display\n3. Search\n4. Update\n5. Delete\n6. Logout\n");
        scanf("%d", &c);

        switch (c) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            default: return;
        }
    }
}

void staffMenu() {
    int c;
    while (1) {
        printf("\nSTAFF MENU\n");
        printf("1. Add\n2. Display\n3. Search\n4. Update\n5. Logout\n");
        scanf("%d", &c);

        switch (c) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            default: return;
        }
    }
}

void guestMenu() {
    int c;
    while (1) {
        printf("\nGUEST MENU\n");
        printf("1. Display\n2. Search\n3. Logout\n");
        scanf("%d", &c);

        switch (c) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            default: return;
        }
    }
}

int main() {
    printf("STUDENT MANAGEMENT SYSTEM\n");

    if (!login()) {
        printf("Invalid login! Exiting...\n");
        return 0;
    }

    printf("Logged in as: %s\n", currentRole);

    if (strcmp(currentRole, "admin") == 0)
        adminMenu();
    else if (strcmp(currentRole, "staff") == 0)
        staffMenu();
    else
        guestMenu();

    return 0;
}
