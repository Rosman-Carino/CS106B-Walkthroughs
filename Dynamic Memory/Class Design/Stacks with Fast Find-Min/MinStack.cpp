#include "MinStack.h"
#include "error.h"
using namespace std;

const int K_INIT_SIZE = 10;

/**
 * @brief MinStack::MinStack: Constructor
 */
MinStack::MinStack() {
    _allocatedSize = K_INIT_SIZE;
    _numElements = 0;
    _elems = new Elem[_allocatedSize];
}

/**
 * @brief MinStack::~MinStack: Destructor
 */
MinStack::~MinStack() {
    delete [] _elems;

}

/**
 * @brief MinStack::peek: Return the value at the top of the Stack,
 *                      but do NOT remove it from the Stack
 * @return
 */
int MinStack::peek() const {
    if (isEmpty()) {
        error("ERROR! EMPTY STACK!");
    }
    return _elems[_numElements - 1].value;
}

/**
 * @brief MinStack::pop: Return the value at the top of the Stack and
 *                  remove it from the Stack
 * @return
 */
int MinStack::pop() {
    int value = peek();
    _numElements--;
    return value;
}

/**
 * @brief MinStack::enlarge: Make the array larger by a factor of 2.
 */
void MinStack::enlarge() {
    // Step 1: Make Allocated Size bigger by 2
    _allocatedSize *= 2;
    // Step 2: Create our Bigger Dynamic Array twice the size
    Elem* biggerElems = new Elem[_allocatedSize];
    // Step 3: Copy the data from _elems to BiggerElems
    for (int i = 0; i < _numElements; i++) {
        biggerElems[i].value = _elems[i].value;
        biggerElems[i].currMin = _elems[i].currMin;
    }
    // Step 4: Deallocate what _elems is pointing at
    delete [] _elems;
    // Step 5: Set _elems to be biggerElems
    _elems = biggerElems;
}

/**
 * @brief MinStack::push: Push a value to the Stack
 * @param value
 */
void MinStack::push(int value) {
    if (_numElements == _allocatedSize) {
        enlarge();
    }
    _elems[_numElements].value = value;
    // Update Min Value

    // Edge Case: What if the Stack is Empty?
    if (isEmpty()) {
        _elems[_numElements].currMin = value;
    } else {
        // Update the Min with what is currently at the top of the
        // Stack
        if (_elems[_numElements - 1].currMin < _elems[_numElements].value) {
            _elems[_numElements].currMin = _elems[_numElements - 1].currMin;
        } else {
            _elems[_numElements].currMin = value;

        }
    }
    _numElements++;
}

/**
 * @brief MinStack::findMin: Return the min value for the Stack
 * @return
 */
int MinStack::findMin() const {
    if (isEmpty()) {
        error("ERROR! EMPTY STACK!");
    }
    return _elems[_numElements - 1].currMin;
}

/**
 * @brief MinStack::size: Return the size of the Stack
 * @return
 */
int MinStack::size() const {
    return _numElements;
}

/**
 * @brief MinStack::isEmpty: Check where the Stack is Empty
 * @return
 */
bool MinStack::isEmpty() const {
    return _numElements == 0;
}

/* * * * * Test Cases Below This Point * * * * */
#include "GUI/SimpleTest.h"

PROVIDED_TEST("Basic correctness checks.") {
    MinStack stack;

    EXPECT_EQUAL(stack.isEmpty(), true);
    EXPECT_EQUAL(stack.size(), 0);
    EXPECT_ERROR(stack.peek());
    EXPECT_ERROR(stack.pop());
    EXPECT_ERROR(stack.findMin());

    stack.push(3);
    stack.push(1);
    stack.push(2);

    EXPECT_EQUAL(stack.size(), 3);
    EXPECT_EQUAL(stack.isEmpty(), false);
    EXPECT_EQUAL(stack.findMin(), 1);
    EXPECT_EQUAL(stack.peek(), 2);
    EXPECT_EQUAL(stack.pop(), 2);

    EXPECT_EQUAL(stack.size(), 2);
    EXPECT_EQUAL(stack.isEmpty(), false);
    EXPECT_EQUAL(stack.findMin(), 1);
    EXPECT_EQUAL(stack.peek(), 1);
    EXPECT_EQUAL(stack.pop(), 1);

    EXPECT_EQUAL(stack.size(), 1);
    EXPECT_EQUAL(stack.isEmpty(), false);
    EXPECT_EQUAL(stack.findMin(), 3);
    EXPECT_EQUAL(stack.peek(), 3);
    EXPECT_EQUAL(stack.pop(), 3);

    EXPECT_EQUAL(stack.isEmpty(), true);
    EXPECT_EQUAL(stack.size(), 0);
    EXPECT_ERROR(stack.peek());
    EXPECT_ERROR(stack.pop());
    EXPECT_ERROR(stack.findMin());
}

PROVIDED_TEST("Finds the min as it regularly changes.") {
    MinStack stack;

    for (int i = 0; i < 100; i++) {
        stack.push(100 - i);
        EXPECT_EQUAL(stack.findMin(), 100 - i);
        stack.push(100 + i);
        EXPECT_EQUAL(stack.findMin(), 100 - i);
    }

    for (int i = 99; i >= 0; i--) {
        EXPECT_EQUAL(stack.findMin(), 100 - i);
        EXPECT_EQUAL(stack.pop(), 100 + i);
        EXPECT_EQUAL(stack.findMin(), 100 - i);
        EXPECT_EQUAL(stack.pop(), 100 - i);
    }
}

PROVIDED_TEST("Stress test: Works when the min is buried.") {
    MinStack stack;

    EXPECT_COMPLETES_IN(0.1,
        for (int i = 0; i < 100000; i++) {
            stack.push(i);
            EXPECT_EQUAL(stack.findMin(), 0);
        }
        stack.push(-1);
        for (int i = 100000; i < 200000; i++) {
            stack.push(i);
            EXPECT_EQUAL(stack.findMin(), -1);
        }
        for (int i = 199999; i >= 100000; i--) {
            EXPECT_EQUAL(stack.pop(), i);
            EXPECT_EQUAL(stack.findMin(), -1);
        }
        EXPECT_EQUAL(stack.pop(), -1);
        for (int i = 99999; i >= 0; i--) {
            EXPECT_EQUAL(stack.findMin(), 0);
            EXPECT_EQUAL(stack.pop(), i);
        }
    );
}
