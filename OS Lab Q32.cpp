#include <stdio.h>

int main() {
    int n, f, i, j, k, faults = 0;
    printf("Enter number of page references: ");
    scanf("%d", &n);

    int pages[n];
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int frame[f], used[f];
    for (i = 0; i < f; i++) {
        frame[i] = -1;
        used[i] = 0;
    }

    for (i = 0; i < n; i++) {
        int hit = 0;
        for (j = 0; j < f; j++) {
            if (frame[j] == pages[i]) {
                hit = 1;
                used[j] = i;
                break;
            }
        }
        if (!hit) {
            int lru = 0;
            for (j = 1; j < f; j++) {
                if (used[j] < used[lru])
                    lru = j;
            }
            frame[lru] = pages[i];
            used[lru] = i;
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

