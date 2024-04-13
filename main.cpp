//
// Created by gabri on 13/04/2024.
//
#include "source/headers/Process.h"
#include "read_file.h"

#include <iostream>


int main() {
    std::cout << "TODO: adicionar algoritmos de escalonamento" << std::endl;

    File f;
    f.read_file();

    std::vector<Process *> processes;

    int i = 1;
    for (auto &p: f.get_processes()) {
          auto *newProcess = new Process(i, p->getCreationTime(), p->getDuration(), p->getPeriod(), p->getDeadline(), p->getPriority());
            processes.push_back(newProcess);
            i++;
    }

    // TODO: adicionar algoritmos de escalonamento
    // por enquanto apenas imprime os processos

    for(auto &p: processes) {
        std::cout << "Processo " << p->getId() << std::endl;
        std::cout << "Tempo de criação: " << p->getStartTime() << std::endl;
        std::cout << "Duração: " << p->getDuration() << std::endl;
        std::cout << "Período: " << p->getPeriod() << std::endl;
        std::cout << "Deadline: " << p->getDeadline() << std::endl;
        std::cout << "Prioridade: " << p->getPriority() << std::endl;
        std::cout << std::endl;
    }

}


