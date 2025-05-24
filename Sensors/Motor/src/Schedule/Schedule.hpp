#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Queue.hpp"

class Schedule{
private:
    Queue m_queue;
public:
    Schedule() {
        Schedule::instance = this;
    }

    void AddTask(const MotorTask& task) {
        m_queue.writeTask(task);
    }

    MotorTask RemoveTask() {
        return m_queue.readTask();
    }

    bool isEmpty() {
        return m_queue.isEmpty();
    } 

    bool execute() {
        while(!m_queue.isEmpty()){
            MotorTask task = RemoveTask();
            task.execute();
            Serial.println("Remove");
        }
        return true;
    }

    void updateSchedule(uint16_t step, uint16_t duration, Direction dir) {
        int iStep = static_cast<int>(step);
        int iDuration = static_cast<int>(duration);
        MotorStepper motorStpper(iStep, iDuration, dir); 
        MotorTask task(TypeMotorTask::MOVE, motorStpper);
        Serial.println("Add");
        AddTask(task);
    }

    static void handleMqttMessage(uint16_t step, uint16_t duration, Direction dir) {
        if (instance != nullptr) {
            instance->updateSchedule(step, duration, dir);
        }
    }

private:
    static Schedule* instance;
};

Schedule* Schedule::instance = nullptr;

#endif