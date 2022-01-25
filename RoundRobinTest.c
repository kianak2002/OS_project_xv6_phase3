#include "types.h"
#include "stat.h"
#include "user.h"

struct timing
{
    uint creationTime;
    uint terminationTime;
    uint runningTime;
    uint readyTime;
    uint sleepingTime;
};

int main(void)
{
    changePolicy(1); // 1 stands for RR

    int i = 0;
    int j = 0;
    int k = 0;

    struct timing times[10];
    for (j = 0; j < 10; j++)
    {
        if (fork() == 0) // child process
        {
            for (i = 1; i < 1000; i++)
            {
                printf(1, "[%d]: [%d] \n", getpid(), i);
            }
            exit();
        }
    }

    for (k = 0; k < 10; k++)
        waitWithTimings(&times[k]);

    int sumTurnaroundTime = 0;
    int sumCBT = 0;
    int sumWaitingTime = 0;

    for (k = 0; k < 10; k++)
    {
        printf(1, "Child number : %d \n", (k + 1));
        printf(1, "Turnaround time : %d  \n", (times[k].terminationTime - times[k].creationTime));
        printf(1, "CBT : %d  \n", times[k].runningTime);
        printf(1, "Waiting time : %d  \n", times[k].readyTime);
        printf(1, "\n");
        sumTurnaroundTime += (times[k].terminationTime - times[k].creationTime);
        sumCBT += times[k].runningTime;
        sumWaitingTime += times[k].readyTime;
    }

    // calculating parameters
    int childNumber = 10;
    int avgTurnaroundTime = sumTurnaroundTime / childNumber;
    int avgCBT = sumCBT / childNumber;
    int avgWaitingTime = sumWaitingTime / childNumber;

    printf(1, "All Processes : \n");
    printf(1, "Average Turnaround time : %d  \n", avgTurnaroundTime);
    printf(1, "Average CBT : %d  \n", avgCBT);
    printf(1, "Average Waiting time : %d  \n", avgWaitingTime);

    exit();
}