#include <stdio.h>

int main() {
    int n, f, i;
    printf("Enter number of blocks in disk: ");
    scanf("%d", &n);

    int disk[n];
    for (i = 0; i < n; i++) disk[i] = -1;

    printf("Enter number of blocks in file: ");
    scanf("%d", &f);

    int blocks[f], next[f];

    printf("Enter block numbers allocated to file:\n");
    for (i = 0; i < f; i++) {
        scanf("%d", &blocks[i]);
        disk[blocks[i]] = 1;
    }

    for (i = 0; i < f - 1; i++)
        next[i] = blocks[i + 1];
    next[f - 1] = -1;

    printf("\nLinked Allocation:\n");
    for (i = 0; i < n; i++) {
        if (disk[i] == -1) printf("- ");
        else printf("F ");
    }
    printf("\n");

    printf("\nFile Block Links:\n");
    for (i = 0; i < f; i++)
        printf("Block %d -> %d\n", blocks[i], next[i]);

    printf("\nFirst Block: %d\n", blocks[0]);
    printf("Last Block: %d\n", blocks[f - 1]);

    return 0;
}

