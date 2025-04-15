#ifndef MLFQ_SCHEDULER_HPP
#define MLFQ_SCHEDULER_HPP

#include <vector>
#include "queue_level.hpp"
#include "aging_manager.hpp"
#include "process.hpp"

class MLFQScheduler {
private:
    std::vector<QueueLevel> queues;
    AgingManager agingManager; 
    int currentTime;

public:
    MLFQScheduler();
    void addProcess(Process* process);
    void run();
};

#endif // MLFQ_SCHEDULER_HPP
