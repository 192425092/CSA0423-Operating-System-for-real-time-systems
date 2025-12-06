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
            int replace = -1, farthest = -1;
            for (j = 0; j < f; j++) {
                int found = 0;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            replace = j;
                        }
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    replace = j;
                    break;
                }
            }
            frame[replace] = pages[i];
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

