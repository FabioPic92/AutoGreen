#ifndef VECTOR_QUEUE_H
#define VECTOR_QUEUE_H

#include "Task.hpp"

const int sizeVector = 10;

class Queue {
private:
    MotorTask m_vecQueue[sizeVector];
    int m_indexWrite;
    int m_indexRead;

public:
    Queue()
    : m_indexWrite(0), m_indexRead(0)
    {}

    bool writeTask(MotorTask newTask) {
      if(isEmpty()){
        m_vecQueue[m_indexWrite] = newTask;
        m_indexWrite = (m_indexWrite + 1) % sizeVector;
      }
      return false;
    }

    MotorTask readTask() {
        if(m_indexWrite != m_indexRead)
        {
            MotorTask task = m_vecQueue[m_indexRead];
            m_indexRead = (m_indexRead + 1) % sizeVector;
            return task;
        }
        return MotorTask();
    }

    bool isEmpty() {
      return m_indexWrite == m_indexRead;
    }
};

#endif