#include "../headers/EarliestDeadlineFirst.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

EarliestDeadlineFirst::EarliestDeadlineFirst(vector<Process *> processes) {
    this->processes = move(processes);
}

void EarliestDeadlineFirst::scheduleNextProcess() {
    Process *nextProcessIt = nullptr;
    for (auto readyProcess : readyProcesses) {
        if (nextProcessIt == nullptr || readyProcess->getRelativeDeadline() < nextProcessIt->getRelativeDeadline()) {
            nextProcessIt = readyProcess;
        }
    }

    if(currentProcess != nullptr && currentProcess != nextProcessIt){
        currentProcess->preempt();
        contextSwitches++;
    }
    if(currentProcess == nullptr) contextSwitches++;
    currentProcess = nextProcessIt;
    CPU.setContext(currentProcess);
}
