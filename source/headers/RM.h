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


private:

    void scheduleNextProcess() override;
    
};

#endif //RM_H