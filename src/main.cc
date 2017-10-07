#include <iostream>
#include "maze.h"

int main (int argc, char *argv[]) {
	int n, m;

	cout << "Size: ";
	cin >> n >> m;

	Maze maze (n, m);

	maze.print ();

	return 0;
}
