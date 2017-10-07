#include "maze.h"
#include <iostream>

Maze::Maze (int n, int m) {
	this->n = n;
	this->m = m;
	maze = new int *[n];
	for (int i = 0; i < n; i++) maze[i] = new int[m];

	generate ();
}
Maze::~Maze () {
	for (int i = 0; i < n; i++) delete maze[i];
	delete maze;

	n = m = 0;
}

void Maze::print () {
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			cout << (char) maze[i][j] << " ";
		}
		cout << endl;
	}
}
int Maze::operator() (int i, int j) {
	return maze[i][j];
}

void Maze::generate () {
}
