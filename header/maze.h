#ifndef _MAZE_H_
#define _MAZE_H_

using namespace std;

#define WALL '*'
#define WAY ' '  // Every non-wall cell
#define PATH '.' // Every non-wall cell of the solution

class Maze {
private:
	int **maze;
	int n, m; // n rows, m columns

	/*
	 * Generates a random maze.
	 */
	void generate ();

public:
	Maze (int n, int m);
	~Maze ();

	/*
	 * Prints the maze.
	 */
	void print ();
	/*
	 * Operator overload to access the position (i,j) in the array.
	 */
	int operator() (int i, int j);

};

#endif
