CXX = g++
CXXFLAGS = -std=c++17 -Wall
OBJS = main.o process.o queue_level.o mlfq_scheduler.o round_robin.o fcfs.o aging_manager.o

all: scheduler

scheduler: $(OBJS)
	$(CXX) $(CXXFLAGS) -o scheduler $(OBJS)

main.o: main.cpp process.hpp mlfq_scheduler.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

process.o: process.cpp process.hpp
	$(CXX) $(CXXFLAGS) -c process.cpp

queue_level.o: queue_level.cpp queue_level.hpp process.hpp scheduling_algorithm.hpp
	$(CXX) $(CXXFLAGS) -c queue_level.cpp

mlfq_scheduler.o: mlfq_scheduler.cpp mlfq_scheduler.hpp queue_level.hpp aging_manager.hpp round_robin.hpp fcfs.hpp
	$(CXX) $(CXXFLAGS) -c mlfq_scheduler.cpp

round_robin.o: round_robin.cpp round_robin.hpp scheduling_algorithm.hpp
	$(CXX) $(CXXFLAGS) -c round_robin.cpp

fcfs.o: fcfs.cpp fcfs.hpp scheduling_algorithm.hpp
	$(CXX) $(CXXFLAGS) -c fcfs.cpp

aging_manager.o: aging_manager.cpp aging_manager.hpp process.hpp queue_level.hpp
	$(CXX) $(CXXFLAGS) -c aging_manager.cpp

clean:
	rm -f *.o scheduler
