#ifndef RM_H
#define RM_H

#include <vector>
#include "Process.h"
#include "Scheduler.h"

class RM : public Scheduler {
public:
    
    // Construtor
    RM(vector<Process *> processes);

private:
    
    // Escalona próximo processo
    void scheduleNextProcess() override;
    
};

#endif //RM_H