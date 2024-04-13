//
// Created by gabri on 13/04/2024.
//

#include "../headers/Process.h"
#include <iostream>
using namespace std;

Process::Process(int id, int startTime, int duration, int period, int deadline, int priority) {
    this->id = id;
    this->startTime = startTime;
    this->duration = duration;
    this->period = period;
    this->deadline = deadline;
    this->priority = priority;
    this->state = CREATED;
    remainingTime = duration;
}

int Process::getId() const {
    return id;
}

int Process::getStartTime() const {
    return startTime;
}

int Process::getDuration() const {
    return duration;
}

int Process::getPeriod() const {
    return period;
}

int Process::getDeadline() const {
    return deadline;
}

int Process::getPriority() const {
    return priority;
}

Process::PROCESS_STATE Process::getState() const {
    return state;
}

void Process::create() {
    state = READY;
}

void Process::run() {
    if (remainingTime > 0) {
        state = RUNNING;
        remainingTime--;
    } else {
        state = FINISHED;
    }
}

void Process::preempt() {
    state = READY;
}

void Process::finish() {
    state = FINISHED;
}

bool Process::isRunning() const {
    return state == PROCESS_STATE::RUNNING;
}

bool Process::isFinished() const {
    return remainingTime == 0;
}


