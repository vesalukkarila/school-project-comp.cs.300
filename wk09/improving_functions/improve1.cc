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

    for ( int i = 0; i<n; ++i)
        v.push_back(i);


    /* O(n2)
    for ( int i = 0; i < n ; i++){  //O(n)
        v.insert(v.end(), i);       // O(n)
    }
    */
    for (auto n : v)
        cout << n << endl;
    return v;
}
