#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[30];
    float salary;
} Employee;

int main() {
    FILE *fp;
    int choice;
    Employee e;
    int id, pos;

    fp = fopen("employee.dat", "rb+");
    if (fp == NULL) fp = fopen("employee.dat", "wb+");
    if (fp == NULL) return 0;

    while (1) {
        printf("\nRandom Access File Menu\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee by ID\n");
        printf("3. Display All Employees\n");
        printf("4. Update Employee by ID\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) return 0;

        if (choice == 1) {
            printf("Enter ID: ");
            scanf("%d", &e.id);
            printf("Enter Name: ");
            scanf("%s", e.name);
            printf("Enter Salary: ");
            scanf("%f", &e.salary);
            fseek(fp, e.id * sizeof(Employee), SEEK_SET);
            fwrite(&e, sizeof(Employee), 1, fp);
            printf("Employee added.\n");

        } else if (choice == 2) {
            printf("Enter ID: ");
            scanf("%d", &id);
            fseek(fp, id * sizeof(Employee), SEEK_SET);
            fread(&e, sizeof(Employee), 1, fp);
            if (e.id == 0 && strlen(e.name) == 0) printf("No employee found.\n");
            else printf("ID: %d  Name: %s  Salary: %.2f\n", e.id, e.name, e.salary);

        } else if (choice == 3) {
            rewind(fp);
            pos = 0;
            while (fread(&e, sizeof(Employee), 1, fp)) {
                if (e.id != 0 && strlen(e.name) > 0)
                    printf("ID: %d  Name: %s  Salary: %.2f\n", e.id, e.name, e.salary);
                pos++;
            }

        } else if (choice == 4) {
            printf("Enter ID to update: ");
            scanf("%d", &id);
            fseek(fp, id * sizeof(Employee), SEEK_SET);
            fread(&e, sizeof(Employee), 1, fp);
            if (e.id == 0 && strlen(e.name) == 0) printf("No such employee.\n");
            else {
                printf("Enter new name: ");
                scanf("%s", e.name);
                printf("Enter new salary: ");
                scanf("%f", &e.salary);
                fseek(fp, id * sizeof(Employee), SEEK_SET);
                fwrite(&e, sizeof(Employee), 1, fp);
                printf("Employee updated.\n");
            }

        } else if (choice == 5) {
            fclose(fp);
            return 0;

        } else printf("Invalid choice.\n");
    }
}

