#include <stdio.h>

int main() {
    int n, i, start;
    printf("Enter number of blocks in disk: ");
    scanf("%d", &n);

    int disk[n];
    for (i = 0; i < n; i++) disk[i] = -1;

    int len;
    printf("Enter starting block of file: ");
    scanf("%d", &start);
    printf("Enter length of file: ");
    scanf("%d", &len);

    if (start + len > n) {
        printf("Not enough space.\n");
        return 0;
    }

    for (i = start; i < start + len; i++)
        disk[i] = 1;

    printf("Sequential Allocation:\n");
    for (i = 0; i < n; i++) {
        if (disk[i] == -1) printf("- ");
        else printf("F ");
    }
    printf("\n");

    printf("Accessing file sequentially:\n");
    for (i = start; i < start + len; i++)
        printf("Reading block %d\n", i);

    return 0;
}

