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
    changePolicy(3); // 3 stands for MultiLayered
    int i = 0;
    int j = 0;
    int k = 0;

    struct timing times[40];
    for (j = 0; j < 40; j++)
    {
        if (fork() == 0)
        {
            if (0 <= j && j <= 9)
                setQueue(1);
            else if (10 <= j && j <= 19)
                setQueue(2);
            else if (20 <= j && j <= 29)
            {
                setQueue(3);
                setPriority(2);
            }
            else if (30 <= j && j <= 39)
            {
                setQueue(4);
                setPriority(4);
            }
            for (i = 1; i < 200; i++)
                printf(1, "[%d]:[%d] \n", j, i);
            exit();
        }
    }
    for (k = 0; k < 40; k++)
        waitWithTimings(&times[k]);

    
    // total
    int totalTurnaroundTime = 0;
    int totalCBT = 0;
    int totalWaitingTime = 0;
    int childNumber = 40;

    // per queue
    int sumTurnaroundTime[5];
    int sumCBT[5];
    int sumWaitingTime[5];
    int childPerClass = 10;

    for (k = 0; k < 40; k++)
    {
        if (0 <= k && k <= 9)
        {
            sumTurnaroundTime[1] += (times[k].terminationTime - times[k].creationTime);
            sumCBT[1] += times[k].runningTime;
            sumWaitingTime[1] += times[k].readyTime;
        }
        else if (10 <= k && k <= 19)
        {
            sumTurnaroundTime[2] += (times[k].terminationTime - times[k].creationTime);
            sumCBT[2] += times[k].runningTime;
            sumWaitingTime[2] += times[k].readyTime;
        }
        else if (20 <= k && k <= 29)
        {
            sumTurnaroundTime[3] += (times[k].terminationTime - times[k].creationTime);
            sumCBT[3] += times[k].runningTime;
            sumWaitingTime[3] += times[k].readyTime;
        }
        else if (30 <= k && k <= 39)
        {
            sumTurnaroundTime[4] += (times[k].terminationTime - times[k].creationTime);
            sumCBT[4] += times[k].runningTime;
            sumWaitingTime[4] += times[k].readyTime;
        }

        totalTurnaroundTime += (times[k].terminationTime - times[k].creationTime);
        totalCBT += times[k].runningTime;
        totalWaitingTime += times[k].readyTime;

        printf(1, "Child number : %d \n", (k + 1));
        printf(1, "Turnaround time : %d  \n", (times[k].terminationTime - times[k].creationTime));
        printf(1, "CBT : %d  \n", times[k].runningTime);
        printf(1, "Waiting time : %d  \n", times[k].readyTime);
        printf(1, "\n");
    }

    // avg - total
    int avgTurnaroundTime_total = totalTurnaroundTime / childNumber;
    int avgCBT_total = totalCBT / childNumber;
    int avgWaitingTime_total = totalWaitingTime / childNumber;

    // avg - per queue
    int avgTurnaroundTime[5];
    int avgCBT[5];
    int avgWaitingTime[5];

    for (int t = 1; t < 5; t++)
    {
        avgTurnaroundTime[t] = sumTurnaroundTime[t] / childPerClass;
        avgCBT[t] = sumCBT[t] / childPerClass;
        avgWaitingTime[t] = sumWaitingTime[t] / childPerClass;

        printf(1, "\nQueue %d : \n", t);
        printf(1, "Average Turnaround time : %d  \n", avgTurnaroundTime[t]);
        printf(1, "Average CBT : %d  \n", avgCBT[t]);
        printf(1, "Average Waiting time : %d  \n", avgWaitingTime[t]);
    }

    printf(1, "\nAll Processes : \n");
    printf(1, "Average Turnaround time : %d  \n", avgTurnaroundTime_total);
    printf(1, "Average CBT : %d  \n", avgCBT_total);
    printf(1, "Average Waiting time : %d  \n", avgWaitingTime_total);

    exit();
}