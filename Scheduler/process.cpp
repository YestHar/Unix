#include "process.hpp"

Process::Process(int pid, int arrival, int burst)
    : pid(pid),
      arrivalTime(arrival),
      burstTime(burst),
      remainingTime(burst),
      currentQueueLevel(0),
      waitingTime(0),
      lastExecutedTime(arrival) {
        enteredQueueTime = arrivalTime;
      }

void Process::updateWaitingTime(int currentTime) {
    waitingTime += currentTime - lastExecutedTime;
    lastExecutedTime = currentTime;
}
