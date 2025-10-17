#include "BarycenterFractal.h"
#include "error.h"
using namespace std;

void drawBarycenterFractal(const GPoint& p0,
                           const GPoint& p1,
                           const GPoint& p2,
                           int order) {
    // Error Check
    if (order < 0) {
        error("ERROR! NO NEGATIVE ORDER!");
    }
    // Base Case: Order-0 Fractal - Just a Triangle
    if (order == 0) {
        drawLine(p0, p1);
        drawLine(p0, p2);
        drawLine(p2, p1);
        return;
    }
    // Recursive Case: Making the problem smaller
    // and handing off that work
    // to the next recursive call

    // Step 1: Calculate BaryCenter and Midpoints
    GPoint baryCenter = {(p0.x + p1.x + p2.x) / 3,
                         (p0.y + p1.y + p2.y) / 3};
    GPoint midPointP01 = {(p0.x + p1.x) / 2,
                          (p0.y + p1.y) / 2};
    GPoint midPointP02 = {(p0.x + p2.x) / 2,
                          (p0.y + p2.y) / 2};
    GPoint midPointP12 = {(p1.x + p2.x) / 2,
                          (p1.y + p2.y) / 2};
    // Step 2: Recurse
    drawBarycenterFractal(p0, baryCenter, midPointP01, order - 1);
    drawBarycenterFractal(p0, midPointP02, baryCenter, order - 1);
    drawBarycenterFractal(midPointP02, p2, baryCenter, order - 1);
    drawBarycenterFractal(baryCenter, p2, midPointP12, order - 1);
    drawBarycenterFractal(baryCenter, midPointP12, p1, order - 1);
    drawBarycenterFractal(midPointP01, baryCenter, p1, order - 1);
}

/* * * * * Test Cases Below This Point * * * * */
#include "GUI/SimpleTest.h"

PROVIDED_TEST("An order-0 triangle is just a triangle.") {
    /* Track all lines that are drawn. */
    LineCatcher catcher;

    drawBarycenterFractal({0, 0}, {1, 0}, {0, 1}, 0);

    EXPECT(areSameLines(catcher.linesDrawn(), {
                    { { 0, 0 }, { 1, 0 } },
                    { { 1, 0 }, { 0, 1 } },
                    { { 0, 1 }, { 0, 0 } },
           }));
}

PROVIDED_TEST("Negative orders trigger errors.") {
    EXPECT_ERROR(drawBarycenterFractal({0, 0}, {1, 0}, {0, 1}, -1));
    EXPECT_ERROR(drawBarycenterFractal({0, 0}, {1, 0}, {0, 1}, -137));
}

PROVIDED_TEST("Order-1 triangles consist of six smaller triangles.") {
    /* Track all lines that are drawn. */
    LineCatcher catcher;

    drawBarycenterFractal({0, 0}, {6, 0}, {0, 6}, 1);

    EXPECT(areSameLines(catcher.linesDrawn(), {
                            {{0, 0}, {3, 0}},
                            {{3, 0}, {2, 2}},
                            {{2, 2}, {0, 0}},
                            {{0, 0}, {0, 3}},
                            {{0, 3}, {2, 2}},
                            {{2, 2}, {0, 0}},
                            {{6, 0}, {3, 0}},
                            {{3, 0}, {2, 2}},
                            {{2, 2}, {6, 0}},
                            {{6, 0}, {3, 3}},
                            {{3, 3}, {2, 2}},
                            {{2, 2}, {6, 0}},
                            {{0, 6}, {0, 3}},
                            {{0, 3}, {2, 2}},
                            {{2, 2}, {0, 6}},
                            {{0, 6}, {3, 3}},
                            {{3, 3}, {2, 2}},
                            {{2, 2}, {0, 6}}
                 }));
}

