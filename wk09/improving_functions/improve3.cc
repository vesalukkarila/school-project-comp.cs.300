#include <iterator>
#include <numeric>
#include <vector>
#include <map>
#include <algorithm>
#include<functional>
#include <iostream>
using namespace  std;

/**
 * @brief Sums up the values of the vector cumulatively, storing cumulative sum
 *        of the vector in a map, where the keys are the unique vector items,
 *        and the value is the last cumulative sum when that value was last
 *        encountered. (example: {4, 5, 4, 6} => {{4, 13}, {5, 9}, {6, 19}}).
 *
 * @param vec vector which is used for the sum operation.
 * @return std::map<int, int> sums - the sums of each cumulation stored in
 *         a map as values, vector values used as keys.
 */
std::map<int, int> cumulativeSums(std::vector<int> v) {

    std::map<int,int> sums; //ok

    vector<int>::iterator b = v.begin();

    vector<int>::iterator it = v.begin();
    while (it != v.end()) {

        sums[*it] = accumulate(b, it+1, 0);
        ++it;


    }
    for (auto n : sums)
        cout << n.first << " ja " << n.second << endl;


    return sums;
}
