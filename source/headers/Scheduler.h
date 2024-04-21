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

    virtual void verifyProcessesToCreate() = 0;

    virtual void printTimelineHeader() {
        cout << "tempo\t";
        for (const auto &process: processes) {
            cout << "P" << process->getId() << "\t";
        }
        cout << endl;
    }

    virtual void printTimeline() {
        cout << setw(2) << time << "-" << setw(2) << time + 1 << "\t";
        for (const auto &process: processes) {
            if (process->getState() == Process::PROCESS_STATE::RUNNING) {
                cout << "##\t";
            } else if (process->getState() == Process::PROCESS_STATE::READY) {
                cout << "--\t";
            } else {
                cout << "  \t";
            }
        }
        cout << std::endl;
    }

    virtual void printProcessesStats() {
        sort(processesStats.begin(), processesStats.end(),
                  [](const Process::ProcessStats &a, const Process::ProcessStats &b) -> bool {
                      return a.id < b.id;
                  });
        cout << "\nProcesso\tTurnaround\tWaiting\t\tDealines Perdidos" << endl;
        for (const auto &processStats: processesStats) {
            cout << processStats.id 
                    <<"\t\t"
                    << processStats.turnarroundTime
                    << "\t\t"
                    << processStats.waitingTime
                    << "\t\t"
                    << processStats.missedDeadlines << endl;
        }
        cout << endl;
        float averageWaitingTime = 0;
        //sum all waiting times and divide by number of processes
        for (const auto &processStats: processesStats) {
            averageWaitingTime += processStats.waitingTime;
        }
        averageWaitingTime /= processesStats.size();
        cout << "Tempo médio de espera: " << averageWaitingTime << " segundos." << endl;
        cout << "Trocas de contexto: " << contextSwitches << " vezes." << endl;
    }
    
    int time = 0;
    int contextSwitches = 0;
    vector<Process *> processes;
    Process *currentProcess = nullptr;
    ProcessContext workingContext = ProcessContext();
    vector<Process::ProcessStats> processesStats;

public:
    virtual void runScheduler() = 0;
};

#endif //SCHEDULER_H