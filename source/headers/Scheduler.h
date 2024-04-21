//
// Created by joao on 13/04/2024.
//

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include "Process.h"
#include "ProcessContext.h"


using namespace std;

class Scheduler {
public:
    
    virtual ~Scheduler() {
        for (auto &processes: processes) {
            delete processes;
        }
    }

protected:

    void verifyProcessesToCreate();

    void printTimelineHeader();
    void printTimeline();
    void printProcessesStats();
    virtual void scheduleNextProcess() = 0;
    void verifyProcessesToFinalize();
    void finalizeProcesses();
    
    int time = 0;
    int contextSwitches = 0;
    vector<Process *> processes;
    Process *currentProcess = nullptr;
    ProcessContext workingContext = ProcessContext();
    vector<Process::ProcessStats> processesStats;
    vector<Process *> readyProcesses = vector<Process *>();

public:
    void runScheduler();
};

#endif //SCHEDULER_H