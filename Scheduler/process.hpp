#ifndef PROCESS_HPP
#define PROCESS_HPP

enum ProcessType {
    CPU_BOUND,
    IO_BOUND
};

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
    ProcessType type; 
    int ioRequestTime;
    bool isWaitingForIO;
    bool ioCompleted;
    
    Process(int pid, int arrival, int burst, ProcessType type);
    void updateWaitingTime(int currentTime);
};

#endif // PROCESS_HPP


