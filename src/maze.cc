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
#ifndef NO_COLORS
			switch(maze[i][j]) {
				case WALL:
					cout << WALL_COLOR << WALL_PRINTCHAR;
					break;
				case PATH:
					cout << PATH_COLOR << PATH_PRINTCHAR;
					break;
				default:
					cout << DEFAULT_COLOR;
					cout << (char) maze[i][j];
					break;
			}
#else
			cout << (char) maze[i][j];
#endif
		}
#ifndef NO_COLORS
	cout << DEFAULT_COLOR;
#endif
		cout << endl;
	}

	cout << DEFAULT_COLOR;
}

int Maze::operator() (int i, int j) {
	return get(i,j);
}

int Maze::get(int r, int c) {
	return maze[r][c];
}

int Maze::getn () {
	return this->n;
}

int Maze::getm () {
	return this->m;
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

	if (!file.is_open()) {
		cout << "Não pode abrir o arquivo " << filename << endl;
		exit(EXIT_FAILURE);
	}

	int rows, cols, startrow, startcol, endrow, endcol;
	int val;

	file >> rows;
	file >> cols;
	file >> startrow;
	file >> startcol;
	file >> endrow;
	file >> endcol;

	Maze* maze = new Maze(rows, cols, make_tuple(startrow, startcol), make_tuple(endrow, endcol));

	while (file.get() != WALL) ;
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

vector< tuple<int, int> > Maze::getAdjacentCells (int i, int j, int n, int m) {
	vector< tuple<int, int> > v;

	if (i-1 >= 0 && maze[i-1][j] == WAY) {
		v.push_back (tuple <int, int> (i-1, j));
	}
	if (i+1 < n && maze[i+1][j] == WAY) {
		v.push_back (tuple <int, int> (i+1, j));
	}
	if (j-1 >= 0 && maze[i][j-1] == WAY) {
		v.push_back (tuple <int, int> (i, j-1));
	}
	if (j+1 < m && maze[i][j+1] == WAY) {
		v.push_back (tuple <int, int> (i, j+1));
	}

	return v;
}

void Maze::clear() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (maze[i][j] == PATH)
				maze[i][j] = WAY;
		}
	}
}