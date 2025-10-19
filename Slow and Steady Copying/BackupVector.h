#pragma once
#include "GUI/SimpleTest.h"

class BackupVector {
public:
    BackupVector();
    ~BackupVector();

    /* Appends a new value to the vector. */
    void append(int toAdd);

    /* Returns the value at the given index. Calls error() if the index is
     * out of bounds.
     */
    int get(int index) const;

    /* Size of the vector, and whether it's empty. */
    int  size() const;
    bool isEmpty() const;

private:
    /* The two arrays. */
    int* small;
    int* large;

    /* The rest is up to you! */

    int _allocatedSize;
    int _numElems;
    void growLargeArray();

    ALLOW_TEST_ACCESS();
};
