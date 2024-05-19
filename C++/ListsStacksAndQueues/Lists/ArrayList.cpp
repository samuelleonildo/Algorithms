#include "List.h"
#include <iostream>

using namespace std;


void assert(bool condition, const string msg){

    if (!condition)
        throw runtime_error(msg);
}


template <typename E>
class ArrayList : public List<E> {

private:

    int maxSize;
    int listSize;
    int curr;
    E* listArray;

public:
    
    explicit ArrayList(int size = 1) { // constructor

        maxSize = size;
        listSize = curr = 0;
        listArray = new E[maxSize];
    }

    ~ArrayList() override { delete [] listArray; }

    void clear() override {

        delete [] listArray;
        listSize = 0;
        listArray = new E[maxSize];
    }

    void insert(const E& it) override {

        if (listSize < maxSize){

            for (size_t i = listSize; i > curr; i--)
                listArray[i] = listArray[i - 1];
            
            listArray[curr] = it;
            listSize++;
        }
    }

    void append(const E& it) override {

        if (listSize < maxSize)
            listArray[listSize++] = it;
    }

    E remove() override {

        if (!(curr >= 0 && curr < listSize))
            return NULL;

        E it = listArray[curr];

        for (size_t i = curr; i < listSize+1; i++)
            listArray[i] = listArray[i+1];
        
        listSize--;
        return it;
    }

    void moveToStart() override { curr = 0; }

    void moveToEnd() override { curr = listSize; }

    void prev() override { if (curr != 0) curr--; }

    void next() override { if (curr < listSize) curr++; }

    int lenght() const override { return listSize; }

    int currPos() const override { return curr; }

    void moveToPos(int pos) override {

        if (pos >= 0 && pos <= listSize)
            curr = pos;
    }

    const E& getValue() const override {

        if (curr >= 0 && curr < listSize)
            return listArray[curr];
    }
};
