#ifndef AGING_MANAGER_HPP
#define AGING_MANAGER_HPP

#include <vector>
#include "queue_level.hpp"

class AgingManager {
private:
    int threshold;

public:
    AgingManager(int agingThreshold);
    void checkAndPromote(std::vector<QueueLevel>& queues, int currentTime);
};

#endif // AGING_MANAGER_HPP
