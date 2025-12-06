#include <stdio.h>
#include <string.h>

#define MAX_FILES 100
#define NAME_LEN 50

int main() {
    char names[MAX_FILES][NAME_LEN];
    int sizes[MAX_FILES];
    int count = 0;
    int choice;

    while (1) {
        printf("\nSingle Level Directory Menu\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Search File\n");
        printf("4. Display All Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) return 0;

        if (choice == 1) {
            if (count == MAX_FILES) {
                printf("Directory full. Cannot create more files.\n");
                continue;
            }
            char fname[NAME_LEN];
            int fsize;
            printf("Enter file name (no spaces): ");
            scanf("%49s", fname);
            int exists = 0;
            for (int i = 0; i < count; i++) if (strcmp(names[i], fname) == 0) { exists = 1; break; }
            if (exists) {
                printf("File '%s' already exists.\n", fname);
                continue;
            }
            printf("Enter file size (in KB): ");
            scanf("%d", &fsize);
            strcpy(names[count], fname);
            sizes[count] = fsize;
            count++;
            printf("File '%s' created successfully.\n", fname);
        } else if (choice == 2) {
            if (count == 0) { printf("Directory is empty.\n"); continue; }
            char fname[NAME_LEN];
            printf("Enter file name to delete: ");
            scanf("%49s", fname);
            int idx = -1;
            for (int i = 0; i < count; i++) if (strcmp(names[i], fname) == 0) { idx = i; break; }
            if (idx == -1) { printf("File '%s' not found.\n", fname); continue; }
            for (int i = idx; i < count - 1; i++) {
                strcpy(names[i], names[i+1]);
                sizes[i] = sizes[i+1];
            }
            count--;
            printf("File '%s' deleted successfully.\n", fname);
        } else if (choice == 3) {
            if (count == 0) { printf("Directory is empty.\n"); continue; }
            char fname[NAME_LEN];
            printf("Enter file name to search: ");
            scanf("%49s", fname);
            int idx = -1;
            for (int i = 0; i < count; i++) if (strcmp(names[i], fname) == 0) { idx = i; break; }
            if (idx == -1) printf("File '%s' not found.\n", fname);
            else {
                printf("File found: Name = %s, Size = %d KB, Index = %d\n", names[idx], sizes[idx], idx);
            }
        } else if (choice == 4) {
            if (count == 0) { printf("Directory is empty.\n"); continue; }
            printf("\nFiles in Single Level Directory:\n");
            printf("Index\tName\t\tSize(KB)\n");
            for (int i = 0; i < count; i++) printf("%d\t%-15s\t%d\n", i, names[i], sizes[i]);
        } else if (choice == 5) {
            printf("Exiting.\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

