#include "aging_manager.hpp"
#include <queue>

AgingManager::AgingManager(int agingThreshold)
    : threshold(agingThreshold) {}

void AgingManager::checkAndPromote(std::vector<QueueLevel>& queues, int currentTime) {
    for (int i = queues.size() - 1; i > 0; --i) {
        std::queue<Process*> tempQueue;

        while (!queues[i].queue.empty()) {
            Process* p = queues[i].queue.front();
            queues[i].queue.pop();

            int waitingTime = currentTime - p->enteredQueueTime;

            if (waitingTime >= threshold) {
                p->currentQueueLevel = i - 1;
                p->enteredQueueTime = currentTime;
                queues[i - 1].addProcess(p);
            } else {
                tempQueue.push(p);
            }
        }

        queues[i].queue = tempQueue;
    }
}
