#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


/**
 * @brief Erases every second item from the vector. Example: {1, 2, 3, 4} -> {1, 3}
 *
 * @param vec vector where every second item is erased.
 *
 *
 * ------------TÖNKKÖ vaikka toimiva TOTEUTUS apuvektorilla SAA VARMAAN ALGORITMILLA REMOVE JA ERASE SUORAAN
 * -------------KATO MITEN TÄÄ TEHTÄVÄ ON MUUT TEHNYT---------------
 */
void eraseEverySecond(std::vector<int>& vec) {
    auto beg = vec.begin();
    auto end = vec.end();
    auto beg2 = vec.begin();
    beg++;  //starts at 1
    beg2 += 2;  //starts at 2
    vector<int> apu;

    for ( unsigned long int i = 0; i < vec.size(); i++){
        if (i % 2==1)
            apu.push_back(vec[i]);
    }
    for (auto val : apu){
        vector<int>::iterator it = find(beg, end, val);

        if ( it != end)
            vec.erase(it);
    }


    /*for (auto i = beg; i != end; i = i+2)
    { vec.erase(i); }
*/

}

