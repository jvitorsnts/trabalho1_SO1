//
// Created by gabri on 13/04/2024.
//

#include <iostream>
#include <vector>
#include "source/headers/RM.h"
#include "source/headers/EarliestDeadlineFirst.h"
#include "source/headers/Process.h"
#include "read_file.h"

using namespace std;

int main() {
    cout << "Bem vindo ao simulador de escalonamento de processos." << endl;
    cout << "Escolha o algoritmo a ser utizado da seguinte lista:" << endl;
    cout << "1 -> RM\n"
            "2 -> EDF\n" << endl;

    File f;
    f.read_file();

    vector<Process *> processes;

    // Cria os processos
    int i = 1;
    for (auto &p: f.get_processes()) {
        auto *newProcess = new Process(i,
                                        p->getCreationTime(),
                                        p->getDuration(),
                                        p->getPeriod(),
                                        p->getDeadline(),
                                        p->getPriority(),
                                        p->getInstances());
        processes.push_back(newProcess);
        i++;
    }

    // Escolhe entre os algoritmos de escalonamento
    Scheduler *scheduler;
    while (true) {
        cout << "Digite sua escolha: ";
        char choice;
        cin >> choice;
        cout << "\n";

        if (choice == '1') {
            scheduler = new RM(processes);
            scheduler->runScheduler();
            break;
        }
        else if (choice == '2') {
            scheduler = new EarliestDeadlineFirst(processes);
            scheduler->runScheduler();
            break;
        }
        else {
            cout << "Opção inválida" << endl;
            continue;
        }
    }

    delete scheduler;
}


