#include "../headers/INE5412.h"
#include "../headers/Process.h"

INE5412::INE5412() {
    R1 = -1;
    R2 = -1;
    R3 = -1;
    R4 = -1;
    R5 = -1;
    ST = INE5412::CPU_STATE::NOT_RUNNING;
    PC = nullptr;
}

INE5412::~INE5412() {
}

void INE5412::setContext(Process *runningProcess) {
    bool newProcess = false;
    if (SP.empty()) {
        newProcess = true;
    } else {
        for (auto process: SP) {
            if (runningProcess->getId() == process.id) {
                newProcess = true;
                break;
            }
        }
    }

    if (newProcess) {
        Process::ProcessContext context;
        context.id = runningProcess->getId();
        context.duration = runningProcess->getDuration();
        context.period = runningProcess->getPeriod();
        context.deadline = runningProcess->getDeadline();
        context.priority = runningProcess->getPriority();
        SP.push_back(context);
        R1 = runningProcess->getId();
        R2 = runningProcess->getDuration();
        R3 = runningProcess->getPeriod();
        R4 = runningProcess->getDeadline();
        R5 = runningProcess->getPriority();
    } else {
        for (auto process: SP) {
            if (runningProcess->getId() == process.id) {
                R1 = process.id;
                R2 = process.duration;
                R3 = process.period;
                R4 = process.deadline;
                R5 = process.priority;                
            }
        }
    }
    PC = runningProcess;
    ST = INE5412::CPU_STATE::RUNNING;
}

void INE5412::clearContext() {
    R1 = -1;
    R2 = -1;
    R3 = -1;
    R4 = -1;
    R5 = -1;
    ST = INE5412::CPU_STATE::NOT_RUNNING;
    PC = nullptr;
}