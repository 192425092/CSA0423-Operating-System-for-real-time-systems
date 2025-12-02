#include <stdio.h>

#define MAX 20

struct Process {
    int pid;   // process id
    int bt;    // burst time
    int at;    // arrival time
    int wt;    // waiting time
    int tat;   // turnaround time
    int ct;    // completion time
};

int main() {
    struct Process p[MAX];
    int n, i, j, completed = 0, time = 0;
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Burst Time and Arrival Time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].bt, &p[i].at);
    }

    // Non-preemptive SJF scheduling
    while (completed != n) {
        int idx = -1;
        int min_bt = 9999;

        // Find process with shortest burst time among arrived processes
        for (i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].ct == 0) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
            completed++;
        } else {
            time++; // CPU idle if no process has arrived
        }
    }

    // Print results
    printf("\nProcess\tBT\tAT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].bt, p[i].at, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
