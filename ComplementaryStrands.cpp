#include "ComplementaryStrands.h"
#include "error.h"
#include "vector.h"
using namespace std;

/* Returns whether the two strands are complementary. */
bool areComplementaryStrands(string one, string two) {
    // Pre-Check: Both strings have to be the same size
    if (one.size() != two.size()) {
        return false;
    }
    // Base Case: Simplest Problem
    if (one == "" && two == "") {
        return true;
    }
    // Check the Complement
    if (one[0] == 'A' && two[0] !='T' ||
        one[0] == 'T' && two[0] != 'A') {
        return false;
    }
    // Check the Complement
    if (one[0] == 'C' && two[0] !='G' ||
        one[0] == 'G' && two[0] != 'C') {
        return false;
    }
    // Recursive Case: Make the problem smaller and hand off the
    // work to the next recursive call
    return areComplementaryStrands(one.substr(1), two.substr(1));
}

/* * * * * Test Cases Below This Point * * * * */
#include "GUI/SimpleTest.h"

PROVIDED_TEST("Works on strands of the same length.") {
    EXPECT(areComplementaryStrands("ACTG",  "TGAC"));
    EXPECT(areComplementaryStrands("AAA",   "TTT"));
    EXPECT(!areComplementaryStrands("AAA",  "TTC"));
    EXPECT(!areComplementaryStrands("AAA",  "TCT"));
    EXPECT(!areComplementaryStrands("AAA",  "CTT"));
}

PROVIDED_TEST("Works when strings have different lengths.") {
    EXPECT(!areComplementaryStrands("AAA", "TT"));
    EXPECT(!areComplementaryStrands("AAA", "TTTT"));
}

PROVIDED_TEST("Works on the empty string.") {
    EXPECT(areComplementaryStrands("", ""));
    EXPECT(!areComplementaryStrands("A", ""));
    EXPECT(!areComplementaryStrands("", "A"));
}
