### OS_project_xv6
Implementing different scheduling policies in XV6 operating system.
This is a course project for the operating systems course instructed by [Dr.Seyed Ahmad Javadi](https://www3.cs.stonybrook.edu/~sjavadi/)

 With the new operating system of XV6, I implemented some scheduling policies, such as Round-Robin, non-preemptive priority scheduling,
 preemptive, and dynamic multi-layered queued scheduling.
 
 ## Round-Robin
 
 Round Robin CPU Algorithm generally focuses on Time Sharing technique. 
The period of time for which a process or job is allowed to run in a pre-emptive method is called time quantum. 
Each process or job present in the ready queue is assigned the CPU for that time quantum, if the execution of the process is completed during that time
then the process will end else the process will go back to the waiting table and wait for the its next turn to complete the execution.
 
 ## non-Preemptive priority
 
 Non-preemptive Scheduling is used when a process terminates, or a process switches from running to the waiting state. In this scheduling, once the resources (CPU cycles) are allocated to a process, the process holds the CPU till it gets terminated or reaches a waiting state. In the case of non-preemptive scheduling does not interrupt a process running CPU in the middle of the execution. Instead, it waits till the process completes its CPU burst time, and then it can allocate the CPU to another process. 
 
 ## Preemptive
 
 Preemptive scheduling is used when a process switches from running state to ready state or from the waiting state to ready state. The resources (mainly CPU cycles) are allocated to the process for a limited amount of time and then taken away, and the process is again placed back in the ready queue if that process still has CPU burst time remaining. That process stays in the ready queue till it gets its next chance to execute.
 
 ## Dynamic multi-layered queued 
 
 It may happen that processes in the ready queue can be divided into different classes where each class has its own scheduling needs. For example, a common division is a foreground (interactive) process and a background (batch) process. These two classes have different scheduling needs. For this kind of situation Multilevel Queue Scheduling is used. 
