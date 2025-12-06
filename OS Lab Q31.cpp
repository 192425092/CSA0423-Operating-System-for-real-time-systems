#include <stdio.h>

int main() {
    int n, f, i, j, k, index = 0, faults = 0;
    printf("Enter number of page references: ");
    scanf("%d", &n);

    int pages[n];
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int frame[f];
    for (i = 0; i < f; i++)
        frame[i] = -1;

    for (i = 0; i < n; i++) {
        int hit = 0;
        for (j = 0; j < f; j++) {
            if (frame[j] == pages[i]) {
                hit = 1;
                break;
            }
        }
        if (!hit) {
            frame[index] = pages[i];
            index = (index + 1) % f;
            faults++;
        }

        for (k = 0; k < f; k++) {
            if (frame[k] == -1) printf("- ");
            else printf("%d ", frame[k]);
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", faults);
    return 0;
}

