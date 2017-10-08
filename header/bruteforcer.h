#ifndef _BRUTEFORCER_H_
#define _BRUTEFORCER_H_

#include "maze.h"

#include <deque>
#include <vector>

using namespace std;

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

    bool findDestination(Maze& m, int r, int c);

public:
    vector<BCell> getPath();
    bool bruteforce(Maze& maze);
};

#endif /* _BRUTEFORCER_H_ */