PROVIDED_TEST("Order-2 curves consist of four lines.") {
    /* Track all lines that are drawn. */
    LineCatcher catcher;

    drawBarycenterFractal({0, 0}, {36, 0}, {0, 36}, 2);

    EXPECT(areSameLines(catcher.linesDrawn(), {
                            {{0, 0}, {9, 0}},
                            {{9, 0}, {10, 4}},
                            {{10, 4}, {0, 0}},
                            {{0, 0}, {6, 6}},
                            {{6, 6}, {10, 4}},
                            {{10, 4}, {0, 0}},
                            {{18, 0}, {9, 0}},
                            {{9, 0}, {10, 4}},
                            {{10, 4}, {18, 0}},
                            {{18, 0}, {15, 6}},
                            {{15, 6}, {10, 4}},
                            {{10, 4}, {18, 0}},
                            {{12, 12}, {6, 6}},
                            {{6, 6}, {10, 4}},
                            {{10, 4}, {12, 12}},
                            {{12, 12}, {15, 6}},
                            {{15, 6}, {10, 4}},
                            {{10, 4}, {12, 12}},
                            {{0, 0}, {0, 9}},
                            {{0, 9}, {4, 10}},
                            {{4, 10}, {0, 0}},
                            {{0, 0}, {6, 6}},
                            {{6, 6}, {4, 10}},
                            {{4, 10}, {0, 0}},
                            {{0, 18}, {0, 9}},
                            {{0, 9}, {4, 10}},
                            {{4, 10}, {0, 18}},
                            {{0, 18}, {6, 15}},
                            {{6, 15}, {4, 10}},
                            {{4, 10}, {0, 18}},
                            {{12, 12}, {6, 6}},
                            {{6, 6}, {4, 10}},
                            {{4, 10}, {12, 12}},
                            {{12, 12}, {6, 15}},
                            {{6, 15}, {4, 10}},
                            {{4, 10}, {12, 12}},
                            {{36, 0}, {27, 0}},
                            {{27, 0}, {22, 4}},
                            {{22, 4}, {36, 0}},
                            {{36, 0}, {24, 6}},
                            {{24, 6}, {22, 4}},
                            {{22, 4}, {36, 0}},
                            {{18, 0}, {27, 0}},
                            {{27, 0}, {22, 4}},
                            {{22, 4}, {18, 0}},
                            {{18, 0}, {15, 6}},
                            {{15, 6}, {22, 4}},
                            {{22, 4}, {18, 0}},
                            {{12, 12}, {24, 6}},
                            {{24, 6}, {22, 4}},
                            {{22, 4}, {12, 12}},
                            {{12, 12}, {15, 6}},
                            {{15, 6}, {22, 4}},
                            {{22, 4}, {12, 12}},
                            {{36, 0}, {27, 9}},
                            {{27, 9}, {22, 10}},
                            {{22, 10}, {36, 0}},
                            {{36, 0}, {24, 6}},
                            {{24, 6}, {22, 10}},
                            {{22, 10}, {36, 0}},
                            {{18, 18}, {27, 9}},
                            {{27, 9}, {22, 10}},
                            {{22, 10}, {18, 18}},
                            {{18, 18}, {15, 15}},
                            {{15, 15}, {22, 10}},
                            {{22, 10}, {18, 18}},
                            {{12, 12}, {24, 6}},
                            {{24, 6}, {22, 10}},
                            {{22, 10}, {12, 12}},
                            {{12, 12}, {15, 15}},
                            {{15, 15}, {22, 10}},
                            {{22, 10}, {12, 12}},
                            {{0, 36}, {0, 27}},
                            {{0, 27}, {4, 22}},
                            {{4, 22}, {0, 36}},
                            {{0, 36}, {6, 24}},
                            {{6, 24}, {4, 22}},
                            {{4, 22}, {0, 36}},
                            {{0, 18}, {0, 27}},
                            {{0, 27}, {4, 22}},
                            {{4, 22}, {0, 18}},
                            {{0, 18}, {6, 15}},
                            {{6, 15}, {4, 22}},
                            {{4, 22}, {0, 18}},
                            {{12, 12}, {6, 24}},
                            {{6, 24}, {4, 22}},
                            {{4, 22}, {12, 12}},
                            {{12, 12}, {6, 15}},
                            {{6, 15}, {4, 22}},
                            {{4, 22}, {12, 12}},
                            {{0, 36}, {9, 27}},
                            {{9, 27}, {10, 22}},
                            {{10, 22}, {0, 36}},
                            {{0, 36}, {6, 24}},
                            {{6, 24}, {10, 22}},
                            {{10, 22}, {0, 36}},
                            {{18, 18}, {9, 27}},
                            {{9, 27}, {10, 22}},
                            {{10, 22}, {18, 18}},
                            {{18, 18}, {15, 15}},
                            {{15, 15}, {10, 22}},
                            {{10, 22}, {18, 18}},
                            {{12, 12}, {6, 24}},
                            {{6, 24}, {10, 22}},
                            {{10, 22}, {12, 12}},
                            {{12, 12}, {15, 15}},
                            {{15, 15}, {10, 22}},
                            {{10, 22}, {12, 12}}
                        }));
}
