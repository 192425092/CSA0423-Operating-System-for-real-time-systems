#include <stdio.h>

int main() {
    int n, tq, i;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rem[n], ct[n], tat[n], wt[n];
    for(i = 0; i < n; i++) {
        printf("Enter arrival time for P%d: ", i+1);
        scanf("%d", &at[i]);
        printf("Enter burst time for P%d: ", i+1);
        scanf("%d", &bt[i]);
        rem[i] = bt[i];
        ct[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, flag = 0;
    while(1) {
        flag = 1;
        for(i = 0; i < n; i++) {
            if(rem[i] > 0 && at[i] <= time) {
                flag = 0;
                if(rem[i] > tq) {
                    time += tq;
                    rem[i] -= tq;
                } else {
                    time += rem[i];
                    rem[i] = 0;
                    ct[i] = time;
                }
            }
        }
        if(flag == 1) break;
    }

    float avg_tat = 0, avg_wt = 0;
    for(i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
    printf("Average Waiting Time = %.2f\n", avg_wt);

    return 0;
}

