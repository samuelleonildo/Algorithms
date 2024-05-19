#ifndef _LIST_H
#define _LIST_H
#endif


template <typename E> class List {

private:

    void operator = (const List&) {}
    List(const List&);

public:

    List() {} // Constructor
    virtual ~List() {} // Destructor

    virtual void clear() = 0;

    virtual void insert(const E& item) = 0;

    virtual void append(const E& item) = 0;

    virtual E remove() = 0;

    virtual void moveToStart() = 0;

    virtual void moveToEnd() = 0;

    virtual void prev() = 0;

    virtual void next() = 0;

    virtual int lenght() const = 0;

    virtual int currPos() const = 0;

    virtual void moveToPos(int pos) = 0;

    virtual const E& getValue() const = 0;
    
};
