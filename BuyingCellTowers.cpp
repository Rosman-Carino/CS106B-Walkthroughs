#include "BuyingCellTowers.h"
using namespace std;

/**
 * @brief totalPopulation: Calculates the population for soFar by using
 *              the values from towns.
 * @param towns
 * @param soFar
 * @return
 */
int totalPopulation(const Vector<int>& towns, const Vector<bool> soFar) {
    // In my solution I did not handle the error check,
    // but I will handle that to you
    int result = 0;
    for (int i = 0; i < soFar.size(); i++) {
        if (soFar[i]) {
            result += towns[i];
        }
    }
    return result;
}

/**
 * @brief bestCellTowersForHelper: Recursive Helper that does all the work for our wrapper
 * @param towns
 * @param soFar
 * @param currIndex
 * @return
 */
Vector<bool> bestCellTowersForHelper(const Vector<int>& towns, const Vector<bool>& soFar, int currIndex) {
    // Base Case: There are no remaining towns left
    if (towns.size() == soFar.size()) {
        return soFar;
    }

    // Base Case: There is only 1 city then we might as well put a cell tower there
    if (towns.size() == currIndex + 1) { // Recall: CurrIndex will be in-bounds so we need to add a +1
                                                    // to compare it to town.size()
        return soFar + true;
    }

    // This is the variable we're going to return at the end
    Vector<bool> best = {};
    // Recursive Case: Iterate through our all our options of towns
    for(int i = 0; i < towns.size(); i++) {
        // What choices can I do with this current town?
        // 1. We can include a cell tower at the current town, but we can't put one to the left or right
        Vector<bool> with = bestCellTowersForHelper(towns, soFar + true + false, currIndex + 2);

        // 2. We can exclude a cell tower at the current town and move on
        Vector<bool> without = bestCellTowersForHelper(towns, soFar + false, currIndex + 1);

        // Perform Max between with and without options
        int withPopulation = totalPopulation(towns, with);
        int withoutPopulation = totalPopulation(towns, without);
        // if (withPopulation > withoutPopulation) {
        //     best = with;
        // } else {
        //     best = without;
        // }
        best = withPopulation > withoutPopulation ? with : without;
    }
    return best;
}

/**
 * @brief bestCellTowersFor: Wrapper Function
 * @param towns
 * @return
 */
Vector<bool> bestCellTowersFor(const Vector<int>& towns) {
    return bestCellTowersForHelper(towns, {}, 0);
}


/* * * * * Test Cases Below This Point * * * * */
#include "GUI/SimpleTest.h"

PROVIDED_TEST("Doesn't always pick the highest-population town.") {
    EXPECT_EQUAL(bestCellTowersFor({ 100, 101, 100 }), { true, false, true });
}

PROVIDED_TEST("Doesn't always zebra-stripe.") {
    EXPECT_EQUAL(bestCellTowersFor({ 100, 1, 1, 100 }), { true, false, false, true });
}

PROVIDED_TEST("Works for the {8, 3, 4, 9} example.") {
    EXPECT_EQUAL(bestCellTowersFor({ 8, 3, 4, 9 }), { true, false, false, true });
}

PROVIDED_TEST("Works for the {137, 106, 107, 166, 103, 261, 109} example.") {
    EXPECT_EQUAL(bestCellTowersFor({137, 106, 107, 166, 103, 261, 109}),
                 { true, false, false, true, false, true, false });
}
