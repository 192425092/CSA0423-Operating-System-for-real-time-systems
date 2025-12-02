#include <stdio.h>

#define MAX 20

struct Process {
    int pid;
    int bt;   // burst time
    int at;   // arrival time
    int pr;   // priority
    int wt;   // waiting time
    int tat;  // turnaround time
    int rt;   // remaining time
    int ct;   // completion time
};

int main() {
    struct Process p[MAX];
    int n, i, time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Burst Time, Arrival Time and Priority for P%d: ", p[i].pid);
        scanf("%d %d %d", &p[i].bt, &p[i].at, &p[i].pr);
        p[i].rt = p[i].bt; // remaining time initially = burst time
    }

    // Preemptive Priority Scheduling
    while (completed != n) {
        int idx = -1;
        int highest = -9999; // track highest priority

        // Find process with highest priority among arrived processes
        for (i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (p[i].pr > highest) { // larger number = higher priority
                    highest = p[i].pr;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].rt--; // execute for 1 unit
            time++;

            if (p[idx].rt == 0) {
                completed++;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                total_wt += p[idx].wt;
                total_tat += p[idx].tat;
            }
        } else {
            time++; // no process available, idle CPU
        }
    }

    // Print results
    printf("\nProcess\tBT\tAT\tPR\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].bt, p[i].at, p[i].pr, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
