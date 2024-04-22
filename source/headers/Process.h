#ifndef PROCESS_H
#define PROCESS_H

class Process {
public:

    enum PROCESS_STATE {
        CREATED,
        READY,
        RUNNING,
        FINISHED
    };
    typedef struct ProcessStats {
        int id;
        int turnarroundTime;
        int waitingTime;
        int missedDeadlines;
    } ProcessStats;

    typedef struct ProcessContext {
        int id;
        int duration;
        int period;
        int deadline;
        int priority;
    } ProcessContext;

    // Construtor
    Process(int id, int startTime, int duration, int period, int deadline, int priority, int instances);

    // Retorna o id
    int getId() const;

    // Retorna o tempo de inicio
    int getStartTime();

    // Atualiza o tempo de inicio conforme o tempo de inicio e periodo, 
    //     para processos com mais instâncias
    void attStartTime();

    // Retorna duração
    int getDuration() const;

    // Retorna o periodo
    int getPeriod() const;

    // Retorna o deadline
    int getDeadline() const;

    // Retorna a prioridade
    int getPriority() const;

    // Retorna o tempo restante
    int getRemainingTime();

    // Atualiza o tempo restante, para processos com mais instâncias
    void attRemainingTime();

    // Retorna o numero de instâncias
    int getInstances();

    // Diminui o número de instâncias
    void subInstances();

    // Atualiza o stats
    void attStats(int time);

    // Retorna os stats
    ProcessStats getStats();

    // Retorna o estado
    PROCESS_STATE getState() const;

    // Retorna o deadline relativo, usado no EDF
    int getRelativeDeadline();

    // Cria processo, state = READY
    void create();

    // Execução de um periodo de tempo da instância, diminui remainingTime, state = RUNNING
    void run();

    // Preempta processo, state = READY
    void preempt();

    // Finaliza processo, state = finish
    void finish();

    // Retorna se o processo está finalizado
    bool isFinished() const;

private:
    int id;
    int startTime;
    int duration;
    int period;
    int deadline;
    int priority;
    int remainingTime; // Tempo restante de execução da instância de um processo
    int instances;
    PROCESS_STATE state;
    ProcessStats stats;
};


#endif //PROCESS_H
