#include "elevator.h"

/**
 * Set the floors for elevator to visit
 * 
 * This functions sorts the input floors to visit by mimicing the SCAN Disk   
 * Scheduling Algorithm (AKA the Elevator Algorithm)
 * 
 * Here we always assume the elevator has been called to the starting floor 
 * from a lower floor, so it visits the above floors first, followed by the 
 * lower floors
 * 
 * @param floorsToVisit The unsorted input of floors to visit, including
 * the starting floor
*/
void Elevator::setFloorsToVisit(std::vector<int> floorsToVisit) {
    _floorsToVisit = floorsToVisit;
    int startingFloor = floorsToVisit[0];
    _floorsToVisit.erase(_floorsToVisit.begin());

    auto partitionFloors = std::partition(_floorsToVisit.begin(), _floorsToVisit.end(), [startingFloor](int floorNum) {
        return floorNum > startingFloor;
    });
    std::sort(_floorsToVisit.begin(), partitionFloors);
    std::sort(partitionFloors, _floorsToVisit.end(), std::greater<int>());

    _currentFloor = startingFloor;
}

/**
 * Visit the floors
 * 
 * This function assumes floors are already sorted in desired order, simply 
 * visits the floors one by one and adds to its travel time until all floors 
 * are visited
*/
void Elevator::visitFloors() {
    _floorsVisited.push_back(_currentFloor);
    for (int floor : _floorsToVisit) {
        int timeToNextFloor = abs(_currentFloor - floor) * _TIME_TO_TRAVEL;
        _travelTime += timeToNextFloor;

        _currentFloor = floor;
        _floorsVisited.push_back(_currentFloor);
    }
}

/**
 * @return The cumulative travel of the elevator
*/
int Elevator::getTravelTime() {
    return _travelTime;
}

/**
 * @return The list of floors that the elevator has visited
*/
std::vector<int> Elevator::getFloorsVisited() {
    return _floorsVisited;
}

Elevator::Elevator() {
    _currentFloor = 0;
    _travelTime = 0;
}

Elevator::~Elevator() {
}