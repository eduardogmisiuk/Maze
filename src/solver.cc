#include <iostream>
#include "solver.h"

Comparison::Comparison () {}
Solver::Solver () {}
Solver::~Solver () {}

Cell& Cell::operator= (const Cell& c1) {
	i = c1.i;
	j = c1.j;
	FC = c1.FC;
	FA = c1.FA;
	xa = c1.xa;
	ya = c1.ya;

	return *this;
}

/*
 * Overrides != of Cell.
 */
bool Cell::operator!= (const Cell& c1) {
	return ((this->i != c1.i) || (this->j != c1.j));
}

/*
 * Overrides () of Cell.
 */
bool Comparison::operator() (Cell &c1, Cell &c2) {
	return (c1.FC+c1.FA < c2.FC+c2.FA);
}

/*
 * A* search of the path of the maze.
 */
void Solver::informedSearch (Maze &maze) {
	int n, m, i, j;
	Cell u, v, w; // Auxiliary cells
	// Vector of adjacent cells
	vector< tuple<int, int> > adj;

	tuple<int, int> start = maze.getStart ();
	tuple<int, int> end = maze.getEnd ();
	n = maze.getn ();
	m = maze.getm ();

	mm = new Cell*[n];
	for (i = 0; i < n; i++) mm[i] = new Cell[m];

	// Initializing the cells
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			mm[i][j].i = i;
			mm[i][j].j = j;
			mm[i][j].FC = 0;
			mm[i][j].FA = MANHATTAN(i,j,get<0>(end),get<1>(end));
			mm[i][j].xa = mm[i][j].ya = -1;
		}
	}

	u = mm[get<0>(start)][get<1>(start)];

	// Pushing the first cell to the queue
	Q.push (u);

	while (!Q.empty ()) {
		v = Q.top ();
		Q.pop ();
		maze.set(v.i, v.j, PATH);

		// If v is not the final state
		if (v.i != get<0>(end) || v.j != get<1>(end)) {
			// Getting v's adjacent cells
			adj = maze.getAdjacentCells (v.i, v.j, n, m);

			for (i = 0; i < (int) adj.size (); i++) {
				w = mm[get<0>(adj[i])][get<1>(adj[i])];

				// If w is the initial node, we don't come back
				// to it, only continue the loop
				if (!(w != mm[get<0>(start)][get<1>(start)]))
					continue;
				// Updating w values
				w.FC = v.FC + 1;
				w.xa = v.i;
				w.ya = v.j;
				// If we don't copy the values we put at w to mm[][],
				// the cell will be outdated
				mm[get<0>(adj[i])][get<1>(adj[i])] = w;
				// Push to the queue
				Q.push (w);
			}
		}
	}

	// Removing the PATH marcation
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) if (maze(i, j) == PATH) maze.set (i, j, WAY);
	}

	u = mm[get<0>(end)][get<1>(end)];
	v = mm[get<0>(start)][get<1>(start)];

	path.push_back (tuple<int, int> (u.i, u.j));
	maze.set(u.i, u.j, PATH);

	// Marking the path from the start to the end
	while (u != v) {
		path.push_back (tuple <int, int> (u.xa, u.ya));
		u = mm[u.xa][u.ya];
		maze.set(u.i, u.j, PATH);
	}

	for (int i = 0; i < n; i++) delete mm[i];
	delete mm;
}
