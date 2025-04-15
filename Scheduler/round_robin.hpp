#ifndef ROUND_ROBIN_HPP
#define ROUND_ROBIN_HPP

#include "scheduling_algorithm.hpp"

class RoundRobin : public ISchedulingAlgorithm {
public:
    int execute(Process* process, int timeQuantum) override;
};

#endif
