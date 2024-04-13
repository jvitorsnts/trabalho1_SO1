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

    Process(int id, int startTime, int duration, int period, int deadline, int priority);

    int getId() const;
    int getStartTime() const;
    int getDuration() const;
    int getPeriod() const;
    int getDeadline() const;
    int getPriority() const;
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
    PROCESS_STATE state;
    int remainingTime; // uma instancia de Process pode ser preemptada, entao precisamos saber quanto tempo falta para terminar
};


#endif //PROCESS_H
