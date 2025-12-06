#include <stdio.h>

int main() {
    int n, f, i;
    printf("Enter number of blocks in disk: ");
    scanf("%d", &n);

    int disk[n];
    for (i = 0; i < n; i++) disk[i] = -1;

    int indexBlock;
    printf("Enter index block number: ");
    scanf("%d", &indexBlock);

    disk[indexBlock] = 2;

    printf("Enter number of file blocks: ");
    scanf("%d", &f);

    int fileBlocks[f];
    printf("Enter the block numbers allocated to file:\n");
    for (i = 0; i < f; i++) {
        scanf("%d", &fileBlocks[i]);
        disk[fileBlocks[i]] = 1;
    }

    printf("\nIndexed Allocation:\n");
    for (i = 0; i < n; i++) {
        if (disk[i] == -1) printf("- ");
        else if (disk[i] == 2) printf("I ");
        else printf("F ");
    }
    printf("\n");

    printf("Index Block Contents:\n");
    for (i = 0; i < f; i++)
        printf("Index[%d] -> Block %d\n", i, fileBlocks[i]);

    return 0;
}

