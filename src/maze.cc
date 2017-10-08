#include "maze.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using std::string;

Maze::Maze (int n, int m, tuple<int, int> start, tuple<int, int> end) {
	this->n = n;
	this->m = m;
	maze = new int *[n];
	for (int i = 0; i < n; i++) maze[i] = new int[m];

	this->start = start;
	this->end = end;

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
	return get(i,j);
}

int Maze::get(int r, int c) {
	return maze[r][c];
}

void Maze::set(int r, int c, int v) {
	maze[r][c] = v;
}

void Maze::generate () {
}

tuple<int, int> Maze::getStart() {
	return start;
}

tuple<int, int> Maze::getEnd() {
	return end;
}