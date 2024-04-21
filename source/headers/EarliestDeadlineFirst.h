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
   

private:
    static bool compareByDeadline(const Process& p1, const Process& p2);
    void scheduleNextProcess() override;
};



#endif //EARLIESTDEADLINEFIRST_H