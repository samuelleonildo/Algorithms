#include <iostream>
#include "List.h"

using namespace std;


void assert(bool condition, const string msg){

    if (!condition)
        throw runtime_error(msg);
}


template <typename E>
class Link {

public:

    E element;
    Link* next;

    Link(const E& elemval, Link* nextval=nullptr){

        element = elemval;
        next = nextval;
    }

    Link(Link* nextval=nullptr){

        next = nextval;
    }
};


template <typename E>
class LinkedList : public List<E> {

private:

    Link<E>* head;
    Link<E>* tail;
    Link<E>* curr;
    int listSize;

    void init() {

        curr = tail = head = new Link<E>;
        listSize = 0;
    }

    void remove_all() {

        while (head != nullptr) {

            curr = head;
            head = head->next;
            delete curr;
        }
    }

public:

    LinkedList(int size = 0) { init(); }

    ~LinkedList() { remove_all(); }

    void print() const;

    void clear() {

        remove_all();
        init();
    }

    void insert(const E& it) override {

        curr->next = new Link<E> (it, curr->next);

        if (tail == curr)
            tail = curr->next;

        listSize++;
    }

    void append(const E& it) override {

        tail = tail->next = new Link<E>(it, nullptr);
        listSize++;
    }

    E remove() {

        if (curr->next == nullptr)
            return NULL;

        E it = curr->next->element;

        Link<E>* ltemp = curr->next;

        if (tail == curr->next)
            tail = curr;

        curr->next = curr->next->next;
        delete ltemp;
        listSize--;
        return it;
    }

    void moveToStart() { curr = head; }

    void moveToEnd() { curr = tail; }

    void prev() {

        if (curr == head)
            return;
        
        Link<E>* temp = head;

        while (temp->next != curr)
            temp = temp->next;
        
        curr = temp;
    }

    void next() {

        if (curr != tail)
            curr = curr->next;
    }

    int lenght() const { return listSize; }

    int currPos() const {

        Link<E>* temp = head;

        int i;
        for (i = 0; curr != temp; i++){

            temp = temp->next;
        }

        return i;
    }

    void moveToPos(int pos) {

        if (pos >= 0 && pos <= listSize){

            curr = head;

            for (size_t i = 0; i < pos; i++)
                curr = curr->next;
        }
    }

    const E& getValue() const {

        if (curr->next == nullptr)
            return NULL;

        return curr->next->element;
    }
};
