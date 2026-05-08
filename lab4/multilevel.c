#include <stdio.h>

#define MAX 20

struct process {
    int id;
    int at, bt, rt;
    int ct, tat, wt;
    int queue;
    int last_exec;
};

int main() {
    struct process p[MAX];
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter Queue(1-System 2-Interactive 3-Batch), AT, BT for P%d: ", i+1);
        scanf("%d %d %d", &p[i].queue, &p[i].at, &p[i].bt);

        p[i].id = i + 1;
        p[i].rt = p[i].bt;
        p[i].last_exec = -1;
    }

    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1;


        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {

                if (idx == -1) {
                    idx = i;
                }
                else if (p[i].queue < p[idx].queue) {
                    idx = i;
                }
                else if (p[i].queue == p[idx].queue) {

                    if (p[i].queue == 1 || p[i].queue == 2) {
                        if (p[i].last_exec < p[idx].last_exec) {
                            idx = i;
                        }
                    }


                    else if (p[i].queue == 3) {
                        if (p[i].at < p[idx].at) {
                            idx = i;
                        }
                    }
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }


        if (p[idx].queue == 1) {
            int tq = 2;

            if (p[idx].rt > tq) {
                p[idx].rt -= tq;
                time += tq;
            } else {
                time += p[idx].rt;
                p[idx].rt = 0;
                p[idx].ct = time;
                completed++;
            }
        }


        else if (p[idx].queue == 2) {
            int tq = 4;

            if (p[idx].rt > tq) {
                p[idx].rt -= tq;
                time += tq;
            } else {
                time += p[idx].rt;
                p[idx].rt = 0;
                p[idx].ct = time;
                completed++;
            }
        }


        else {
            time += p[idx].rt;
            p[idx].rt = 0;
            p[idx].ct = time;
            completed++;
        }


        p[idx].last_exec = time;
    }

    float totalTAT = 0, totalWT = 0;

    printf("\nProcess\tQueue\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        char *qname =
            (p[i].queue == 1) ? "System" :
            (p[i].queue == 2) ? "Inter" :
                                "Batch";

        printf("P%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, qname,
               p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);

        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);
    printf("Average Waiting Time    = %.2f\n", totalWT / n);

    return 0;
}
