// Colin Sprague
// 10/27/2026
// generate_map
//
// This program takes a positive integer as a command line argument, n.
// It prints valid standard input for the dijkstra executable.
// Run: ./exec n

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
	
	// Take input
	if (argc != 2 || stoi(argv[1]) <= 0) {
		cerr << "Usage: ./generate_map <N>\n";
		return 1;
	}

	int n = stoi(argv[1]);
	srand(time(nullptr));

	// Initialize Symbols
	vector< pair<char, int> > symbol = {
		{'f', 3},
		{'g', 1},
		{'G', 2},
		{'h', 4},
		{'m', 7},
		{'r', 5}
	};

	// Print number of unique tiles  
	cout << symbol.size() << endl;

	// Print each unique tile
	for (size_t i = 0; i < symbol.size(); i++) {
		cout << symbol.at(i).first << " ";
		cout << symbol.at(i).second << endl;
	}
	
	// Print map dimensions
	cout << n << " " << n << endl;

	// Print map
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			int rand_idx = rand() % symbol.size();
			cout << symbol.at(rand_idx).first;
			if (c < n - 1) cout << " ";
		}
		cout << endl;
	}

	// Print start and end position
	cout << "0 0" << endl;
	cout << (n - 1) << " " << (n - 1) << endl;

	return 0;
}
