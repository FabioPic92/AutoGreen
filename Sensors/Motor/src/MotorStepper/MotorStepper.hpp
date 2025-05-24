#ifndef MOTOR_STEPPER_H
#define MOTOR_STEPPER_H

#include <AccelStepper.h>

const int stepPin = 4;
const int dirPin = 3; 

class MotorStepper{
public:
    MotorStepper(int step) 
      : m_step(step)
    {
        pinMode(stepPin, OUTPUT);
        pinMode(dirPin, OUTPUT);

        digitalWrite(dirPin, HIGH);
    }

    void step(){
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(500); 
    }

    void setSpeed(int step){
        if(step > 0){
            m_step = step;
        }
        Serial.println(m_step);
    }

private:
    int m_step;
};

#endif