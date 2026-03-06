#include <stdio.h>
typedef struct process{
int pid,AT,BT,CT,TAT,WT;
}process;

int main(){
int n;
printf("enter the number of process : ");
scanf("%d",&n);
process p[n];
for( int i=0;i<n;i++){
    p[i].pid=i+1;
    printf("\n arrival time of %d : ",p[i].pid);
    scanf("%d",&p[i].AT);
    printf("\n burst time of %d: ",p[i].pid);
    scanf("%d",&p[i].BT);
}
float total_WT=0,total_TAT=0;

for( int i=0;i<n ; i++){
    for(int j=i+1;j<n;j++){
        process temp;

        if(p[i].AT>p[j].AT){
            temp=p[i];
            p[i]=p[j];
            p[j]=temp;

        }
    }
}

int curr_time=0;
for(int i =0 ;i<n;i++){
    if(curr_time<p[i].AT){
        curr_time=p[i].AT;
    }
        p[i].CT=curr_time+ p[i].BT;
        p[i].TAT=p[i].CT-p[i].AT;
        p[i].WT=p[i].TAT-p[i].BT;
        curr_time=p[i].CT;
        total_TAT+=p[i].TAT;
        total_WT+=p[i].WT;

}
 printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }

    printf("\nAverage Waiting Time: %.2f", total_WT / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_TAT / n);

    return 0;

}
