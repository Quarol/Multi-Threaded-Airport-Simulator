cmake_minimum_required(VERSION 3.10)

# Set the project name
project(AirportProject)

# Set C++ standard to C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add all your source files
set(SOURCES 
    src/Main.cpp
    src/Constants.hpp
    src/Passenger.cpp 
    src/PassengerFactory.cpp 
    src/Plane.cpp 
    src/Runway.cpp 
    src/Utils.cpp
    src/Gate.cpp
    src/Output.cpp  # fixed typo from 'serc/Output.cpp'
)

# Find the ncurses package
find_package(Curses REQUIRED)

# Include ncurses directories
include_directories(${CURSES_INCLUDE_DIR})

# Add executable target
add_executable(main ${SOURCES})

# Link ncurses library to the target
target_link_libraries(main ${CURSES_LIBRARIES})
