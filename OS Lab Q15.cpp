#include <stdio.h>
#include <string.h>

#define MAX_USERS 20
#define MAX_FILES 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int size;
} File;

typedef struct {
    char username[NAME_LEN];
    File files[MAX_FILES];
    int file_count;
} UserDir;

UserDir users[MAX_USERS];
int user_count = 0;

int find_user(const char *name) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, name) == 0) return i;
    }
    return -1;
}

int find_file_in_user(int uid, const char *fname) {
    for (int i = 0; i < users[uid].file_count; i++) {
        if (strcmp(users[uid].files[i].name, fname) == 0) return i;
    }
    return -1;
}

void create_user() {
    if (user_count == MAX_USERS) {
        printf("Maximum user directories reached.\n");
        return;
    }
    char name[NAME_LEN];
    printf("Enter user directory name (no spaces): ");
    scanf("%49s", name);
    if (find_user(name) != -1) {
        printf("User directory '%s' already exists.\n", name);
        return;
    }
    strcpy(users[user_count].username, name);
    users[user_count].file_count = 0;
    user_count++;
    printf("User directory '%s' created.\n", name);
}

void create_file() {
    if (user_count == 0) {
        printf("No user directories exist. Create one first.\n");
        return;
    }
    char uname[NAME_LEN], fname[NAME_LEN];
    int fsize;
    printf("Enter user directory name: ");
    scanf("%49s", uname);
    int uid = find_user(uname);
    if (uid == -1) {
        printf("User directory '%s' not found.\n", uname);
        return;
    }
    if (users[uid].file_count == MAX_FILES) {
        printf("User directory full.\n");
        return;
    }
    printf("Enter file name (no spaces): ");
    scanf("%49s", fname);
    if (find_file_in_user(uid, fname) != -1) {
        printf("File '%s' already exists in '%s'.\n", fname, uname);
        return;
    }
    printf("Enter file size (KB): ");
    scanf("%d", &fsize);
    strcpy(users[uid].files[users[uid].file_count].name, fname);
    users[uid].files[users[uid].file_count].size = fsize;
    users[uid].file_count++;
    printf("File '%s' created in '%s'.\n", fname, uname);
}

void delete_file() {
    if (user_count == 0) {
        printf("No user directories exist.\n");
        return;
    }
    char uname[NAME_LEN], fname[NAME_LEN];
    printf("Enter user directory name: ");
    scanf("%49s", uname);
    int uid = find_user(uname);
    if (uid == -1) {
        printf("User directory '%s' not found.\n", uname);
        return;
    }
    if (users[uid].file_count == 0) {
        printf("No files in '%s'.\n", uname);
        return;
    }
    printf("Enter file name to delete: ");
    scanf("%49s", fname);
    int fid = find_file_in_user(uid, fname);
    if (fid == -1) {
        printf("File '%s' not found in '%s'.\n", fname, uname);
        return;
    }
    for (int i = fid; i < users[uid].file_count - 1; i++) {
        users[uid].files[i] = users[uid].files[i+1];
    }
    users[uid].file_count--;
    printf("File '%s' deleted from '%s'.\n", fname, uname);
}

void search_file() {
    if (user_count == 0) {
        printf("No user directories exist.\n");
        return;
    }
    char fname[NAME_LEN];
    printf("Enter file name to search: ");
    scanf("%49s", fname);
    int found = 0;
    for (int i = 0; i < user_count; i++) {
        int fid = find_file_in_user(i, fname);
        if (fid != -1) {
            printf("Found '%s' in '%s' (Size: %d KB)\n", fname, users[i].username, users[i].files[fid].size);
            found = 1;
        }
    }
    if (!found) printf("File '%s' not found in any user directory.\n", fname);
}

void display_user() {
    if (user_count == 0) {
        printf("No user directories exist.\n");
        return;
    }
    char uname[NAME_LEN];
    printf("Enter user directory name: ");
    scanf("%49s", uname);
    int uid = find_user(uname);
    if (uid == -1) {
        printf("User directory '%s' not found.\n", uname);
        return;
    }
    if (users[uid].file_count == 0) {
        printf("No files in '%s'.\n", uname);
        return;
    }
    printf("\nFiles in '%s':\n", uname);
    printf("Index\tName\t\tSize(KB)\n");
    for (int i = 0; i < users[uid].file_count; i++) {
        printf("%d\t%-15s\t%d\n", i, users[uid].files[i].name, users[uid].files[i].size);
    }
}

void display_all() {
    if (user_count == 0) {
        printf("No user directories exist.\n");
        return;
    }
    for (int i = 0; i < user_count; i++) {
        printf("\nDirectory: %s\n", users[i].username);
        if (users[i].file_count == 0) {
            printf("  (empty)\n");
            continue;
        }
        printf("  Index\tName\t\tSize(KB)\n");
        for (int j = 0; j < users[i].file_count; j++) {
            printf("  %d\t%-15s\t%d\n", j, users[i].files[j].name, users[i].files[j].size);
        }
    }
}

int main() {
    int choice;
    while (1) {
        printf("\nTwo-Level Directory Menu\n");
        printf("1. Create User Directory\n");
        printf("2. Create File in User Directory\n");
        printf("3. Delete File from User Directory\n");
        printf("4. Search File (across all directories)\n");
        printf("5. Display Files in a User Directory\n");
        printf("6. Display All Directories and Files\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) return 0;
        if (choice == 1) create_user();
        else if (choice == 2) create_file();
        else if (choice == 3) delete_file();
        else if (choice == 4) search_file();
        else if (choice == 5) display_user();
        else if (choice == 6) display_all();
        else if (choice == 7) { printf("Exiting.\n"); break; }
        else printf("Invalid choice. Try again.\n");
    }
    return 0;
}

