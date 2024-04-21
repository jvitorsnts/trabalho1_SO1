//
// Created by joao on 13/04/2024.
//

#include <iostream>
#include <vector>
#include "../headers/RM.h"

using namespace std;

RM::RM(vector<Process *> processes) {
        this->processes = move(processes);
    }

void RM::scheduleNextProcess() {
    if (currentProcess == nullptr) {
        currentProcess = readyProcesses.front();
        contextSwitches++;
    }
    else {
        for (auto readyProcess : readyProcesses) {
            if (readyProcess->getPriority() > currentProcess->getPriority()) {
                currentProcess->preempt();
                currentProcess = readyProcess;
                contextSwitches++;
            }
        }
    }
}