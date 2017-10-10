#ifndef _BRUTEFORCER_H_
#define _BRUTEFORCER_H_

#include "maze.h"

#include <deque>
#include <vector>

using namespace std;

//class that applies the backtrack (not-informed search) to get to the solved maze

/*
* A cell in the Maze
*/
struct BCell {
public:
    BCell(int r, int c);
    BCell(const BCell& c);

    int row, column;

    BCell& operator= (const BCell& c);
};

class Bruteforcer {
private:
    deque<BCell> path;
    int cost;
    /*
    * Applying the backtrack in the Maze
    */
    bool findDestination(Maze& m, int r, int c);

public:
    vector<BCell> getPath();
    /*
    * Function used for external calls (in main e.g.) to apply backtrack to solve maze
    */
    bool bruteforce(Maze& maze);

    /*
    * Calculates the cost to find the solution
    */
    int getCost();
};

#endif /* _BRUTEFORCER_H_ */