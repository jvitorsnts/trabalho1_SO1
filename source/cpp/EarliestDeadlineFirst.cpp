#include "../headers/EarliestDeadlineFirst.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

EarliestDeadlineFirst::EarliestDeadlineFirst(vector<Process *> processes) {
    this->processes = move(processes);
}

void EarliestDeadlineFirst::runScheduler() {
    printTimelineHeader();
    verifyProcessesToCreate();
        
    while (processes.size() != processesStats.size()) {
        // cout << "TESTES  " << processes.size() << "  " << processesStats.size() << "  " << readyProcesses.size() << endl;
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

void EarliestDeadlineFirst::verifyProcessesToCreate() {
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
                        break;
                    }
                    iter++;
                }
                readyProcesses.insert(readyProcesses.begin()+iter, process);
            }
        }
    }
}

void EarliestDeadlineFirst::verifyProcessesToFinalize() {
    for (auto readyProcess : readyProcesses) {
        bool finalize = (readyProcess->getDeadline() == time-readyProcess->getStartTime())
                        or
                        (readyProcess->getRemainingTime() == 0);
        if (finalize) {
            readyProcess->finish(); 
        }
    }
}

void EarliestDeadlineFirst::finalizeProcesses() {
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
            //cout << processesStats.size() << " " << processes.size() << endl;
            readyProcesses.erase(readyProcesses.cbegin()+iter);
            // cout << processesStats.size() << endl;
        }
        iter++;
    }
}

void EarliestDeadlineFirst::printTimelineHeader() {
    Scheduler::printTimelineHeader();
}

void EarliestDeadlineFirst::printTimeline() {
    Scheduler::printTimeline();
}

void EarliestDeadlineFirst::printProcessesStats() {
    Scheduler::printProcessesStats();
}

void EarliestDeadlineFirst::scheduleNextProcess() {
    Process *nextProcessIt = nullptr;
    for (auto readyProcess : readyProcesses) {
        //cout << "readyProcess   " << readyProcess->getRelativeDeadline() << "   " << endl;
        //if(nextProcessIt != nullptr){
        //   cout << "nextProcessIt   "<< nextProcessIt->getRelativeDeadline() << endl;
        //}
        if (nextProcessIt == nullptr || readyProcess->getRelativeDeadline() < nextProcessIt->getRelativeDeadline()) {
            nextProcessIt = readyProcess;
        }
    }

    if(currentProcess != nullptr && currentProcess != nextProcessIt){
        currentProcess->preempt();
        contextSwitches++;
    }
    currentProcess = nextProcessIt;
}
