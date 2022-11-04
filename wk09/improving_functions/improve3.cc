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

    for (unsigned int i=0; i<v.size(); ++i) {   //tehokkaampaa tapaa loopata? vertailu ulkopuolella, !=, while ehkä, koska nyt i:n arvo jatkuvassa käytössä
        //while (v.begin() != v.end() ?
        if (sums.empty())       //jos map tyhjä..
        { sums[v[i]] = v[i]; }  //luodaan avain-arvopari, tehokkaampi tapa luoda pari? päästä käsiksi avaimeen/arvoon

        else
        { sums[v[i]] = sums.at(v[i-1]) + v[i]; }    //tehokkaampaa tapaa päästä käsiksi avaimeen, summaus vektori

    }

    return sums;
}

