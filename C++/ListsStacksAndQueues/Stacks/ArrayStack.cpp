#include <iostream>
#include "Stack.h"

using namespace std;


template <typename E>
class ArrayStack : public Stack<E> {

private:

    int maxSize;
    int top;
    E* stackArray;

public:

    ArrayStack(int size = 1) {

        maxSize = size;
        top = 0;
        stackArray = new E[size];
    }

    ~ArrayStack() { delete[] stackArray; }

    void clear() { top = 0; }

    void push(const E& it) {

        if (top != maxSize)
            stackArray[top++] = it;
    }

    E pop() {

        if (top != 0)
            return stackArray[--top];

        return NULL; // Warning
    }

    const E& topValue() const {

        if (top != 0)
            return stackArray[top - 1];

        return NULL; // Warning
    }

    int lenght() const { return top; }

};
