#include <stdio.h>

#define MAX 20

struct Process {
    int pid;   // process id
    int bt;    // burst time
    int at;    // arrival time
    int rt;    // remaining time
    int wt;    // waiting time
    int tat;   // turnaround time
};

int main() {
    struct Process p[MAX];
    int n, i, time_quantum;
    int time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Burst Time and Arrival Time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].bt, &p[i].at);
        p[i].rt = p[i].bt; // remaining time initially = burst time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);

    // Round Robin Scheduling
    while (completed != n) {
        int done = 1;
        for (i = 0; i < n; i++) {
            if (p[i].rt > 0 && p[i].at <= time) {
                done = 0;
                if (p[i].rt > time_quantum) {
                    time += time_quantum;
                    p[i].rt -= time_quantum;
                } else {
                    time += p[i].rt;
                    p[i].wt = time - p[i].bt - p[i].at;
                    p[i].tat = time - p[i].at;
                    p[i].rt = 0;
                    completed++;
                    total_wt += p[i].wt;
                    total_tat += p[i].tat;
                }
            }
        }
        if (done) {
            time++; // CPU idle if no process is ready
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
