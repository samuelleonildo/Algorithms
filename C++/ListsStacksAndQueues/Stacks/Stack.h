#include <iostream>
#ifndef STACK_H
#define STACK_H

template <typename E>
class Stack {

private:

    void operator = (const Stack&) {}
    Stack(const Stack&) {}

public:

    Stack() {}
    virtual ~Stack() {}

    virtual void clear() = 0;

    virtual void push(const E& it) = 0;

    virtual E pop() = 0;

    virtual const E& topValue() const = 0;

    virtual int lenght() const = 0;

};

#endif
