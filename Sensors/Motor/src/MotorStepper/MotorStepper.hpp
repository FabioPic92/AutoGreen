#ifndef MOTOR_STEPPER_H
#define MOTOR_STEPPER_H

#include <AccelStepper.h>

#include "../struct.hpp"

const int stepPin = 4;
const int dirPin = 3; 

class MotorStepper{
private:
    int m_step;
    int m_duration;
    Direction m_direction;

public:
    MotorStepper() {}

    MotorStepper(int step, int duration, Direction direction) 
    :   m_step(step), m_duration(duration), m_direction(direction)
    {
        pinMode(stepPin, OUTPUT);
        pinMode(dirPin, OUTPUT);

        if(m_direction == Direction::FORWARD) {
            digitalWrite(dirPin, HIGH);
        } else {
            digitalWrite(dirPin, LOW);
        }
    }

    void execute()
    {
        for (int step = 0; step < m_duration; ++step) {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(m_step);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(m_step);
        }
    }
};

#endif