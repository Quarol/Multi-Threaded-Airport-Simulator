#include "Output.hpp"

#include <ncurses.h>
#include <cstring>
#include <thread>
#include <chrono>

#include "Constants.hpp"

std::mutex OutputHandler::ncursesMutex_;

std::string headerTxt = "Multi-threaded airport:";
std::string pplPastGatesTxt = "People past gates: ";
std::string planesReadyTxt = "Planes ready: ";
std::string terroristAttackTxt = "Terrorist attack: ";
const int screenWidth = 70;
const int screenHeight = 10;

int passengersPastGates = 0;
int numberOfPlanes = 0;

const char* stringToConstCharPtr(std::string str) 
{
    return str.c_str();
}
const char * intToConstCharPtr(int number) 
{
    return std::to_string(number).c_str();
}
void writeMessageAt(int y, int x, std::string message)
{
    message = message + "   ";
    mvprintw(y, x, "%s", stringToConstCharPtr(message));
}

void OutputHandler::refreshOutput()
{
    while (1)
    {
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void OutputHandler::initGUI() 
{
    numberOfPlanes = 0;
    passengersPastGates = 0;

    initscr();
    cbreak();
    noecho();

    writeMessageAt(0, 1, headerTxt);
    writeMessageAt(3, 3, pplPastGatesTxt + "0");
    writeMessageAt(4, 3, planesReadyTxt + "0");
    writeMessageAt(5, 3, terroristAttackTxt + "off");

    // Set borders of GUI:
    for (int i = 1; i < screenHeight; i++) 
        mvaddch(i, 1, '#');
    for (int i = 1; i < screenWidth; i++) 
        mvaddch(1, i, '#');
    for (int i = 1; i < screenHeight; i++) 
        mvaddch(i, screenWidth, '#');
    for (int i = 1; i < screenWidth; i++) 
        mvaddch(screenHeight, i, '#');

    refresh();
}


void OutputHandler::addPlanes(int number)
{
    std::unique_lock<std::mutex> lock(ncursesMutex_);
    numberOfPlanes += number;

    const char* output = intToConstCharPtr(numberOfPlanes);
    writeMessageAt(4, 3 + planesReadyTxt.length(), output);

    refresh();
}


void OutputHandler::adjustAfterFlight()
{
    std::unique_lock<std::mutex> lock(ncursesMutex_);

    passengersPastGates -= Constants::PASSENGERS_PER_PLANE;
    numberOfPlanes -= 1;

    const char* passengersOutput = intToConstCharPtr(passengersPastGates);
    const char* planesOutput = intToConstCharPtr(numberOfPlanes);
    
    writeMessageAt(3, 3 + pplPastGatesTxt.length(), passengersOutput);
    writeMessageAt(4, 3 + planesReadyTxt.length(), planesOutput); 

    refresh();
}


void OutputHandler::setPeoplePastGates(int peoplePastGates)
{
    std::unique_lock<std::mutex> lock(ncursesMutex_);

    const char* output = intToConstCharPtr(peoplePastGates);
    writeMessageAt(3, 3 + pplPastGatesTxt.length(), output);

    refresh();
}


void OutputHandler::addPeoplePastGates(int peoplePastGates)
{
    std::unique_lock<std::mutex> lock(ncursesMutex_);

    passengersPastGates += peoplePastGates;
    const char* output = intToConstCharPtr(passengersPastGates);
    writeMessageAt(3, 3 + pplPastGatesTxt.length(), output);

    refresh();
}


void OutputHandler::setIsTerroristAttackOn(bool isOn)
{
    std::unique_lock<std::mutex> lock(ncursesMutex_);

    if (isOn)
        writeMessageAt(5, 3 + terroristAttackTxt.length(), "on ");
    else
        writeMessageAt(5, 3 + terroristAttackTxt.length(), "off");

    refresh();
}
