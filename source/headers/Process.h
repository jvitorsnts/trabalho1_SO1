//
// Created by gabri on 13/04/2024.
//

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

    Process(int id, int startTime, int duration, int period, int deadline, int priority, int instances);

    int getId() const;
    int getStartTime();
    void attStartTime();
    int getDuration() const;
    int getPeriod() const;
    int getDeadline() const;
    int getPriority() const;
    int getRemainingTime();
    void attRemainingTime();
    int getInstances();
    void subInstances();
    void attStats(int time);
    ProcessStats getStats();
    PROCESS_STATE getState() const;

    void create();
    void run();
    void preempt();
    void finish();

    bool isRunning() const;

    bool isFinished() const;

private:
    int id;
    int startTime;
    int duration;
    int period;
    int deadline;
    int priority;
    int remainingTime; // uma instancia de Process pode ser preemptada, entao precisamos saber quanto tempo falta para terminar
    int instances;
    PROCESS_STATE state;
    ProcessStats stats;
};


#endif //PROCESS_H
