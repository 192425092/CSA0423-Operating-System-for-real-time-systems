#include <stdio.h>

void printPerm(int p) {
    printf((p & 4) ? "r" : "-");
    printf((p & 2) ? "w" : "-");
    printf((p & 1) ? "x" : "-");
}

int main() {
    char file[50];
    int owner, group, others;

    printf("Enter file name: ");
    scanf("%s", file);

    printf("Enter owner permissions (0-7): ");
    scanf("%d", &owner);

    printf("Enter group permissions (0-7): ");
    scanf("%d", &group);

    printf("Enter others permissions (0-7): ");
    scanf("%d", &others);

    printf("\nFile: %s\n", file);

    printf("Owner  : ");
    printPerm(owner);
    printf("\n");

    printf("Group  : ");
    printPerm(group);
    printf("\n");

    printf("Others : ");
    printPerm(others);
    printf("\n");

    return 0;
}

