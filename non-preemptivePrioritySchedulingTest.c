#include "types.h"
#include "user.h"

struct timing
{
    int creationTime;
    int terminationTime;
    int sleepingTime;
    int readyTime;
    int runningTime;
};

int main(void)
{
    changePolicy(2); // 2 stands for priority sched

    int i = 0;
    int j = 0;
    int k = 0;

    struct timing times[30];
    int pids[30];
    for (j = 0; j < 30; j++)
    {
        if (fork() == 0)
        {
            if (0 <= j && j <= 4)
                setPriority(6);
            else if (5 <= j && j <= 9)
                setPriority(5);
            else if (10 <= j && j <= 14)
                setPriority(4);
            else if (15 <= j && j <= 19)
                setPriority(3);
            else if (20 <= j && j <= 24)
                setPriority(2);
            else if (25 <= j && j <= 29)
                setPriority(1);

            for (i = 1; i < 250; i++)
                printf(1, "[%d]:[%d] \n", j, i);
            exit();
        }
    }

    for (k = 0; k < 30; k++)
        pids[k] = waitWithTimings(&times[k]);

    // sorting
    struct timing tmp;
    int priority_min_index;
    int pid_min;
    int pid_tmp;
    for (i = 0; i < 30; i++)
    {
        // find minimum
        pid_min = 100000;
        priority_min_index = -1;
        for (j = i; j < 30; j++)
        {
            if (pids[j] < pid_min)
            {
                pid_min = pids[j];
                priority_min_index = j;
            }
        }

        // swapping
        tmp = times[priority_min_index];
        times[priority_min_index] = times[i];
        times[i] = tmp;

        pid_tmp = pids[priority_min_index];
        pids[priority_min_index] = pids[i];
        pids[i] = pid_tmp;
    }

    // total
    int totalTurnaroundTime = 0;
    int totalCBT = 0;
    int totalWaitingTime = 0;
    int childNumber = 30;

    // per priority
    int sumTurnaroundTime[7];
    int sumCBT[7];
    int sumWaitingTime[7];
    int childPerClass = 5;

    for (k = 0; k < 30; k++)
    {
        if (0 <= k && k <= 4)
        {
            sumTurnaroundTime[6] += (times[k].terminationTime - times[k].creationTime);
            sumCBT[6] += times[k].runningTime;
            sumWaitingTime[6] += times[k].readyTime;
        }
        else if (5 <= k && k <= 9)
        {
            sumTurnaroundTime[5] += (times[k].terminationTime - times[k].creationTime);
            sumCBT[5] += times[k].runningTime;
            sumWaitingTime[5] += times[k].readyTime;
        }
        else if (10 <= k && k <= 14)
        {
            sumTurnaroundTime[4] += (times[k].terminationTime - times[k].creationTime);
            sumCBT[4] += times[k].runningTime;
            sumWaitingTime[4] += times[k].readyTime;
        }
        else if (15 <= k && k <= 19)
        {
            sumTurnaroundTime[3] += (times[k].terminationTime - times[k].creationTime);
            sumCBT[3] += times[k].runningTime;
            sumWaitingTime[3] += times[k].readyTime;
        }
        else if (20 <= k && k <= 24)
        {
            sumTurnaroundTime[2] += (times[k].terminationTime - times[k].creationTime);
            sumCBT[2] += times[k].runningTime;
            sumWaitingTime[2] += times[k].readyTime;
            
        }
        else if (25 <= k && k <= 29)
        {
            sumTurnaroundTime[1] += (times[k].terminationTime - times[k].creationTime);
            sumCBT[1] += times[k].runningTime;
            sumWaitingTime[1] += times[k].readyTime;
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

    // avg - per priority
    int avgTurnaroundTime[7];
    int avgCBT[7];
    int avgWaitingTime[7];

    for (int t = 1; t < 7; t++)
    {
        avgTurnaroundTime[t] = sumTurnaroundTime[t] / childPerClass;
        avgCBT[t] = sumCBT[t] / childPerClass;
        avgWaitingTime[t] = sumWaitingTime[t] / childPerClass;

        printf(1, "\nPriority %d : \n", t);
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