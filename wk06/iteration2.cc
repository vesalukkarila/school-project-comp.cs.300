/**
 * iteration2.cc
 *
 * Print every second item of a list starting from the first item
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include <iostream>
#include <iterator> // for iterators
#include <list> // for lists
using namespace std;


void printEverySecond(const list<int>& lst)
{
  /**
  * Use iterators to go through the list and print elements
  */

  // ADD YOUR CODE HERE
    
    list<int>::const_iterator iteraattori = lst.begin();
    for(;iteraattori != lst.end(); advance(iteraattori, 2)){
        cout << *iteraattori << " ";

        if (iteraattori == --lst.end()  )
            return;
            
    }
}
