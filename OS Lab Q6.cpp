#include <stdio.h>

int main() {
    int n,i;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    int at[n], bt[n], pr[n], rem[n], ct[n], completed=0, time=0;
    for(i=0;i<n;i++){
        printf("Enter arrival time for P%d: ",i+1);
        scanf("%d",&at[i]);
        printf("Enter burst time for P%d: ",i+1);
        scanf("%d",&bt[i]);
        printf("Enter priority for P%d (smaller = higher): ",i+1);
        scanf("%d",&pr[i]);
        rem[i]=bt[i];
        ct[i]=0;
    }
    while(completed < n){
        int idx = -1;
        int best_pr = 1<<30;
        for(i=0;i<n;i++){
            if(at[i] <= time && rem[i] > 0){
                if(pr[i] < best_pr){
                    best_pr = pr[i];
                    idx = i;
                } else if(pr[i] == best_pr){
                    if(at[i] < at[idx]) idx = i;
                }
            }
        }
        if(idx == -1){
            time++;
        } else {
            rem[idx]--;
            time++;
            if(rem[idx] == 0){
                completed++;
                ct[idx] = time;
            }
        }
    }
    int tat[n], wt[n];
    float avg_tat=0, avg_wt=0;
    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_tat += tat[i];
        avg_wt += wt[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }
    avg_tat /= n;
    avg_wt /= n;
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
    printf("Average Waiting Time = %.2f\n", avg_wt);
    return 0;
}

