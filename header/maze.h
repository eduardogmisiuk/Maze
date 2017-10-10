#ifndef _MAZE_H_
#define _MAZE_H_

#include <string>
#include <tuple>
#include <vector>

using namespace std;

//Maze -> class that contains data from maze structure and auxiliar functions to solve

#define WALL (int)'*' // Every unvisited cell
#define WAY (int)' '  // Every non-wall cell
#define PATH (int)'.' // Every non-wall cell of the solution

//graphic interface macros
#define WALL_PRINTCHAR ' '
#define WALL_COLOR "\x1B[37;47m"
#define PATH_PRINTCHAR ' '
#define PATH_COLOR "\x1B[34;44m"
#define DEFAULT_COLOR "\x1B[37;40m"

class Maze {
private:
	int **maze;
	int n, m; // n rows, m columns

	/*
	 * Generates a random maze.
	 */
	void generate ();

	tuple<int, int> start; // Initial position
	tuple<int, int> end; // Destiny

public:
	//constructor + destructor
	Maze (int n, int m, tuple<int, int> start, tuple<int, int> end);
	~Maze ();

	/*
	 * Prints the maze.
	 */
	void print ();
	/*
	 * Operator overload to access the position (i,j) in the array int **maze.
	 */
	int operator() (int i, int j);

	// Getters
	/*
	 * Gets the cell at (r, c).
	 */
	int get(int r, int c);
	/*
	 * Size getters.
	 */
	int getn ();
	int getm ();
	/*
	 * Start/End getters.
	 */
	tuple<int, int> getStart();
	tuple<int, int> getEnd();

	// Setters
	void set(int r, int c, int v);

	void clear();

	/*
	 * Read the maze from the file.
	 */
	static Maze* fromFile(string filename);
	/*
	 * Returns a vector of adjacent cells.
	 */
	vector< tuple<int, int> > getAdjacentCells (int i, int j, int n, int m);
};

#endif
