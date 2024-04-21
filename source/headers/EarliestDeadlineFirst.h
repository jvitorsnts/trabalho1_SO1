#ifndef EARLIESTDEADLINEFIRST_H
#define EARLIESTDEADLINEFIRST_H

#include <array>
#include <vector>
#include "Register.h"
#include "Process.h"

class EarliestDeadlineFirst {
private:
    std::vector<Process> processes;
    int currentTime;
public:
    EarliestDeadlineFirst();
    void scheduleNextProcess();
    void addProcess(const Process& process);
    void schedule();
    bool hasActiveProcesses();
    void scheduleOneTimeUnit();
    int getCurrentTime();

private:
    static bool compareByDeadline(const Process& p1, const Process& p2);
};



#endif //EARLIESTDEADLINEFIRST_H