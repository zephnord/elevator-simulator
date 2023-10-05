#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <libgen.h>

class Elevator {

public:
    const int _MIN_FLOOR = 0;
    const int _MAX_FLOOR = 202; // The most floors in a building I could find   (Sky City Tower in Changsha, China)

    Elevator();
    ~Elevator();

    void setFloorsToVisit(std::vector<int> floorsToVisit);
    void visitFloors();
    int getTravelTime();
    std::vector<int> getFloorsVisited();

private:
    int _currentFloor;
    int _travelTime;
    std::vector<int> _floorsToVisit;
    std::vector<int> _floorsVisited;
    const int _TIME_TO_TRAVEL = 10;
};

#endif /* ELEVATOR_H */