cmake_minimum_required(VERSION 3.10)

# Set the project name
project(AirportProject)

# Set C++ standard to C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add all your source files
set(SOURCES 
    src/Main.cpp 
    src/Airport.cpp 
    src/Constants.hpp
    src/Passenger.cpp 
    src/PassengerFactory.cpp 
    src/Plane.cpp 
    src/Runway.cpp 
    src/Utils.cpp
    src/Gate.cpp
)

# Add executable target
add_executable(main ${SOURCES})
