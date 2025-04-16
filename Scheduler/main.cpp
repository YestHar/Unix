#include <iostream>
#include "mlfq_scheduler.hpp"
#include "process.hpp"

ProcessType determineProcessType(int burstTime) {
    return (burstTime < 10) ? IO_BOUND : CPU_BOUND;
}

int main() {
    MLFQScheduler scheduler;
    std::vector<Process*> processes;

    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        int pid, arrival, burst;
        std::cout << "\nProcess #"<< i + 1 << ":\n";
        std::cout << "PID: ";
        std::cin >> pid;
        std::cout << "Arrival time: ";
        std::cin >> arrival;
        std::cout << "Burst time: ";
        std::cin >> burst;

        ProcessType type = determineProcessType(burst);
        Process* p = new Process(pid, arrival, burst, type);

        if (type == IO_BOUND) {
            int ioTime;
            do {
                std::cout << "I/O request time (less than the burst time = " << burst << "): ";
                std::cin >> ioTime;
                if (ioTime >= burst || ioTime < 0) {
                    std::cout << "Invalid input: I/O request time must be positive and less than the burst time. Please try again.\n";
                }
            } while (ioTime >= burst || ioTime < 0);
        
            p->ioRequestTime = ioTime;
        }

        scheduler.addProcess(p);
        processes.push_back(p);
    }

    std::cout << "\nMLFQ Scheduling Simulation Start:\n" << std::endl;
    scheduler.run();
    std::cout << "\nSimulation Complete.\n" << std::endl;

    return 0;
}
