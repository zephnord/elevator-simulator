# elevator-simulator

This is a command line program to simulate a very simple elevator.

This elevator assumes it is always called to the starting floor from a lower floor, and therefor services floors higher than the starting floors in ascending order, and then floors lower than the starting floor in descending order. This utilizes the SCAN Disk Scheduling Algorithm.

This elevator also only services floors 0-202 inclusively.

The executable can be ran with the following arguments via command line: \<starting floor> \<list of floors to visit>

  e.g. .\elevator-simulator.exe 10 15,20,30,11,25

The output of the program will display the total travel time of the elevator (in arbitrary units) along with a list of floors the elevator visited in order.

This program was compiled and verified with gcc version 12.1.0 but should be compatible with any modern C++ compiler if you choose to compile from source.
