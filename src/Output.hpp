#pragma once

#include <string>
#include <mutex>

class OutputHandler {
public:
    static void initGUI();
    static void setPeoplePastGates(int peoplePastGates);
    static void addPeoplePastGates(int peoplePastGates);
    static void setIsTerroristAttackOn(bool isOn);
    static void addPlanes(int number);
    static void adjustAfterFlight();
    static void refreshOutput();
private:
    static std::mutex ncursesMutex_;
};
