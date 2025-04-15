#include "fcfs.hpp"

int FCFS::execute(Process* process, int) {
    int execTime = process->remainingTime;
    process->remainingTime = 0;
    return execTime;
}
