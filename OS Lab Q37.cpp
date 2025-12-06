#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, i, seek = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter disk request sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    for (i = 0; i < n; i++) {
        seek += abs(req[i] - head);
        head = req[i];
    }

    printf("Total Seek Time: %d\n", seek);

    return 0;
}

