#include "mlfq_scheduler.hpp"
#include "round_robin.hpp"
#include "fcfs.hpp"
#include <iostream>

MLFQScheduler::MLFQScheduler() : currentTime(0), agingManager(20) {
    queues.emplace_back(0, 5, new RoundRobin());  
    queues.emplace_back(1, 10, new RoundRobin()); 
    queues.emplace_back(2, 0, new FCFS());        
}

void MLFQScheduler::addProcess(Process* process) {
    process->currentQueueLevel = 0;
    queues[0].addProcess(process);
}

void MLFQScheduler::run() {
    while (true) {
        bool didWork = false;

        for (size_t i = 0; i < queues.size(); ++i) {
            QueueLevel& q = queues[i];
            if (!q.hasProcess()) continue;

            Process* p = q.getNextProcess();
            p->updateWaitingTime(currentTime);

            int execTime = q.algorithm->execute(p, q.timeQuantum);

            std::cout << "Time " << currentTime 
                      << ": Executing P" << p->pid 
                      << " from Q" << i 
                      << " for " << execTime << " ms" << std::endl;

            currentTime += execTime;

            if (p->remainingTime == 0) {
                std::cout << "Process P" << p->pid << " finished at " << currentTime << " ms\n";
                delete p;
            } else {
                if (i + 1 < queues.size()) {
                    p->currentQueueLevel = i + 1;
                    queues[i + 1].addProcess(p);
                } else {
                    queues[i].addProcess(p); 
                }
            }

            didWork = true;
            break; 
        }
        agingManager.checkAndPromote(queues, currentTime);
        if (!didWork) break;
    }
}
