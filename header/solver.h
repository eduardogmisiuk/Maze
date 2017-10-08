#ifndef _SOLVER_H_
#define _SOLVER_H_

#include <queue>
#include <vector>
#include <tuple>
#include "maze.h"

using namespace std;

#define ABS(x) (((x) > 0) ? (x) : -(x))
// Future's cost
#define MANHATTAN(xi,yi,xf,yf) (ABS(xf-xi) + ABS(yf-yi))

/*
 * A cell in the maze
 */
typedef struct Cell {
public:
	int i, j; 	// Position in the matrix
	int FC, FA; // Past and Future functions
	int xa, ya; // Previous cell

	Cell& operator= (const Cell& c1);
	bool operator!= (const Cell& c1);
} Cell;

class Comparison {
public:
	Comparison ();
	bool operator() (Cell &c1, Cell &c2);
};

class Solver {
private:
	// Maze matrix
	Cell **mm;
	priority_queue<Cell, vector<Cell>, Comparison> Q;
	// The path from begin to end
	vector< tuple<int, int> > path;

public:
	Solver ();
	~Solver ();

	/*
	 * Implements A* search.
	 */
	void informedSearch (Maze &maze);

	
};

#endif
