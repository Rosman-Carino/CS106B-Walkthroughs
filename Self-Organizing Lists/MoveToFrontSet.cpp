#include "MoveToFrontSet.h"
using namespace std;

/**
 * @brief MoveToFrontSet::MoveToFrontSet: Constructor
 */
MoveToFrontSet::MoveToFrontSet() {
    head = nullptr;
}

/**
 * @brief MoveToFrontSet::~MoveToFrontSet: Destructor
 */
MoveToFrontSet::~MoveToFrontSet() {
    while(head != nullptr) {
        Cell* next = head->next;
        delete head;
        head = next;
    }
}

/**
 * @brief MoveToFrontSet::contains: Checks to see
 *          if str is in Linked List. If it is then
 *          we move the Cell containing str to the
 *          front of the Linked List.
 * @param str
 * @return
 */
bool MoveToFrontSet::contains(const string& str) {
    Cell* current = head;
    Cell* previous = nullptr;
    // Iterate through our Linked List and find `str`
    // Use prev and current approach

    // Approach 1: Using a break condition
    while (current != nullptr) {
        if (current->value == str) {
            break;
        }
        previous = current;
        current = current->next;
    }

    // Approach 2: Combining the logic
    // while (current != nullptr && current->value != str) {
    //     previous = current;
    //     current = current->next;
    // }

    // We need to do some checks on current
    if (current == nullptr) {
        // We iterated through the entire Linked List
        // Because current is at nullptr, we did not
        // find str in the Linked List
        return false;
    }
    // We found str and make sure that it is not head.
    // If str is at head then there is no need to do
    // the rewiring
    if (current != head) {
        previous->next = current->next;
        current->next = head;
        head = current;
    }
    // If we got to this point then either str is at head
    // or at another location which we did rewiring so we
    // can return true;
    return true;
}

/**
 * @brief ::MoveToFrontSet::Cell: Create's a new cell
 * @param str
 * @return
 */
MoveToFrontSet::Cell* MoveToFrontSet::createCell(const string& str) {
    Cell* newCell = new Cell();
    newCell->value = str;
    newCell->next = nullptr;
    return newCell;
}

/**
 * @brief MoveToFrontSet::add: Add data to the
 *          Linked List at the front using
 *          Head Insertion method.
 * @param str
 */
void MoveToFrontSet::add(const string& str) {
    // If str is alread in Linked List then it will
    // be moved to the front of the Linked List and
    // we can just return to exit out and not continue
    // with the rest of the function
    if (contains(str))  {
        return;
    }
    // Otherwise, if str is not in Linked List we
    // perform Head Insertion
    Cell* newCell = createCell(str);
    newCell->next = head;
    head = newCell;
}

/**
 * @brief MoveToFrontSet::remove: Remove data from
 *          Linked List. First check to see if it is
 *          there and if it is then we remove it.
 * @param str
 */
void MoveToFrontSet::remove(const std::string& str) {
    // Check to see if str is in the Linked List
    // If it is not then we can just exit out of here
    // with return
    if (!contains(str)) {
        return;
    }
    // Because str is in the Linked List then we can
    // rewire because we moved it at the front.
    Cell* trash = head;
    head = trash->next;
    delete trash;
}

/* * * * * Test Cases Below This Point * * * * */
#include "GUI/SimpleTest.h"

PROVIDED_TEST("add.") {
    MoveToFrontSet s;

    EXPECT_EQUAL(s.head, nullptr);

    // a
    s.add("a");
    EXPECT_NOT_EQUAL(s.head, nullptr);
    auto* a = s.head;


    // b a
    s.add("b");
    EXPECT_NOT_EQUAL(s.head, a);
    auto* b = s.head;

    EXPECT_EQUAL(b->next, a);
    EXPECT_EQUAL(a->next, nullptr);

    // c b a
    s.add("c");
    EXPECT_NOT_EQUAL(s.head, a);
    auto* c = s.head;

    EXPECT_EQUAL(c->next, b);
    EXPECT_EQUAL(b->next, a);
    EXPECT_EQUAL(a->next, nullptr);
}

PROVIDED_TEST("contains.") {
    MoveToFrontSet s;

    // c b a
    s.add("a");
    s.add("b");
    s.add("c");

    auto* c = s.head;
    auto* b = c->next;
    auto* a = b->next;

    // a c b
    EXPECT(s.contains("a"));
    EXPECT_EQUAL(s.head, a);
    EXPECT_EQUAL(a->next, c);
    EXPECT_EQUAL(c->next, b);
    EXPECT_EQUAL(b->next, nullptr);

    EXPECT(!s.contains("d"));
    EXPECT_EQUAL(s.head, a);
    EXPECT_EQUAL(a->next, c);
    EXPECT_EQUAL(c->next, b);
    EXPECT_EQUAL(b->next, nullptr);
}

PROVIDED_TEST("remove.") {
    MoveToFrontSet s;

    // c b a
    s.add("a");
    s.add("b");
    s.add("c");

    auto* c = s.head;
    auto* b = c->next;
    auto* a = b->next;

    // c a
    s.remove("b");
    EXPECT_EQUAL(s.head, c);
    EXPECT_EQUAL(c->next, a);
    EXPECT_EQUAL(a->next, nullptr);

    // a
    s.remove("c");
    EXPECT_EQUAL(s.head, a);
    EXPECT_EQUAL(a->next, nullptr);

    s.remove("a");
    EXPECT_EQUAL(s.head, nullptr);
}
