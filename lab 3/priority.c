#include <stdio.h>

typedef struct {
    int pid, at, bt, ct, tat, wt, rt, priority;
    int completed;
} process;

void calculateAverages(process p[], int n) {
    float total_tat = 0, total_wt = 0;
    printf("\nPID\tPri\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].priority, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
}

int main() {
    int n, choice;
    printf("1. Non-Preemptive Priority\n2. Preemptive Priority\nSelect: ");
    scanf("%d", &choice);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT, BT, and Priority for P%d (Lower # = Higher Priority): ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].rt = p[i].bt;
        p[i].completed = 0;
    }

    int time = 0, completed_count = 0;

    switch (choice) {
        case 1: // Non-Preemptive
            while (completed_count < n) {
                int idx = -1;
                int highest_priority = 1e9; // Infinity

                for (int i = 0; i < n; i++) {
                    if (p[i].at <= time && p[i].completed == 0) {
                        if (p[i].priority < highest_priority) {
                            highest_priority = p[i].priority;
                            idx = i;
                        }
                    }
                }

                if (idx != -1) {
                    time += p[idx].bt;
                    p[idx].ct = time;
                    p[idx].tat = p[idx].ct - p[idx].at;
                    p[idx].wt = p[idx].tat - p[idx].bt;
                    p[idx].completed = 1;
                    completed_count++;
                } else {
                    time++;
                }
            }
            break;

        case 2: // Preemptive (Priority SRTF-style)
            while (completed_count < n) {
                int idx = -1;
                int highest_priority = 1e9;

                for (int i = 0; i < n; i++) {
                    if (p[i].at <= time && p[i].completed == 0) {
                        if (p[i].priority < highest_priority) {
                            highest_priority = p[i].priority;
                            idx = i;
                        }
                    }
                }

                if (idx != -1) {
                    p[idx].rt--;
                    time++;
                    if (p[idx].rt == 0) {
                        p[idx].ct = time;
                        p[idx].tat = p[idx].ct - p[idx].at;
                        p[idx].wt = p[idx].tat - p[idx].bt;
                        p[idx].completed = 1;
                        completed_count++;
                    }
                } else {
                    time++;
                }
            }
            break;

        default:
            printf("Invalid Choice\n");
            return 1;
    }

    calculateAverages(p, n);
    return 0;
}
