#include "bruteforcer.h"

BCell::BCell(int r, int c) {
    row = r;
    column = c;
}

BCell::BCell(const BCell& c) {
    row = c.row;
    column = c.column;
}

BCell& BCell::operator=(const BCell& c) {
    row = c.row;
    column = c.column;

    return *this;
}

vector<BCell> Bruteforcer::getPath() {
    vector<BCell> v;

    for (auto it = path.begin(); it != path.end(); it++) {
        v.push_back(*it);
    }

    return v;
}

bool Bruteforcer::bruteforce(Maze& maze) {
    int startrow, startcol;
    tuple<int, int> start = maze.getStart();

    startrow = get<0>(start);
    startcol = get<1>(start);

    return findDestination(maze, startrow, startcol);
}

bool Bruteforcer::findDestination(Maze& m, int row, int col) {
    m.set(row, col, PATH);

    BCell currcell(row, col);
    path.push_back(currcell);
    
    tuple<int, int> end = m.getEnd();

    if (row == get<0>(end) && col == get<1>(end))
        return true;

    if (row > 1 && m.get(row - 1, col) == WAY) {
        if (findDestination(m, row - 1, col))
            return true;
    }

    if (col < m.getm() - 1 && m.get(row, col + 1) == WAY) {
        if (findDestination(m, row, col + 1))
            return true;
    }

    if (row < m.getn() - 1 && m.get(row + 1, col) == WAY) {
        if (findDestination(m, row + 1, col))
            return true;
    }

    if (col > 1 && m.get(row, col - 1) == WAY) {
        if (findDestination(m, row, col - 1))
            return true;
    }

    path.pop_back();

    m.set(row, col, WAY);

    return false;
}