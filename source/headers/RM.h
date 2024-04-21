//
// Created by joao on 13/04/2024.
//

#ifndef RM_H
#define RM_H

#include <vector>
#include "Process.h"
#include "Scheduler.h"

using namespace std;

class RM : public Scheduler {
public:

    explicit RM(vector<Process *> processes) {
        this->processes = move(processes);
    }

    void runScheduler() override;

private:

    vector<Process *> readyProcesses = vector<Process *>();
    void printTimelineHeader() override;
    void printTimeline() override;
    void printProcessesStats() override;
    void verifyProcessesToCreate() override;
    void scheduleNextProcess();
    void verifyProcessesToFinalize();
    void finalizeProcesses();
};

#endif //RM_H