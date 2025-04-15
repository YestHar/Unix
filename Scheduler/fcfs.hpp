#ifndef FCFS_HPP
#define FCFS_HPP

#include "scheduling_algorithm.hpp"

class FCFS : public ISchedulingAlgorithm {
public:
    int execute(Process* process, int timeQuantum) override;
};

#endif
