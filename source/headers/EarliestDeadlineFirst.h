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

    // Construtor
    EarliestDeadlineFirst(vector<Process *> processes);

private:

    // Compara deadlines entre processos
    static bool compareByDeadline(const Process& p1, const Process& p2);
    
    // Escalona próximo processo
    void scheduleNextProcess() override;
};



#endif //EARLIESTDEADLINEFIRST_H