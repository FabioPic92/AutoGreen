#ifndef TASK_H
#define TASK_H

#include "../MotorStepper/MotorStepper.hpp"
#include "../struct.hpp"

class Task {
private:
    MotorStepper m_motorStepper;
    TypeTask m_typeTask;
public:
    Task(){}
    Task(TypeTask typeTask, MotorStepper motorStepper)
    :   m_typeTask(typeTask), m_motorStepper(motorStepper)
    {}

    void execute() {
        if(m_typeTask == TypeTask::MOVE){
            Serial.println("Start Execution");
            m_motorStepper.execute();
            Serial.println("Stop Execution");
        }
    }
};

#endif