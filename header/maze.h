#ifndef _MAZE_H_
#define _MAZE_H_

#include <string>
#include <tuple>
#include <vector>

using namespace std;

#define WALL (int)'*'
#define WAY (int)' '  // Every non-wall cell
#define PATH (int)'.' // Every non-wall cell of the solution

class Maze {
private:
	int **maze;
	int n, m; // n rows, m columns

	/*
	 * Generates a random maze.
	 */
	void generate ();

	tuple<int, int> start;
	tuple<int, int> end;

public:
	Maze (int n, int m, tuple<int, int> start, tuple<int, int> end);
	~Maze ();

	/*
	 * Prints the maze.
	 */
	void print ();
	/*
	 * Operator overload to access the position (i,j) in the array.
	 */
	int operator() (int i, int j);

	int get(int r, int c);
	int getn ();
	int getm ();
	void set(int r, int c, int v);

	tuple<int, int> getStart();
	tuple<int, int> getEnd();

	static Maze* fromFile(string filename);
	vector< tuple<int, int> > getAdjacentCells (int i, int j, int n, int m);
};

#endif
