#ifndef MOTOR_STEPPER_H
#define MOTOR_STEPPER_H

#include <AccelStepper.h>

const int stepPin = 3;
const int dirPlusPin = 2; 
const int dirMinusPin = 4;

class MotorStepper{
public:
    MotorStepper(int step) 
      : m_step(step)
    {
        pinMode(stepPin, OUTPUT);
        pinMode(dirPlusPin, OUTPUT);
        pinMode(dirMinusPin, OUTPUT);

        digitalWrite(dirPlusPin, HIGH);
        digitalWrite(dirMinusPin, LOW);
    }

    void step(){
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(20);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(20); 
    }

    void PositiveRotate(){
        digitalWrite(dirPlusPin, HIGH);
        digitalWrite(dirMinusPin, LOW);
    }

    void NegativeRotate(){
        digitalWrite(dirPlusPin, LOW);
        digitalWrite(dirMinusPin, HIGH);
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