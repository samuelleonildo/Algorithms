#include <iostream>
#include "Queue.h"

using namespace std;


template <typename E>
class ArrayQueue : public Queue<E> {

private:

    int maxSize;
    int front;
    int rear;
    E* queueArray;

public:

    ArrayQueue(int size = 1) {

        maxSize = size + 1;
        rear = 0;
        front = 1;
        queueArray = new E[maxSize];
    }
    
    ~ArrayQueue() { delete[] queueArray; }

    virtual int lenght() const {

        return ((rear + maxSize) - front + 1) % maxSize;
    }

    void clear() {

        rear = 0;
        front = 1;    
    }

    void enqueue(const E& it) {

        if (((rear + 2) % maxSize) != front){

            rear = (rear + 1) % maxSize;
            queueArray[rear] = it;
        }
    }

    E dequeue() {

        if (lenght() != 0) {

            E it = queueArray[front];
            front = (front + 1) % maxSize;

            return it;
        }

        return NULL; // Warning
    }

    const E& frontValue() const {

        if (lenght() != 0)
            return queueArray[front];
        
        return NULL; // Warning
    }
};
