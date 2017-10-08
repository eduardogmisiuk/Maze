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
			cout << (char) maze[i][j];
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
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			maze[i][j] = WALL;
		}
	}
}

Maze* Maze::fromFile(string filename) {
	ifstream file(filename, ifstream::in);
	int rows, cols, startx, starty, endx, endy;
	int val;

	file >> rows;
	file >> cols;
	file >> startx;
	file >> starty;
	file >> endx;
	file >> endy;

	Maze* maze = new Maze(rows, cols, make_tuple(startx, starty), make_tuple(endx, endy));

	while (file.get() != (int)'*') ;
	file.unget();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			val = file.get();
			if (val != WALL && val != WAY) {
				cout << "erro ao ler o arquivo de labirinto. '" << (char)val << "'" << endl;
				exit(EXIT_FAILURE);
			}
			maze->set(i, j, val);
		}
		do {
			val = file.get();
		} while (val == '\n' || val == '\r');
		file.unget();
	}

	return maze;
}

tuple<int, int> Maze::getStart() {
	return start;
}

tuple<int, int> Maze::getEnd() {
	return end;
}