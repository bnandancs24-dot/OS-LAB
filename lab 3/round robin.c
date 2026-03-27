#include <stdio.h>

typedef struct  {
    int pid,at,bt,ct,tat,wt,rt;
} process;

int main() {
    int n, qt;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter quantum time: ");
    scanf("%d", &qt);

    process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter AT and BT of P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt; // initialize remaining time
    }

    int time = 0, completed = 0;
    int queue[100], front = 0, rear = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    // enqueue first process
    queue[rear++] = 0;
    visited[0] = 1;

    while (completed < n) {
        int idx = queue[front++];
        if (front == 100) front = 0;

        if (p[idx].rt > qt) {
            time += qt;
            p[idx].rt -= qt;
        } else {
            time += p[idx].rt;
            p[idx].rt = 0;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }

        // enqueue new processes that have arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && visited[i] == 0) {
                queue[rear++] = i;
                if (rear == 100) rear = 0;
                visited[i] = 1;
            }
        }

        // re-enqueue current process if not finished
        if (p[idx].rt > 0) {
            queue[rear++] = idx;
            if (rear == 100) rear = 0;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}
