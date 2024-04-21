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
    
    // Destrutor
    virtual ~Scheduler() {
        for (auto &processes: processes) {
            delete processes;
        }
    }

protected:
    
    // Verifica se tem processos para criar, cria e adiciona no vector de prontos
    void verifyProcessesToCreate();

    // Printa o cabeçalho do diagrama de tempo
    void printTimelineHeader();

    // Printa o diagrama de tempo do estado atual de cada processo
    void printTimeline();

    // printa os stats de cada processo(id, turnarroundtime, tempo médio de espera, deadlines perdidos)
    void printProcessesStats();

    // Escalona próximo processo
    virtual void scheduleNextProcess() = 0;

    // Verifica quais processos tem que ser finalizados
    void verifyProcessesToFinalize();

    // Finaliza os procesos e atualiza aqueles com mais instancias
    void finalizeProcesses();
    
    int time = 0;
    int contextSwitches = 0;
    vector<Process *> processes;
    Process *currentProcess = nullptr;
    ProcessContext workingContext = ProcessContext();
    vector<Process::ProcessStats> processesStats;
    vector<Process *> readyProcesses = vector<Process *>();

public:
    void runScheduler();
};

#endif //SCHEDULER_H