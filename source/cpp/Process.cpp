//
// Created by gabri on 13/04/2024.
//

#include "../headers/Process.h"
#include <iostream>

using namespace std;

Process::Process(int id, int startTime, int duration, int period, int deadline, int priority, int instances) {
    this->id = id;
    this->startTime = startTime;
    this->duration = duration;
    this->period = period;
    this->deadline = deadline;
    this->priority = priority;
    this->remainingTime = duration;
    this->instances = instances;
    this->state = CREATED;
    stats.id = id;
    stats.turnarroundTime = 0;
    stats.missedDeadlines = 0;
    stats.waitingTime = 0;
}

int Process::getId() const {
    return id;
}

int Process::getStartTime() {
    return startTime;
}

void Process::attStartTime() {
    int newStartTime = startTime + period;
    startTime = newStartTime;
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

int Process::getRelativeDeadline() {
    return startTime+deadline;
}

int Process::getPriority() const {
    return priority;
}

int Process::getRemainingTime() {
    return remainingTime;
}

void Process::attRemainingTime() {
    remainingTime = this->duration;
}

int Process::getInstances() {
    return instances;
}

void Process::subInstances() {
    instances--;
}

void Process::attStats(int time) {
    int auxTurnarroundTime = time - startTime;
    stats.turnarroundTime += auxTurnarroundTime;
    stats.waitingTime += auxTurnarroundTime + remainingTime-duration;
    if(remainingTime > 0) stats.missedDeadlines++;
}

Process::ProcessStats Process::getStats() {
    return stats;
}

Process::PROCESS_STATE Process::getState() const {
    return state;
}

void Process::create() {
    state = READY;
}

void Process::run() {
    state = RUNNING;
    remainingTime--;
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
    return state == PROCESS_STATE::FINISHED;
}
