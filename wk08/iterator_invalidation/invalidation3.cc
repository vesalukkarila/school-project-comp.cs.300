#include <iterator>
#include <vector>
#include <algorithm>
#include<iostream>

using namespace std;


/**
 * @brief duplicates even numbers in the vector, removes uneven numbers. Example: {1, 2, 3 4} -> {2, 2, 4, 4}
 *
 * @param vec vector to be handled
 */
void duplicateEvenRemoveUneven(std::vector<int>& vec) {

    using Iter = std::vector<int>::iterator;

    Iter begin = vec.begin();
    Iter end = vec.end();
    vector<int> apu;


     //ALKUPERÄINEN
    for ( Iter it = begin; it < end; it++){
        if ( *it % 2 == 0 ){
            vec.insert(it, *it);
            it++;

        }
        else {
            vec.erase(it);
            it--;
        }
    }

}

