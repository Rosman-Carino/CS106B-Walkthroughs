#include "BarnstormingBrainstorming.h"
#include "vector.h"
#include "set.h"
#include <cmath>
using namespace std;

/**
 * Returns the Euclidean distance between two points.
 *
 * @param one The first point.
 * @param two The second point.
 * @return The distance between them.
 */
double distanceBetween(const GPoint& one, const GPoint& two) {
    double dx = one.x - two.x;
    double dy = one.y - two.y;
    return sqrt(dx * dx + dy * dy);
}

bool canVisitAllSitesHelper(const Set<GPoint>& sites,
                      double timeAvailable,
                      const GPoint currPoint) {
    // Base Case 1: Failure Case & Pruning Case
    if (timeAvailable < 0)  {
        return false;
    }

    // Base Case 2: Success Case: There are no more sites to visit!
    // No matter how much time we have, we have already visited
    // everything
    if (sites.isEmpty()) {
        return true;
    }
    // Recursive Case: Iterate through all the possible points
    // at my disposal
    for (GPoint nextPoint : sites) {
        // Step 1: Calculate the distance from our currPoint to
        // nextPoint
        double timeDistance = distanceBetween(currPoint,
                                                   nextPoint);

        // Step 2: Remove the nextPoint from sites, update our
        // available time, and update our currPoint to be
        // nextPoint and then recursion
        bool canVisitSites = canVisitAllSitesHelper(sites - nextPoint,
                                timeAvailable - timeDistance,
                                                    nextPoint);
        // If this worked! Great, let's return it!
        if (canVisitSites) {
            return true;
        }
    }
    // After exhaustively looking through all the points we were unable
    // to visit the entire sites.
    return false;
}

bool canVisitAllSites(const Set<GPoint>& sites, double timeAvailable) {
    // Error Check:
    if (timeAvailable < 0) {
        error("ERROR! NO Negative Time!");
    }
    // We get lucky that the sites are empty
    if (sites.isEmpty()) {
        return true;
    }
    // Recursive Case: Iterate through all the points
    // and kick start the recursive process into our helper
    for (GPoint point : sites) {
        // We need to try a starting point so let's remove it
        // and set it as our extra parameter in our helper function
        bool canVisit = canVisitAllSitesHelper(sites - point,
                                               timeAvailable,
                                               point);
        if (canVisit) {
            return true;
        }
    }
    // After exhaustively looking through all the points none of them
    // as the starting position worked
    return false;
}

/* * * * * Test Cases Below This Point * * * * */
#include "GUI/SimpleTest.h"

/* We want our test cases to work for canVisitAllSites both if you are on part (i)
 * or on part (ii) of this problem. To do this, we've set things up so that you
 * can use this function, which will call the right version of canVisitAllSites based
 * on which version you've written.
 */
namespace {
    /* Dispatch as appropriate. */
    bool invoke(bool callback(const Set<GPoint>&, double, Vector<GPoint>&),
                const Set<GPoint>& points, double maxDistance, Vector<GPoint>& result) {
        return callback(points, maxDistance, result);
    }
    bool invoke(bool callback(const Set<GPoint>&, double),
                const Set<GPoint>& points, double maxDistance, Vector<GPoint>& result) {
        (void) result;
        return callback(points, maxDistance);
    }

    /* Suppress compiler warnings. */
    bool quiet1(const Set<GPoint>&, double, Vector<GPoint>&) {
        return false;
    }
    bool quiet2(const Set<GPoint>&, double) {
        return false;
    }
    void quietPlease() {
        Vector<GPoint> dummy;
        (void) dummy;
        (void) invoke(quiet1, {}, 0, dummy);
        (void) invoke(quiet2, {}, 0, dummy);
    }

    bool testCanVisit(const Set<GPoint>& points,
                      double maxLength,
                      Vector<GPoint>& result) {
        quietPlease();
        return invoke(canVisitAllSites, points, maxLength, result);
    }

