#include "round_robin.hpp"
#include <algorithm>

int RoundRobin::execute(Process* process, int timeQuantum) {
    int execTime = std::min<int>(process->remainingTime, timeQuantum);
    process->remainingTime -= execTime;
    return execTime;
}

