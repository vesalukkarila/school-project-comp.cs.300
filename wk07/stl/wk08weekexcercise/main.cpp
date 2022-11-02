#include <iostream>
#include <vector>

using namespace std;
/*In this exercise you are given a vector v that contains items of type struct Place{ int x; int y; string name; }. Your task is to customize available STL algorithms to perform the following.

Sort the elements of v according to the following criteria: first in ascending order of the x coordinate, then in ascending order of y coordinate, if two elements have equal x coordinates, and finally in dictionary order of the name, if both the x and y coordinates are equal.
Sort the elements of v according to the following criteria: first according to their distance from the origin {0,0} in ascending order and then in dictionary order of the name, if the distances from the origin are equal.
Create a new vector nearby1, that contains all elements whose distance from the origin is between 10 and 20.
Create a new vector nearby2, that contains all elements whose distance from the origin is between low and high, where low and high are parameters provided by the user.
Erase all items from vector nearby2, that contain string ”Unlisted” in their names or have an x coordinate or a y coordinate less than 1.
Bonus: How many comparisons are being done for the sorts in a and b?

*/
int main()
{



    struct Place{ int x; int y; string name; };
    vector<Place> v;

    auto sort_x = [](Place a, Place b){return a.x < b.x;} ;
    sort(v.begin(), v.end(), sort_x);



    return 0;
}
