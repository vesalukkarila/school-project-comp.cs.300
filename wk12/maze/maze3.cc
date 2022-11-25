#include <iterator>
#include <vector>
#include <algorithm>
#include "maze.hh"

using namespace std;

// Remember to implement your own container here or in another cc file to store the nodes in the maze
// If you define it elsewhere, remember to make sure it's accessible by this file as well.


/**
 * @brief Connect two adjacent nodes together. If the nodes are not adjacent, do nothing
 * 
 * @param fromNode  The node to connect from
 * @param toNode  The node to connect to
 */
void connectNodes(Node& node1, Node& node2) {

    // Student code here to connect the nodes together
    //sen mielestä ei ole connected, pitääkö hajottaa if ja lisätästructin above, below kohtiin ne linkitetyt, osaako se katsoa sitä kun nyt on to ja from
/*
    if ((node1.x == node2.x || node1.x == node2.x +1 || node1.x == node2.x -1)
            &&
            (node1.y == node2.y || node1.y == node2.y +1 || node1.y == node2.y -1) ){

        node1.to = &node2;
        node2.from = &node1;
    }
    */
    if (node1.x == node2.x && node1.y == node2.y -1){
        node1.above = &node2;
        node2.below = &node1;
    }

    if (node1.x == node2.x && node1.y == node2.y +1){
        node1.below = &node2;
        node2.above = &node1;
    }
    if (node1.x == node2.x-1 && node1.y == node2.y ){
        node1.right = &node2;
        node2.left = &node1;
    }
    if (node1.x == node2.x +1 && node1.y == node2.y ){
        node1.left = &node2;
        node2.right = &node1;
    }
}