#pragma once

class MinStack {
public:
    MinStack();
    ~MinStack();

    void push(int value);
    int  peek() const;
    int  pop();
    int  findMin() const;

    bool isEmpty() const;
    int  size() const;

private:
    struct Elem {
        int value;
        int currMin;
    };
    int _allocatedSize;
    int _numElements;
    Elem* _elems;
    void enlarge();
};

