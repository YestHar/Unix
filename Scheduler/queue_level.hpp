#ifndef QUEUE_LEVEL_HPP
#define QUEUE_LEVEL_HPP

#include <queue>
#include <string>
#include "process.hpp"
#include "scheduling_algorithm.hpp"

class QueueLevel {
public:
    int levelID;
    int timeQuantum;
    std::queue<Process*> queue;
    ISchedulingAlgorithm* algorithm; 

    QueueLevel(int id, int quantum, ISchedulingAlgorithm* algo);

    void addProcess(Process* process);
    bool hasProcess() const;
    Process* getNextProcess();
};

#endif // QUEUE_LEVEL_HPP
