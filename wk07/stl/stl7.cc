#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh" // NOT_FOUND constant

using namespace std;


/**
 * @brief Find the median value of a given vector, whose elements are in random
 *        order. Return NOT_FOUND if the size of the vector is zero.
 *
 * @param v a random vector
 * @return int
 */
int findMedian(std::vector<int>& v)
{
    if (v.size() == 0)
        return NOT_FOUND;

    sort(v.begin(), v.end());
    if (v.size()%2 != 0){
        return v.at(v.size()/2);
    }

    int parillinen = (v.at(v.size()/2) + v.at(v.size()/2 -1) )/2;
    return parillinen;
}
