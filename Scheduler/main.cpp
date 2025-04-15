#include <iostream>
#include "mlfq_scheduler.hpp"
#include "process.hpp"

int main() {
    MLFQScheduler scheduler;

    Process* p1 = new Process(1, 0, 4);   
    Process* p2 = new Process(2, 0, 15);   
    Process* p3 = new Process(3, 0, 25); 
    Process* p4 = new Process(4, 5, 30);  
    Process* p5 = new Process(5, 10, 6);  

    scheduler.addProcess(p1);
    scheduler.addProcess(p2);
    scheduler.addProcess(p3);
    scheduler.addProcess(p4);
    scheduler.addProcess(p5);

    std::cout << "\nMLFQ Scheduling Simulation Start:\n" << std::endl;

    scheduler.run();

    std::cout << "\nSimulation Complete.\n" << std::endl;

    return 0;
}
