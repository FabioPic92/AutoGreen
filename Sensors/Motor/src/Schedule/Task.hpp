#ifndef TASK_H
#define TASK_H

#include "../MotorStepper/MotorStepper.hpp"
#include "../struct.hpp"

class MotorTask {
private:
    MotorStepper m_motorStepper;

    TypeMotorTask m_typeTask;

public:
    MotorTask(){}
    MotorTask(TypeMotorTask typeTask, MotorStepper motorStepper)
    :   m_typeTask(typeTask), m_motorStepper(motorStepper)
    {}

    void execute() {
        if(m_typeTask == TypeMotorTask::MOVE){
            Serial.println("Start Execution");
            m_motorStepper.execute();
            Serial.println("Stop Execution");
        }
    }
};

#endif