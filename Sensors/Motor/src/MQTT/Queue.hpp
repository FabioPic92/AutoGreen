#ifndef VECTOR_QUEUE_H
#define VECTOR_QUEUE_H

const int sizeVector = 10;

enum TypeTask {
    PHOTO,
    IDLE
};

struct Task {
    TypeTask m_typeTask;
    int m_timeStep;
    int m_step;

    // Task(TypeTask typeTask, int timeStep, int step)
    // : m_typeTask(typeTask), m_timeStep(timeStep), m_step(step)
    // {}
};

class Queue {
private:
    Task m_vecQueue[sizeVector];
    int m_indexWrite;
    int m_indexRead;

public:
    Queue()
    : m_indexWrite(0), m_indexRead(0)
    {}

    bool writeTask(Task newTask) {
      if(!isEmpty()){
        m_vecQueue[m_indexWrite] = newTask;
        m_indexWrite = (m_indexWrite + 1) % sizeVector;
      }
      return false;
    }

    Task readTask() {
        if(m_indexWrite != m_indexRead)
        {
            Task task = m_vecQueue[m_indexRead];
            m_indexRead = (m_indexRead + 1) % sizeVector;
            return task;
        }
        Task task;
        return task;
    }

    bool isEmpty() {
      return m_indexWrite == m_indexRead;
    }
};

#endif