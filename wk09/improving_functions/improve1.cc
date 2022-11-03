#include <iterator>
#include <vector>
#include <algorithm>
#include<iostream>
using namespace std;
/**
 * @brief creates a vector of integers with ascending numbers from 0 - n-1
 *
 * @param n the size of the vector to be created
 * @return std::vector<int>
 */
std::vector<int> ascendingVector(int n){
    std::vector<int> v;
    int i = 0;
    // push_back() amortized constant O(n)
    while (  i!= n) {     //O(n), muutettu != koska vertailee vain onko sama vai ei
        v.push_back(i);             // a.constant
        ++i;
    }

    return v;
}
