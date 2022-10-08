/**
 * iteration3.cc
 *
 * Print beginning half of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include <iostream>
#include <iterator> // for iterators
#include <list> // for lists
using namespace std;


void printHalf(const list<int>& lst)
{
  /**
  * Use iterators to go through the list and print elements
  */

    // ADD YOUR CODE HERE
      list<int>::const_iterator iteraattori= lst.begin();

      list<int>::const_iterator mIter = lst.begin();
      advance(mIter,distance(lst.begin(), lst.end()) / 2);

      for(; iteraattori != mIter; ++iteraattori){
          cout << *iteraattori << " ";
      }
      cout << endl;
                                 
                                 
                                
}
