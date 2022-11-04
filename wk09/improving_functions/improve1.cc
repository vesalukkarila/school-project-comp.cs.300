#include <iterator>
#include <vector>
#include <algorithm>
#include<iostream>
#include<numeric>
using namespace std;
/**
 * @brief creates a vector of integers with ascending numbers from 0 - n-1
 *
 * @param n the size of the vector to be created
 * @return std::vector<int>
 */

//Tiiä mitä vittua täsä pitäs vielä hinkata
std::vector<int> ascendingVector(int n){
    std::vector<int> v(n-1);
    iota(v.begin(), v.end(), 0);



    return v;
}
