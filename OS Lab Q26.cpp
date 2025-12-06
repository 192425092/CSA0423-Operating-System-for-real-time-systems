#include <stdio.h>
#include <stdlib.h>

int main() {
    int choice;
    char fname[100], data[500];
    FILE *fp;

    while (1) {
        printf("\nFile Management Menu\n");
        printf("1. Create File\n");
        printf("2. Write to File\n");
        printf("3. Read File\n");
        printf("4. Append to File\n");
        printf("5. Delete File\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter file name: ");
            scanf("%s", fname);
            fp = fopen(fname, "w");
            if (fp == NULL) printf("Error creating file.\n");
            else {
                printf("File created: %s\n", fname);
                fclose(fp);
            }

        } else if (choice == 2) {
            printf("Enter file name: ");
            scanf("%s", fname);
            fp = fopen(fname, "w");
            if (!fp) printf("File not found.\n");
            else {
                printf("Enter text: ");
                fflush(stdin);
                gets(data);
                fputs(data, fp);
                fclose(fp);
                printf("Data written.\n");
            }

        } else if (choice == 3) {
            printf("Enter file name: ");
            scanf("%s", fname);
            fp = fopen(fname, "r");
            if (!fp) printf("File not found.\n");
            else {
                printf("File content:\n");
                while (fgets(data, sizeof(data), fp)) {
                    printf("%s", data);
                }
                fclose(fp);
            }

        } else if (choice == 4) {
            printf("Enter file name: ");
            scanf("%s", fname);
            fp = fopen(fname, "a");
            if (!fp) printf("File not found.\n");
            else {
                printf("Enter text to append: ");
                fflush(stdin);
                gets(data);
                fputs(data, fp);
                fclose(fp);
                printf("Data appended.\n");
            }

        } else if (choice == 5) {
            printf("Enter file name to delete: ");
            scanf("%s", fname);
            if (remove(fname) == 0)
                printf("File deleted.\n");
            else
                printf("File not found.\n");

        } else if (choice == 6) {
            printf("Exiting.\n");
            break;

        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}

