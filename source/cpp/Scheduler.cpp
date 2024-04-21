#include <iostream>
#include <vector>
#include "../headers/Scheduler.h"

using namespace std;

void Scheduler::runScheduler() {
    printTimelineHeader();
    verifyProcessesToCreate();
    
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
            if (currentProcess != nullptr) {
                if (readyProcess->getId() == currentProcess->getId()) {
                    currentProcess = nullptr;
                }
            }

            readyProcess->subInstances();
            readyProcess->attStats(time);
            // cout << readyProcess->getId() << "\t" << readyProcess->getInstances() << endl;
            if (readyProcess->getInstances() == 0) {
                // cout << readyProcess->getId() << endl;
                processesStats.push_back(readyProcess->getStats());
                // cout << processesStats.size() << " " << processes.size() << endl;
            } else {
                readyProcess->attRemainingTime();
                readyProcess->attStartTime();
            }
            // cout << "Processos finalizados: " << processesStats.size() << " " << "de " << processes.size() << endl;
            // readyProcesses.erase(readyProcesses.cbegin()+iter);
            // cout << processesStats.size() << endl;
        } else {
            auxReadyProcesses.push_back(readyProcess);
        }
        iter++;
    }
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
        //sum all waiting times and divide by number of processes
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