#ifndef _SOLVER_H_
#define _SOLVER_H_

#include <queue>
#include <vector>
#include <tuple>
#include "maze.h"

using namespace std;

//class that applies the A* heuristic to search the result of the maze

//absolut value
#define ABS(x) (((x) > 0) ? (x) : -(x))
// Future's cost - based in manhattan's distance
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

/*
 * Auxiliary class to be used to compare cells in the priority queue.
 */
class Comparison {
public:
	Comparison ();
	bool operator() (Cell &c1, Cell &c2);
};

/*
 * Solver that uses A* search to find the path to the end of the maze.
 */
class Solver {
private:
	// Maze matrix
	Cell **mm;
	priority_queue<Cell, vector<Cell>, Comparison> Q;
	// The path from begin to end
	vector< tuple<int, int> > path;
	int cost;

public:
	Solver ();
	~Solver ();

	/*
	 * Implements A* search.
	 */
	void informedSearch (Maze &maze);

	int getCost();
};

#endif
