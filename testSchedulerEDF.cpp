

#include "source/headers/Process.h"
#include "source/headers/EarliestDeadlineFirst.h"
#include <iostream>

void testSchedulerEDF() {
    // Criar o escalonador
    EarliestDeadlineFirst scheduler;

    // Adicionar os processos
    scheduler.addProcess(Process(0, 0, 5, 10, 10, 1));
    scheduler.addProcess(Process(1, 0, 2, 4, 4, 2));
    scheduler.addProcess(Process(2, 1, 4, 8, 8, 3));
    scheduler.addProcess(Process(3, 3, 3, 6, 6, 4));

    // Simular a execução até que todos os processos tenham terminado
    while (scheduler.hasActiveProcesses()) {
        scheduler.scheduleOneTimeUnit();
    }
}

int main() {
    testSchedulerEDF();
    return 0;
}