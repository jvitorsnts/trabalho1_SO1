#include <iostream>
#include <vector>
#include "../headers/Scheduler.h"

using namespace std;

void Scheduler::runScheduler() {
    printTimelineHeader();
    verifyProcessesToCreate();
    
    // O processesStats recebe os stats dos processos finalizados
    while (processes.size() != processesStats.size()) {
        if (readyProcesses.empty()) {
            printTimeline();
            time++;
            verifyProcessesToCreate();
        }
        else {
            scheduleNextProcess();
            currentProcess->run();
            printTimeline();
            time++;
            verifyProcessesToFinalize();
            finalizeProcesses();
            verifyProcessesToCreate();
        }
    }
    printProcessesStats();
}

void Scheduler::verifyProcessesToCreate() {
    for (const auto &process: processes) {
        if (process->getStartTime() == time) {
            process->create();
            if (readyProcesses.empty()) {
                readyProcesses.push_back(process);
            } 
            else {
                // Já ordena o vetor de processos prontos pela prioridade(menor periodo)
                int iter = 0;
                for (auto readyProcess : readyProcesses) {
                    if (process->getPriority() > readyProcess->getPriority()) {
                        break;
                    }
                    iter++;
                }
                readyProcesses.insert(readyProcesses.begin()+iter, process);
            }
        }
    }
}

void Scheduler::verifyProcessesToFinalize() {
    for (auto readyProcess : readyProcesses) {
        // Processo pode finalizar executando o tempo de computação necessário
        //     ou caso perda deadline 
        bool finalize = (readyProcess->getDeadline() == time-readyProcess->getStartTime())
                        or
                        (readyProcess->getRemainingTime() == 0);
        if (finalize) {
            readyProcess->finish(); 
        }
    }
}

void Scheduler::finalizeProcesses() {
    int iter = 0;
    vector<Process *> auxReadyProcesses = vector<Process *>();
    for (auto readyProcess : readyProcesses) {
        if (readyProcess->isFinished()) {
            // Processo finalizado pode ser o atual
            if (currentProcess != nullptr) {
                if (readyProcess->getId() == currentProcess->getId()) {
                    currentProcess = nullptr;
                }
            }
            
            // Reduz instâncias executadas
            readyProcess->subInstances();
            readyProcess->attStats(time);

            // Processo finalizado caso todas instâncias executadas,
            //    se não, prepara para execução de outra instância
            if (readyProcess->getInstances() == 0) {
                processesStats.push_back(readyProcess->getStats());
            } else {
                readyProcess->attRemainingTime();
                readyProcess->attStartTime();
            }
        } else {
            auxReadyProcesses.push_back(readyProcess);
        }
        iter++;
    }
    // Atualiza lista de processos
    readyProcesses.clear();
    readyProcesses = move(auxReadyProcesses);
}

void Scheduler::printProcessesStats() {
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
    for (const auto &processStats: processesStats) {
        averageWaitingTime += processStats.waitingTime;
    }
    averageWaitingTime /= processesStats.size();
    cout << "Tempo médio de espera: " << averageWaitingTime << " segundos." << endl;
    cout << "Trocas de contexto: " << contextSwitches << " vezes." << endl;
}

void Scheduler::printTimeline() {
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

void Scheduler::printTimelineHeader() {
    cout << "tempo\t";
    for (const auto &process: processes) {
        cout << "P" << process->getId() << "\t";
    }
    cout << endl;
}