    /* Confirms that the proposed trip route is valid. */
    void check(const Set<GPoint>& points,
               double timeLimit,
               const Vector<GPoint>& result) try {
        /* Track where we've been. */
        Set<GPoint> used;

        /* Total travel time. */
        double travelTime = 0.0;

        for (int i = 0; i < result.size(); i++) {
            /* Make sure this is one of the points. */
            if (!points.contains(result[i])) {
                ostringstream builder;
                builder << "Point is not a city: " << result[i] << endl;
                error(builder.str());
            }

            /* ... and not a duplicate. */
            if (used.contains(result[i])) {
                ostringstream builder;
                builder << "Duplicate city: " << result[i] << endl;
                error(builder.str());
            }

            used += result[i];

            /* Increase distance. */
            if (i != 0) {
                travelTime += distanceBetween(result[i - 1], result[i]);
            }
        }

        /* Can't exceed time limit. Add a little wiggle room to account for
         * floating-point inaccuracy.
         */
        if (travelTime > 1.000001 * timeLimit) {
            error("Trip too long.");
        }

        /* Need to visit everything. */
        if (used != points) {
            error("Not all points visited.");
        }

    } catch (const ErrorException& e) {
        ostringstream builder;
        builder << "Invalid route: " << e.what() << endl;
        builder << "         " << result << endl;
        SHOW_ERROR(builder.str());
    }
}

STUDENT_TEST("Walkthrough Video Example, without output") {
    const Set<GPoint> points = {
        { 0, 0 },
        { 0, 1 },
        { 1, 0 },
        { 0, 2 },
        { 1, 2 }
    };
    Vector<GPoint> unused;
    EXPECT( testCanVisit(points, 4, unused));
    EXPECT(!testCanVisit(points, 3, unused));
}

PROVIDED_TEST("Works for simple cases, without output.") {
    Vector<GPoint> unused;
    EXPECT(testCanVisit({ }, 137, unused)); // Can visit no points
    EXPECT(testCanVisit({ { 0, 0 } }, 1, unused)); // Can visit one point
    EXPECT(testCanVisit({ { 0, 0 } }, 0, unused)); // Can visit one point with no time

    EXPECT(!testCanVisit( { { 0, 0 }, { 1, 0 } }, 0.5, unused)); // Needs one time unit
    EXPECT( testCanVisit( { { 0, 0 }, { 1, 0 } }, 1,   unused)); // Needs one time unit
}

PROVIDED_TEST("Works for more elaborate cases, without output.") {
    /* Points around the border of a 2x2 square. */
    const Set<GPoint> points = {
        { 0, 0 },
        { 0, 1 },
        { 0, 2 },
        { 1, 2 },
        { 2, 2 },
        { 2, 1 },
        { 2, 0 },
        { 1, 0 }
    };

    Vector<GPoint> unused;
    EXPECT( testCanVisit(points, 7, unused));
    EXPECT(!testCanVisit(points, 6, unused));
}

PROVIDED_TEST("Works for simple cases, with output.") {
    Vector<GPoint> route;
    EXPECT(testCanVisit({ }, 137, route)); // Can visit no points
    check({ }, 137, route);
    EXPECT(testCanVisit({ { 0, 0 } }, 1, route)); // Can visit one point
    check({ { 0, 0 } }, 1, route);
    EXPECT(testCanVisit({ { 0, 0 } }, 0, route)); // Can visit one point with no time
    check({ { 0, 0 } }, 0, route);

    EXPECT(!testCanVisit( { { 0, 0 }, { 1, 0 } }, 0.5, route)); // Needs one time unit
    EXPECT( testCanVisit( { { 0, 0 }, { 1, 0 } }, 1,   route)); // Needs one time unit
    check( { { 0, 0 }, { 1, 0 } }, 1, route);
}

PROVIDED_TEST("Works for more elaborate cases, with output.") {
    /* Points around the border of a 2x2 square. */
    const Set<GPoint> points = {
        { 0, 0 },
        { 0, 1 },
        { 0, 2 },
        { 1, 2 },
        { 2, 2 },
        { 2, 1 },
        { 2, 0 },
        { 1, 0 }
    };

    Vector<GPoint> route;
    EXPECT( testCanVisit(points, 7, route));
    check(points, 8, route);
    EXPECT(!testCanVisit(points, 6, route));
}

PROVIDED_TEST("Handles error cases.") {
    Vector<GPoint> dummy;
    EXPECT_ERROR(testCanVisit({ {0, 1} }, -1, dummy));
}
