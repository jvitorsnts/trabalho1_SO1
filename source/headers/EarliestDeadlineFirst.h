#ifndef EARLIESTDEADLINEFIRST_H
#define EARLIESTDEADLINEFIRST_H

#include <array>
#include <vector>
#include "Process.h"
#include "Scheduler.h"

class EarliestDeadlineFirst : public Scheduler {
public:

    // Construtor
    EarliestDeadlineFirst(vector<Process *> processes);

private:
    
    // Escalona próximo processo
    void scheduleNextProcess() override;
};



#endif //EARLIESTDEADLINEFIRST_H