#include <stdio.h>

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int i, j;
    for(i=0;i<n;i++) allocation[i]=-1;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(blockSize[j] >= processSize[i]){
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation\nProcess\tSize\tBlock\n");
    for(i=0;i<n;i++){
        if(allocation[i] != -1) printf("P%d\t%d\tB%d\n", i+1, processSize[i], allocation[i]+1);
        else printf("P%d\t%d\tNot Allocated\n", i+1, processSize[i]);
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int i, j;
    for(i=0;i<n;i++) allocation[i] = -1;
    for(i=0;i<n;i++){
        int best = -1;
        for(j=0;j<m;j++){
            if(blockSize[j] >= processSize[i]){
                if(best == -1 || blockSize[j] < blockSize[best]) best = j;
            }
        }
        if(best != -1){
            allocation[i] = best;
            blockSize[best] -= processSize[i];
        }
    }
    printf("\nBest Fit Allocation\nProcess\tSize\tBlock\n");
    for(i=0;i<n;i++){
        if(allocation[i] != -1) printf("P%d\t%d\tB%d\n", i+1, processSize[i], allocation[i]+1);
        else printf("P%d\t%d\tNot Allocated\n", i+1, processSize[i]);
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int i, j;
    for(i=0;i<n;i++) allocation[i]=-1;
    for(i=0;i<n;i++){
        int worst = -1;
        for(j=0;j<m;j++){
            if(blockSize[j] >= processSize[i]){
                if(worst == -1 || blockSize[j] > blockSize[worst]) worst = j;
            }
        }
        if(worst != -1){
            allocation[i] = worst;
            blockSize[worst] -= processSize[i];
        }
    }
    printf("\nWorst Fit Allocation\nProcess\tSize\tBlock\n");
    for(i=0;i<n;i++){
        if(allocation[i] != -1) printf("P%d\t%d\tB%d\n", i+1, processSize[i], allocation[i]+1);
        else printf("P%d\t%d\tNot Allocated\n", i+1, processSize[i]);
    }
}

int main() {
    int m, n, i;
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    int blockSize1[m], blockSize2[m], blockSize3[m];
    for(i=0;i<m;i++){
        printf("Enter size of Block %d: ", i+1);
        scanf("%d", &blockSize1[i]);
        blockSize2[i] = blockSize1[i];
        blockSize3[i] = blockSize1[i];
    }
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int processSize[n];
    for(i=0;i<n;i++){
        printf("Enter size of Process %d: ", i+1);
        scanf("%d", &processSize[i]);
    }
    firstFit(blockSize1, m, processSize, n);
    bestFit(blockSize2, m, processSize, n);
    worstFit(blockSize3, m, processSize, n);
    return 0;
}

