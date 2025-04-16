#include "mlfq_scheduler.hpp"
#include "round_robin.hpp"
#include "fcfs.hpp"
#include <iostream>
#include <algorithm>

MLFQScheduler::MLFQScheduler()
    : currentTime(0), agingManager(20) 
{
    queues.emplace_back(0, 5, new RoundRobin()); 
    queues.emplace_back(1, 10, new RoundRobin());
    queues.emplace_back(2, 0, new FCFS());      
}

void MLFQScheduler::addProcess(Process* process) {
    if (process->type == IO_BOUND && queues.size() > 1) {
        process->currentQueueLevel = 0;
        std::cout << "Process P" << process->pid << " (I/O-bound) placed in highest priority Q0\n";
        queues[0].addProcess(process);
    } else {
        int level = (queues.size() > 2) ? 1 : 0;
        process->currentQueueLevel = level;
        std::cout << "Process P" << process->pid << " (CPU-bound) placed in Q" << level << "\n";
        queues[level].addProcess(process);
    }
}

void MLFQScheduler::run() {
    while (true) {
        bool didWork = false;

        for (size_t i = 0; i < queues.size(); ++i) {
            QueueLevel& q = queues[i];
            if (!q.hasProcess()) continue;

            Process* p = q.getNextProcess();

            if (p->isWaitingForIO) {
                q.addProcess(p);
                continue;
            }

            if (p->type == IO_BOUND && !p->ioCompleted) {
                int executed = p->burstTime - p->remainingTime;
                int nextExec = std::min(p->remainingTime, q.timeQuantum);

                if (executed < p->ioRequestTime && executed + nextExec >= p->ioRequestTime) {
                    int slice = p->ioRequestTime - executed;
                    std::cout << "Time " << currentTime << ": Executing P" << p->pid
                              << " from Q" << i << " for " << slice << " ms (until I/O request)\n";

                    p->updateWaitingTime(currentTime);
                    currentTime += slice;
                    p->remainingTime -= slice;

                    p->isWaitingForIO = true;
                    q.addProcess(p);
                    std::cout << "P" << p->pid << " is now waiting for I/O at time " << currentTime << " ms\n";
                    didWork = true;
                    break;
                }
            }

            p->updateWaitingTime(currentTime);

            int execTime = q.algorithm->execute(p, q.timeQuantum);

            std::cout << "Time " << currentTime 
                      << ": Executing P" << p->pid 
                      << " from Q" << i 
                      << " for " << execTime << " ms\n";

            currentTime += execTime;

            if (p->remainingTime == 0) {
                std::cout << "Process P" << p->pid << " finished at " << currentTime << " ms\n";
                delete p;
            } else {
                if (execTime < q.timeQuantum && i > 0) {
                    p->currentQueueLevel = i - 1;
                    std::cout << "Promoting P" << p->pid << " to Q" << p->currentQueueLevel << " (I/O-bound)\n";
                    queues[i - 1].addProcess(p);
                } else if (q.timeQuantum > 0 && execTime == q.timeQuantum && i + 1 < queues.size()) {
                    p->currentQueueLevel = i + 1;
                    std::cout << "Demoting P" << p->pid << " to Q" << p->currentQueueLevel << " (CPU-bound)\n";
                    queues[i + 1].addProcess(p);
                } else {
                    queues[i].addProcess(p);
                }
            }

            didWork = true;
            break;
        }

        agingManager.checkAndPromote(queues, currentTime);

        for (QueueLevel& q : queues) {
            std::queue<Process*> temp;
            while (!q.queue.empty()) {
                Process* p = q.queue.front();
                q.queue.pop();

                if (p->isWaitingForIO) {
                    std::string answer;
                    std::cout << "Input is ready for process P" << p->pid << ". Would you like to provide input now? (yes/no): ";
                    std::cin >> answer;

                    if (answer == "yes") {
                        p->isWaitingForIO = false;
                        p->ioCompleted = true;
                        std::cout << "I/O has been provided. Process P" << p->pid << " is returning to queue Q" << p->currentQueueLevel << "\n";
                    }
                    temp.push(p);
                } else {
                    temp.push(p);
                }
            }
            q.queue = temp;
        }

        if (!didWork) break;
    }
}
