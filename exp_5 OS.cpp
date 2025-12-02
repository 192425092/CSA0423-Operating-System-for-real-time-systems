#include <stdio.h>

#define MAX_PROCESSES 50

int main() {
    int n, i, j;

    int burst_time[MAX_PROCESSES];
    int priority[MAX_PROCESSES];
    int pid[MAX_PROCESSES];

    int waiting_time[MAX_PROCESSES];
    int turnaround_time[MAX_PROCESSES];

    int total_wt = 0;
    int total_tat = 0;

    // Read number of processes
    printf("Enter number of processes (1-%d): ", MAX_PROCESSES);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    // Read burst time and priority for each process
    printf("Enter burst time and priority for each process:\n");
    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("P%d Burst Time: ", pid[i]);
        if (scanf("%d", &burst_time[i]) != 1 || burst_time[i] < 0) {
            printf("Invalid burst time.\n");
            return 1;
        }
        printf("P%d Priority: ", pid[i]);
        if (scanf("%d", &priority[i]) != 1) {
            printf("Invalid priority.\n");
            return 1;
        }
    }

    // Sort by priority (non-preemptive)
    // Default: higher number = higher priority.
    // If you want smaller number = higher priority, change (priority[i] < priority[j]) to (priority[i] > priority[j]).
    for (i = 0; i < n - 1; i++) {
        int best = i;
        for (j = i + 1; j < n; j++) {
            if (priority[j] > priority[best]) { // change to < if smaller is higher
                best = j;
            }
        }
        if (best != i) {
            // swap pid
            int tpid = pid[i];
            pid[i] = pid[best];
            pid[best] = tpid;

            // swap burst_time
            int tbt = burst_time[i];
            burst_time[i] = burst_time[best];
            burst_time[best] = tbt;

            // swap priority
            int tpr = priority[i];
            priority[i] = priority[best];
            priority[best] = tpr;
        }
    }

    // Compute waiting times
    waiting_time[0] = 0;
    for (i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + burst_time[i - 1];
    }

    // Compute turnaround times
    for (i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + burst_time[i];
        total_wt += waiting_time[i];
        total_tat += turnaround_time[i];
    }

    // Output results
    printf("\nProcess\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t\t%d\t%d\n",
               pid[i], burst_time[i], priority[i], waiting_time[i], turnaround_time[i]);
    }

    // Averages
    printf("\nAverage Waiting Time = %.2f", (float) total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float) total_tat / n);

    // Optional: Gantt chart
    printf("\nGantt Chart (execution order):\n|");
    int current_time = 0;
    for (i = 0; i < n; i++) {
        printf(" P%d |", pid[i]);
        current_time += burst_time[i];
    }
    printf("\n0");
    current_time = 0;
    for (i = 0; i < n; i++) {
        current_time += burst_time[i];
        printf("   %d", current_time);
    }
    printf("\n");

    return 0;
}
