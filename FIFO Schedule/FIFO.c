#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "plist.dat"
#define MAX_TIME 40

void printResult(int pnum, int *pid, int *at, int *bt, int *tt, int *wt) {
    int i, sum_tt=0, sum_wt=0;

    printf("%s %s %s %s %s\n", "Pid", "At", "Bt", "Tt", "Wt");
    for(i=0; i<pnum; ++i) {
        printf("%2d %2d %2d %2d %2d\n", pid[i], at[i], bt[i], tt[i], wt[i]);
        sum_tt+=tt[i];
        sum_wt+=wt[i];
    }

    printf("  avg. of TT: %.2f\n", (float)sum_tt/pnum);
    printf("  avg. of WT: %.2f\n", (float)sum_wt/pnum);
}

void FIFO(int pnum, int *pid, int *at, int *bt, int *tt, int *wt) {
    printf("  Scheme: First-In-First-Out\n");
    int cpu_time=0, p=0;
    
    do{
        //  Plus Waiting Time
        if(p!=0 && cpu_time<at[p-1]+tt[p-1])
            wt[p]++;
        
        //  Kill the Process
        if(cpu_time==at[p]+bt[p]+wt[p]){
            tt[p]=bt[p]+wt[p];
            printf("wt[%d] : %d , tt[%d] : %d\n", p, wt[p], p, tt[p]);
            p++;
            cpu_time = at[p]-1;
        }
        
        if(p==10)
            break;
        
        cpu_time++;
    }while(cpu_time<MAX_TIME);
}

int main(void) {
    FILE *fp;
    int pnum, i, exit=0;
    int *pid, *at, *bt, *tt, *wt;

    fp = fopen(INPUT_FILE, "r");
    //read the number of processes
    fscanf(fp, "%d", &pnum);

    pid = (int*)calloc(pnum, sizeof(int));
    at = (int*)calloc(pnum, sizeof(int));
    bt = (int*)calloc(pnum, sizeof(int));
    tt = (int*)calloc(pnum, sizeof(int));
    wt = (int*)calloc(pnum, sizeof(int));

    for(i=0; i<pnum; ++i) {
        fscanf(fp, "%d %d %d", &pid[i], &at[i], &bt[i]);
    }

    fclose(fp);
        
    FIFO(pnum, pid, at, bt, tt, wt);
        

    printResult(pnum, pid, at, bt, tt, wt);
    memset(tt, 0, sizeof(int)*pnum);
    memset(wt, 0, sizeof(int)*pnum);
    
    return 0;
}

