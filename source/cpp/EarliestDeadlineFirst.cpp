#include "../headers/EarliestDeadlineFirst.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

    EarliestDeadlineFirst::EarliestDeadlineFirst() : currentTime(0) {}

    void EarliestDeadlineFirst::addProcess(const Process& process) {
        processes.push_back(process);
    }

    bool EarliestDeadlineFirst::compareByDeadline(const Process& p1, const Process& p2) {
        return p1.getDeadline() < p2.getDeadline();
    }

void EarliestDeadlineFirst::scheduleOneTimeUnit() {
    std::cout << std::setw(2) << std::right << currentTime << "-" << currentTime + 1;

    auto nextProcessIt = processes.end();
    for (auto it = processes.begin(); it != processes.end(); ++it) {
        if (!it->isFinished() && it->getStartTime() <= currentTime) {
            if (nextProcessIt == processes.end() || it->getDeadline() < nextProcessIt->getDeadline()) {
                nextProcessIt = it;
            }
        }
    }

    nextProcessIt->run();

    for (auto& process : processes) {
        if (&process == &(*nextProcessIt)) {
            std::cout << " ##";
        } else if (process.getStartTime() <= currentTime && !process.isFinished()) {
            std::cout << " --";
        } else {
            std::cout << "   ";
        }
    }
    std::cout << std::endl;

    currentTime++;
}

    bool EarliestDeadlineFirst::hasActiveProcesses() {
        // Verifica se algum processo ainda está em execução
        return std::any_of(processes.begin(), processes.end(), [](const Process& p) {
            return !p.isFinished();
        });
    }

    int EarliestDeadlineFirst::getCurrentTime() {
        return currentTime;
    }