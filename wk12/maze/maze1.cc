#include <iterator>
#include <vector>
#include <algorithm>
#include <set>
#include "maze.hh"

using namespace std;

// Remember to implement your own container here or in another cc file to store the nodes in the maze
// If you define it elsewhere, remember to make sure it's accessible by this file as well.


/**
 * @brief Create a Node object
 * 
 * @param loc  The location of the node
 * @return Node*  A pointer to the node that is created. If the node already exists, return a pointer to the existing node
 */
Node* createNode  (std::pair<int, int> loc, std::map<std::string, Node*> paths) {
    //If attempting to create a node that already exists, you must simply return the existing node.
    for (auto alkio : vektori){
        if ( alkio->x == loc.first && alkio->y == loc.second)
            return alkio;
    }

    Node* t = new Node;
    t->x = loc.first;
    t->y = loc.second;
    if(paths.count(ABOVE) == 1)
        t->above = paths.at(ABOVE);
    else
        t->above = nullptr;

    if(paths.count(BELOW) == 1)
        t->below = paths.at(BELOW);
    else
        t->below = nullptr;

    if(paths.count(RIGHT) == 1)
        t->right = paths.at(RIGHT);
    else
        t->right = nullptr;

    if(paths.count(LEFT) == 1)
        t->left = paths.at(LEFT);
    else
        t->left = nullptr;

    t->from = nullptr;
    t->to = nullptr;

  //  Node* t = &uusi;            //tän o is ehkä voinu tehdä suoraan Node* paikallisosoitin = new Node{loc.first, loc.second, jne}
    vektori.push_back(t);


    return t;
}
