#include <iostream>
#include "maze.h"
#include "solver.h"
#include "bruteforcer.h"

#include <cstdio>

int main (int argc, char *argv[]) {
	// executing in terminal:
	// main <maze file> <mode>
	// <mode> = 0 : A*; 1 : backtracking; 2 : both
	if (argc < 3) {
		cout << "uso:" << endl;
		cout << "./" << argv[0] << " <arquivo.in> <modo>" << endl;
		cout << "<modo> = 0, 1 ou 2, onde 0 = A*, 1 = backtracking, 2 = ambos." << endl;
		return 1;
	}

	//read and print of the input
	string filename = argv[1];
	Maze* maze = Maze::fromFile(filename);
	cout << "Labirinto original:" << endl;
	maze->print();
	cout << endl << endl;

	//setting search mode in maze
	int mode = std::atoi(argv[2]);
	//A* search
	if (mode == 0 || mode == 2) {
		Solver s;
		s.informedSearch(*maze);

		cout << "A*: (custo: " << s.getCost() << ")" << endl;

		maze->print();
		cout << endl;
	}
	//cleaning maze to be able to execute both searches
	if (mode == 2)
		maze->clear();
	//backtracking
	if (mode == 1 || mode == 2) {
		Bruteforcer b;
		b.bruteforce(*maze);

		cout << "Busca em largura (backtracking): (custo: " << b.getCost() << ")" << endl;

		maze->print();
		cout << endl;
	}

	delete maze;

	return 0;
}
