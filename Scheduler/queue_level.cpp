#include "queue_level.hpp"

QueueLevel::QueueLevel(int id, int quantum, ISchedulingAlgorithm* algo)
    : levelID(id), timeQuantum(quantum), algorithm(algo) {}

void QueueLevel::addProcess(Process* process) {
    process->enteredQueueTime = process->lastExecutedTime;
    queue.push(process);
}


bool QueueLevel::hasProcess() const {
    return !queue.empty();
}

Process* QueueLevel::getNextProcess() {
    if (queue.empty()) return nullptr;

    Process* p = queue.front();
    queue.pop();
    return p;
}

