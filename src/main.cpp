#include "elevator.h"

/*******************************************************************************
 * This program simulates a very basic elevator that can be ran via 
 * command-line arguments
 * 
 * The elevator assumes that all passengers are loaded at a single given floor 
 * (The first floor in the given floors to visit list) and makes one round trip 
 * to drop off all passengers before returning to the user the total trip time, 
 * and the order in which the floors were visited before exiting the program.
 * 
 * There are no intermediate stops or loading once the elevator has been 
 * started.
 ******************************************************************************
 */

/**
 * Parse the command-line input of the user
 * 
 * This function ensures the user provides valid list of floors to visit between
 * the minimum and maximum floor, without any invalid characters.
 * 
 * @param floorsInput The list of floors the user has provided in comma-delimited format
 * 
 * @return Whether the input was successfully parsed (0) or not (-1)
 ********************************************************************************/
int parseInput(std::string startingFloor, std::string floorsInput, 
    const int MIN_FLOOR, const int MAX_FLOOR, std::vector<int> &floorsToVisit) {
    std::string floors(floorsInput);
    std::istringstream floorsStream(floors);
    std::string floor;

    // Check the given starting floor for valid input
    int startingFloorNum = stoi(startingFloor);
    if (MIN_FLOOR <= startingFloorNum && startingFloorNum <= MAX_FLOOR &&
        startingFloorNum != 13) {
        for (char charInStartingFloor : startingFloor) {
            if (!isdigit(charInStartingFloor)) {
                std::cout << "Invalid input: " << charInStartingFloor << std::endl;
                return -1;
            }
        }
    }
    else {
        std::cout << "Invalid starting floor number given: " << floor << std::endl << "Elevator services floors " << MIN_FLOOR << " to " << MAX_FLOOR << std::endl;
        return -1;        
    }
    floorsToVisit.push_back(startingFloorNum);


    // Check the given list of floors for valid input
    while (std::getline(floorsStream, floor, ',')) {    
        for (char charInFloor : floor) {
            if (!isdigit(charInFloor)) {
                std::cout << "Invalid input: " << charInFloor << std::endl;
                return -1;
            }
        }

        int floorNum;
        std::istringstream(floor) >> floorNum;
        
        if (MIN_FLOOR <= floorNum && floorNum <= MAX_FLOOR && floorNum != 13) {
            // This handles duplicate floors to visit as well as trying to visit the starting floor
            if (std::find(floorsToVisit.begin(), floorsToVisit.end(), floorNum) == floorsToVisit.end()) {
                floorsToVisit.push_back(floorNum);
            }
        }
        else {
            std::cout << "Invalid floor number given: " << floor << std::endl
                << "Elevator services floors " << MIN_FLOOR << " to "  
                << MAX_FLOOR << std::endl;
            return -1;
        }
    }

    return 0;
}

/**
 * Parse the command-line output of the program
 * 
 * This function outputs the final travel time and list of floors visited into a comma-delimited format
 * 
 * @param travelTime The total travel time of the elevator after visiting all floors
 * @param floorsVisited The list of floors visited by the elevator
 ********************************************************************************/
void parseOutput(int travelTime, std::vector<int> floorsVisited) {
    std::ostringstream outputStreamFloors;
    for (int floor : floorsVisited) {
        outputStreamFloors << floor << ",";
    }

    std::string floorsVisitedString = outputStreamFloors.str();
    floorsVisitedString.erase(floorsVisitedString.end()-1);

    std::cout << "Total travel time: " << travelTime << " "
        << "Floors visited in order: " << floorsVisitedString << std::endl;
}

/**
 * Show the user how to interact with the program
 * 
 * @param filePath The input path of the executable
*/
void outputUsage(char* filePath) {
    std::cout << "Usage: " << std::endl;
    std::cout << "\t" << basename(filePath) << " " << "<starting floor> <list of floors to visit>" << std::endl;
    std::cout << "\tExample: " << basename(filePath) << " 20 4,15,10,49" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        outputUsage(argv[0]);
        return 0;
    }

    Elevator elevator;
    std::vector<int> floorsToVisit;

    int retVal = parseInput(argv[1], argv[2], elevator._MIN_FLOOR, elevator._MAX_FLOOR, floorsToVisit);

    if (retVal == 0) {
        elevator.setFloorsToVisit(floorsToVisit);
        elevator.visitFloors();

        parseOutput(elevator.getTravelTime(), elevator.getFloorsVisited());
    }
    else {
        outputUsage(argv[0]);
    }

    return 0;
}