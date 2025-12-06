#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, disk, i, j, seek = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter request sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk);

    int temp[n], t = 0;
    for (i = 0; i < n; i++)
        temp[t++] = req[i];

    for (i = 0; i < t - 1; i++)
        for (j = 0; j < t - i - 1; j++)
            if (temp[j] > temp[j + 1]) {
                int c = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = c;
            }

    int pos = 0;
    for (i = 0; i < t; i++)
        if (temp[i] >= head) {
            pos = i;
            break;
        }

    for (i = pos; i < t; i++) {
        seek += abs(temp[i] - head);
        head = temp[i];
    }

    seek += abs((disk - 1) - head);
    head = 0;
    seek += (disk - 1);

    for (i = 0; i < pos; i++) {
        seek += abs(temp[i] - head);
        head = temp[i];
    }

    printf("Total Seek Time: %d\n", seek);

    return 0;
}

