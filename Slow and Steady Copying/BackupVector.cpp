#include "BackupVector.h"
using namespace std;

/* Initial size of the large array. (The small array is not allocated until
 * the large array is full.)
 */
const int K_INITIAL_SIZE = 2;

/**
 * @brief BackupVector::BackupVector: Constructor
 */
BackupVector::BackupVector() {
    _allocatedSize = K_INITIAL_SIZE;
    _numElems = 0;
    small = nullptr;
    large = new int[_allocatedSize];
}

/**
 * @brief BackupVector::~BackupVector: Destructor
 */
BackupVector::~BackupVector() {
    delete [] small;
    delete [] large;
}

/**
 * @brief BackupVector::growLargeArray: Grow the Large Array
 */
void BackupVector::growLargeArray() {
    if (small != nullptr) {
        delete [] small;
    }
    small = large;
    _allocatedSize *= 2;
    large = new int[_allocatedSize];
    large[_numElems - 1] = small[_numElems - 1];
}

/**
 * @brief BackupVector::append: Add a value to the BackupVector
 * @param toAdd
 */
void BackupVector::append(int toAdd) {
    if (_numElems == _allocatedSize) {
        growLargeArray();
    }
    large[_numElems] = toAdd;
    _numElems++;
    if (small != nullptr) {
        int indexLocation = _allocatedSize - _numElems;
        large[indexLocation] = small[indexLocation];
    }
}

/**
 * @brief BackupVector::get: Get a value from a respective index
 * @param index
 * @return
 */
int BackupVector::get(int index) const {
    if (index < 0 || index > _numElems - 1) {
        error("ERROR! Invalid index: Out of Range!");
    }
    int value = 0;
    // Talk about turning 2 into a CONST!
    if (index < _allocatedSize / 2) {
        value = small[index];
    } else {
        value = large[index];
    }
    return value;
}

/**
 * @brief BackupVector::size: Return the size of the BackupVector
 * @return
 */
int BackupVector::size() const {
    return _numElems;
}

/**
 * @brief BackupVector::isEmpty: Return whether or not the BackupVector is
 *                                                  empty.
 * @return
 */
bool BackupVector::isEmpty() const {
    return _numElems == 0;
}

/* * * * * Test Cases Below This Point * * * * */
#include "GUI/SimpleTest.h"

PROVIDED_TEST("Grows from size 0 to size 5.") {
    /* Small: (null)
     * Large: _ _
     */
    BackupVector v;
    EXPECT_EQUAL(v.small, nullptr);
    EXPECT_NOT_EQUAL(v.large, nullptr);

    EXPECT(v.isEmpty());
    EXPECT_EQUAL(v.size(), 0);

    /* Small: (null)
     * Large: 0 1
     */
    v.append(0);
    v.append(1);
    EXPECT_EQUAL(v.large[0], 0);
    EXPECT_EQUAL(v.large[1], 1);

    int* oldLarge = v.large;

    /* Small: 0 ?
     * Large: _ 1 2 _
     */
    v.append(2);

    /* Confirm the small/large pointers changed. */
    EXPECT_EQUAL(v.small, oldLarge);
    EXPECT_NOT_EQUAL(v.large, oldLarge);

    /* Confirm values are there. */
    EXPECT_EQUAL(v.small[0], 0);
    EXPECT_EQUAL(v.large[1], 1);
    EXPECT_EQUAL(v.large[2], 2);

    /* Small: ? ?
     * Large: 0 1 2 3
     */
    int* oldSmall = v.small;
    oldLarge = v.large;

    v.append(3);

    /* No new allocations / deallocations should have happened. */
    EXPECT_EQUAL(v.small, oldSmall);
    EXPECT_EQUAL(v.large, oldLarge);

    /* Confirm values are there. */
    EXPECT_EQUAL(v.large[0], 0);
    EXPECT_EQUAL(v.large[1], 1);
    EXPECT_EQUAL(v.large[2], 2);
    EXPECT_EQUAL(v.large[3], 3);

    oldSmall = v.small;
    oldLarge = v.large;
    v.append(4);

    /* Small: 0 1 2 ?
     * Large: _ _ _ 3 4 _ _ _
     */
    EXPECT_EQUAL(v.small, oldLarge);
    EXPECT_NOT_EQUAL(v.large, oldLarge);

    EXPECT_EQUAL(v.small[0], 0);
    EXPECT_EQUAL(v.small[1], 1);
    EXPECT_EQUAL(v.small[2], 2);
    EXPECT_EQUAL(v.large[3], 3);
    EXPECT_EQUAL(v.large[4], 4);
}

PROVIDED_TEST("Lookups work after a small series appends.") {
    BackupVector v;

    const int kNumItems = 10;

    for (int i = 0; i < kNumItems; i++) {
        v.append(i);
    }

    EXPECT_EQUAL(v.size(), kNumItems);

    for (int i = 0; i < kNumItems; i++) {
        EXPECT_EQUAL(v.get(i), i);
    }
}

PROVIDED_TEST("Handles out-of-range lookups.") {
    BackupVector v;

    EXPECT_ERROR(v.get(0));
    EXPECT_ERROR(v.get(-1));
    EXPECT_ERROR(v.get(137));

    v.append(0);
    v.append(1);
    v.append(2);

    EXPECT_ERROR(v.get(-1));
    EXPECT_ERROR(v.get(137));
}

PROVIDED_TEST("Stress test: Can perform 1,000,000 appends and lookups (should take at most half a second).") {
    BackupVector v;
    const int kNumItems = 1000000;


    EXPECT_COMPLETES_IN(0.5,
        for (int i = 0; i < kNumItems; i++) {
            v.append(i);
        }

        EXPECT_EQUAL(v.size(), kNumItems);

        for (int i = 0; i < kNumItems; i++) {
            EXPECT_EQUAL(v.get(i), i);
        }
    );
}
