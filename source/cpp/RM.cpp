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
        // cout << processes.size() << processesStats.size() << endl;
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
            if (currentProcess != nullptr) {
                if (readyProcess->getId() == currentProcess->getId()) {
                    currentProcess = nullptr;
                }
            }

            readyProcess->subInstances();
            readyProcess->attStats(time);
            // cout << readyProcess->getId() << "\t" << readyProcess->getInstances() << endl;
            if (readyProcess->getInstances() == 0) {
                // cout << readyProcess->getId() << endl;
                processesStats.push_back(readyProcess->getStats());
                // cout << processesStats.size() << " " << processes.size() << endl;
            } else {
                readyProcess->attRemainingTime();
                readyProcess->attStartTime();
            }
            cout << "Processos finalizados: " << processesStats.size() << " " << "de " << processes.size() << endl;
            readyProcesses.erase(readyProcesses.cbegin()+iter);
            // cout << processesStats.size() << endl;
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