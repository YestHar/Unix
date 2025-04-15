#ifndef SCHEDULING_ALGORITHM_HPP
#define SCHEDULING_ALGORITHM_HPP

#include "process.hpp"

class ISchedulingAlgorithm {
public:
    virtual int execute(Process* process, int timeQuantum) = 0;
    virtual ~ISchedulingAlgorithm() = default;
};

#endif
