#include <iostream>
#include "maze.h"
#include "solver.h"

int main (int argc, char *argv[]) {
	Maze *maze = Maze::fromFile("in/1.in");
	Solver s;
	s.informedSearch (*maze);
	maze->print ();
	delete maze;
	return 0;
}
