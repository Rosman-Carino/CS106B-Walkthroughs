#include "ShapeOf.h"
#include "hashset.h"
using namespace std;

/**
 * @brief shapeOf: Returns the Shape of a Linked List.
 *              Implementation uses a HashSet
 * @param list
 * @return Shape can be the following:
 *      Linear
 *      Cycle
 *      Rho
 */
Shape shapeOf(Cell* list) {
    // General Case
    HashSet<Cell*> seen;
    Cell* current = list;
    // Iterate through the Linked List
    while (current != nullptr) {
        // We are seeing a Cell* again
        if (seen.contains(current)) {
            // Check if current is at the beginning of
            // our Linked List. If it is then we have
            // a Cylce
            if (current == list) {
                return Shape::CYCLE;
            }
            // Otherwise, this is a Rho
            return Shape::RHO;
        }
        // Add this Cell* to our Hashet
        if (!seen.contains(current)) {
            seen.add(current);
        }
        // Move our current pointer forward
        current = current->next;
    }
    // If we reach Nullptr (End of the List) then
    // there we have no Cy
    return Shape::LINEAR;

}

/* * * * * Test Cases Below This Point * * * * */
#include "GUI/SimpleTest.h"
#include "set.h"

/* Helper functions to make lists of the given shapes. */
namespace {
    struct Chain {
        Cell* head;
        Cell* tail;
    };

    /* Creates a linear list of the given length. */
    Chain chainOfSize(int length) {
        /* Validate input. */
        if (length < 0) {
            error("Negative lengths aren't allowed.");
        }

        Chain result;
        result.head = result.tail = nullptr;

        /* Build the list. */
        for (int i = 0; i < length; i++) {
            Cell* cell = new Cell;
            cell->value = 0;
            cell->next = nullptr;

            if (result.tail == nullptr) {
                result.head = result.tail = cell;
            } else {
                result.tail->next = cell;
                result.tail = cell;
            }
        }

        return result;
    }

    /* If you just want the first element of the chain. */
    Cell* linearOfSize(int length) {
        return chainOfSize(length).head;
    }

    /* Creates a loop of the given length. */
    Cell* cycleOfSize(int length) {
        /* Bounds-check. */
        if (length <= 0) {
            error("Invalid cycle length.");
        }

        /* Take a line and wrap it around itself. */
        auto linear = chainOfSize(length);
        linear.tail->next = linear.head;
        return linear.head;
    }

    /* Creates a rho of the given dimensions. */
    Cell* rhoOfSize(int chainLength, int cycleLength) {
        /* Validate inputs. */
        if (chainLength <= 0) {
            error("Bad chain length.");
        }
        if (cycleLength <= 0) {
            error("Bad cycle length.");
        }

        /* Stick a cycle onto a chain. */
        auto linear = chainOfSize(chainLength);
        linear.tail->next = cycleOfSize(cycleLength);
        return linear.head;
    }

    /* Cleans up a general list, which may be rho-shaped. */
    void freeGeneralList(Cell* list) {
        Set<Cell*> seen;
        while (list != nullptr && !seen.contains(list)) {
            /* Okay to store the pointer even though we're about to free it;
             * we are not going to follow it ever again.
             */
            seen += list;

            Cell* next = list->next;
            delete list;
            list = next;
        }
    }
}

PROVIDED_TEST("Works on reasonable examples of each shape.") {
    Cell* linear = linearOfSize(5);
    Cell* cycle  = cycleOfSize(5);
    Cell* rho    = rhoOfSize(5, 5);

    EXPECT_EQUAL(shapeOf(linear), Shape::LINEAR);
    EXPECT_EQUAL(shapeOf(cycle),  Shape::CYCLE);
    EXPECT_EQUAL(shapeOf(rho),    Shape::RHO);

    freeGeneralList(linear);
    freeGeneralList(cycle);
    freeGeneralList(rho);
}

PROVIDED_TEST("Works on trickier examples of each shape.") {
    Cell* linear = linearOfSize(1);
    Cell* cycle  = cycleOfSize(1);
    Cell* rho    = rhoOfSize(1, 1);

    EXPECT_EQUAL(shapeOf(linear), Shape::LINEAR);
    EXPECT_EQUAL(shapeOf(cycle),  Shape::CYCLE);
    EXPECT_EQUAL(shapeOf(rho),    Shape::RHO);

    freeGeneralList(linear);
    freeGeneralList(cycle);
    freeGeneralList(rho);
}

PROVIDED_TEST("Works on an empty list.") {
    /* It's linear, since there's no cycles anywhere. */
    EXPECT_EQUAL(shapeOf(nullptr), Shape::LINEAR);
}

