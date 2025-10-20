#pragma once

#include "GUI/SimpleTest.h"
#include "GUI/MemoryDiagnostics.h"
#include <string>

class MoveToFrontSet {
public:
    MoveToFrontSet();  // Creates an empty set
    ~MoveToFrontSet(); // Cleans up all memory allocated

    /* Returns whether str is in the set. If so, moves it to the front. */
    bool contains(const std::string& str);

    /* Adds str to the set if it isn't already there. Either way, str ends
     * up at the front of the set.
     */
    void add(const std::string& str);

    /* Removes str from the set. If it isn't present in the set, the list
     * is not modified or reordered.
     */
    void remove(const std::string& str);

private:
    struct Cell {
        std::string value;
        Cell* next;

        TRACK_ALLOCATIONS_OF(Cell);
    };

    Cell* head;
    Cell* createCell(const std::string& str);

    ALLOW_TEST_ACCESS();
};
