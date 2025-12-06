#include <stdio.h>

int main() {
    int m, n, i, j;
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    int block[m], blockCopy[m];
    for (i = 0; i < m; i++) {
        printf("Enter size of Block %d: ", i+1);
        scanf("%d", &block[i]);
        blockCopy[i] = block[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int process[n], alloc[n];
    for (i = 0; i < n; i++) {
        printf("Enter size of Process %d: ", i+1);
        scanf("%d", &process[i]);
        alloc[i] = -1;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (blockCopy[j] >= process[i]) {
                alloc[i] = j;
                blockCopy[j] -= process[i];
                break;
            }
        }
    }

    printf("\nProcess\tSize\tBlock\n");
    for (i = 0; i < n; i++) {
        if (alloc[i] != -1)
            printf("P%d\t%d\tB%d\n", i+1, process[i], alloc[i] + 1);
        else
            printf("P%d\t%d\tNot Allocated\n", i+1, process[i]);
    }

    return 0;
}

