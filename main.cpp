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

    // Todo: adicionar saida
    // turnaround time
    // tempo medio de espera
    // numero total de trocas de contexto
    // numero total de deadlines perdidos de cada processo
    // diagrama do tempo de execução dos processos


// exemplo de saida
// tempo P1 P2 P3 P4
// 0- 1 ## --
// 1- 2 ## -- --
// 2- 3 -- ## --
// 3- 4 -- ## -- --
// 4- 5 -- ## --
// 5- 6 -- ## --
// 6- 7 ## -- --
// 7- 8 ## -- --
// 8- 9 -- -- ##
// 9-10 -- -- ##
// 10-11 -- ## --
// 11-12 -- ## --
// 12-13 ## --
// 13-14 ##

    // ## significa que o processo esta em execucao
    // -- significa que o processo ja foi criado e esta esperando para ser executado
    // " " (espaco em branco) significa que o processo ainda nao foi criado ou ja terminou

 // cada processo deve ter as seguintes informacoes:
    // identificador
    // datas de início e de conclusão
    // duração (tempo necessário no processador)
    // prioridades estática e dinâmica (se houver)
    // estado atual (novo, pronto, executando, terminado)
    // tempo já executado (total e no quantum atual)
    // … (outros campos podem ser necessários para algumas políticas de
    // escalonamento)

//     Além disso, o programa de simulação deve abstrair o contexto de um processador (CPU)
// hipotético chamado INE5412 que possui 6 registradores de propósito geral, SP (stack
// pointer), PC (program counter) e ST (status), todos com 64 bits.

}


