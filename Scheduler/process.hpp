#ifndef PROCESS_HPP
#define PROCESS_HPP

class Process {
public:
    int pid;              
    int arrivalTime;       
    int burstTime;         
    int remainingTime;     
    int currentQueueLevel;
    int waitingTime;      
    int lastExecutedTime;  
    int enteredQueueTime; 

    Process(int pid, int arrival, int burst);

    void updateWaitingTime(int currentTime);
};

#endif // PROCESS_HPP
