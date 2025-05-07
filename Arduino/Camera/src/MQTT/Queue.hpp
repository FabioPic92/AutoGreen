#ifndef VECTOR_QUEUE_H
#define VECTOR_QUEUE_H

#include <cstring> 

const int sizeVector = 10;

enum TypeTask {
    MOVE,
    PHOTO,
    IDLE
};

struct Task{
    TypeTask typeTask;
    int timeStep;
    int step;
};

class Queue{
private:
    Task vecQueue[sizeVector];
    int indexWrite;
    int indexRead;

public:
    Queue()
    : indexWrite(0), indexRead(0)
    {}

    bool writeTask(Task newTask){
      if(!isEmpty()){
        vecQueue[indexWrite] = newTask;
        indexWrite = (indexWrite + 1) % sizeVector;
      }
      return false;
    }

    Task readTask(){
        if(indexWrite != indexRead)
        {
            Task task = vecQueue[indexRead];
            indexRead = (indexRead + 1) % sizeVector;
            return task;
        }

    }

    bool isEmpty(){
      return indexWrite == indexRead;
    }

};

#endif