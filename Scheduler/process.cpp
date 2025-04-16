#include "process.hpp"

Process::Process(int pid, int arrival, int burst, ProcessType type)
    : pid(pid),
      arrivalTime(arrival),
      burstTime(burst),
      remainingTime(burst),
      currentQueueLevel(0),
      waitingTime(0),
      lastExecutedTime(arrival),
      enteredQueueTime(arrival),
      type(type),
      ioRequestTime(-1),
      isWaitingForIO(false),
      ioCompleted(false) {}


void Process::updateWaitingTime(int currentTime) {
    waitingTime += currentTime - lastExecutedTime;
    lastExecutedTime = currentTime;
}

