#include <iostream>
#include "solver.h"

Cell& Cell::operator= (const Cell& c1) {
	i = c1.i;
	j = c1.j;
	FC = c1.FC;
	FA = c1.FA;
	xa = c1.xa;
	ya = c1.ya;

	/*cout << i << " "
		 << j << " "
		 << FC << " "
		 << FA << " "
		 << xa << " "
		 << ya << endl;*/

	return *this;
}

bool Cell::operator!= (const Cell& c1) {
	return ((this->i != c1.i) || (this->j != c1.j));
}

Comparison::Comparison () {}
bool Comparison::operator() (Cell &c1, Cell &c2) {
	return (c1.FC+c1.FA < c2.FC+c2.FA);
}

Solver::Solver () {}
Solver::~Solver () {}

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

		/*cout << "v.i: " << v.i << " | v.j: " << v.j << endl;
		cout << "end<0>: " << get<0>(end) << " | end<1>: " << get<1>(end) << endl;*/

		// If v is not the final state
		if (v.i != get<0>(end) || v.j != get<1>(end)) {
			// Getting v's adjacent cells
			adj = maze.getAdjacentCells (v.i, v.j, n, m);

			for (i = 0; i < (int) adj.size (); i++) {
				w = mm[get<0>(adj[i])][get<1>(adj[i])];

				if (!(w != mm[get<0>(start)][get<1>(start)]))
					continue;
				w.FC = v.FC + 1;
				w.xa = v.i;
				w.ya = v.j;
				mm[get<0>(adj[i])][get<1>(adj[i])] = w;
				Q.push (w);
			}
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) if (maze(i, j) == PATH) maze.set (i, j, WAY);
	}

	u = mm[get<0>(end)][get<1>(end)];
	v = mm[get<0>(start)][get<1>(start)];

	path.push_back (tuple<int, int> (u.i, u.j));
	maze.set(u.i, u.j, PATH);

	while (u != v) {
		path.push_back (tuple <int, int> (u.xa, u.ya));
		u = mm[u.xa][u.ya];
		maze.set(u.i, u.j, PATH);
	}

	for (int i = 0; i < n; i++) delete mm[i];
	delete mm;
}
