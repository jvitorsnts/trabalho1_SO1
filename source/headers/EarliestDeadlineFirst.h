#ifndef EARLIESTDEADLINEFIRST_H
#define EARLIESTDEADLINEFIRST_H

#include <array>
#include <vector>
#include "Register.h"
#include "Process.h"
#include "Scheduler.h"

class EarliestDeadlineFirst : public Scheduler {
private:
    int currentTime;
public:
    EarliestDeadlineFirst(vector<Process *> processes);
    void runScheduler() override;
   

private:
    vector<Process *> readyProcesses = vector<Process *>();

    static bool compareByDeadline(const Process& p1, const Process& p2);
    void printTimelineHeader() override;
    void printTimeline() override;
    void printProcessesStats() override;
    void verifyProcessesToCreate() override;
    void scheduleNextProcess();
    void verifyProcessesToFinalize();
    void finalizeProcesses();
};



#endif //EARLIESTDEADLINEFIRST_H