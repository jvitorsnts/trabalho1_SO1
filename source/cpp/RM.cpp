//
// Created by joao on 13/04/2024.
//

#include <iostream>
#include <vector>
#include "../headers/RM.h"

using namespace std;

void RM::runScheduler() {
    printTimelineHeader();
    verifyProcessesToCreate();
        
    while (processes.size() != processesStats.size()) {
        if (readyProcesses.empty()) {
            printTimeline();
            time++;
            verifyProcessesToCreate();
        }
        else {
            scheduleNextProcess();
            currentProcess->run();
            printTimeline();
            time++;
            verifyProcessesToFinalize();
            finalizeProcesses();
            verifyProcessesToCreate();
        }
    }
    printProcessesStats();
}

void RM::verifyProcessesToCreate() {
    for (const auto &process: processes) {
        if (process->getStartTime() == time) {
            process->create();
            if (readyProcesses.empty()) {
                readyProcesses.push_back(process);
            } 
            else {
                int iter = 0;
                for (auto readyProcess : readyProcesses) {
                    if (process->getPriority() > readyProcess->getPriority()) {
                        readyProcesses.insert(readyProcesses.begin()+iter, process);
                        break;
                    }
                    iter++;
                }
            }
        }
    }
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

void RM::verifyProcessesToFinalize() {
    for (auto readyProcess : readyProcesses) {
        bool finalize = (readyProcess->getDeadline() == time-readyProcess->getStartTime())
                        or
                        (readyProcess->getRemainingTime() == 0);
        if (finalize) {
            readyProcess->finish(); 
        }
    }
}

void RM::finalizeProcesses() {
    int iter = 0;
    for (auto readyProcess : readyProcesses) {
        if (readyProcess->isFinished()) {
            readyProcess->subInstances();
            readyProcess->attStats(time);

            if (readyProcess->getInstances() == 0) {
                processesStats.push_back(readyProcess->getStats());
            }
            else {
                readyProcess->attRemainingTime();
                readyProcess->attStartTime();
            }
            
            if (readyProcess->getId() == currentProcess->getId()) {
                currentProcess = nullptr;
            }

            readyProcesses.erase(readyProcesses.cbegin()+iter);
        }
        iter++;
    }
}

void RM::printTimelineHeader() {
    Scheduler::printTimelineHeader();
}

void RM::printTimeline() {
    Scheduler::printTimeline();
}

void RM::printProcessesStats() {
    Scheduler::printProcessesStats();
}