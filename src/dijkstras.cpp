// Colin Sprague
// October 27, 2026
// Dijkstra's Algorithm
//
// This program takes data from standard input,
// sparses it, and prints output to stdout.
//
// Input:
// TILES_N
// TILE_NAME_0 TILE_COST_0
// ...
// TILE_NAME_N-1 TILE_COST_N-1
//
// MAP_ROWS MAP_COLS
// TILE_0_0 ...
// ...
//
// RUNNER_START_ROW RUNNER_START_COL
// RUNNER_END_ROW   RUNNER_END_COL
// ----------------------------------
// Where:
//	TILES_N is the number of unique tiles
//	TILE_NAME_N is the symbol of a tile
//	TILE_COST_N is the cost to leave that tile
//	MAP_ROWS and MAP_COLS are the maps dimensions
//	TILE_N_N is the symbol of that position on the map
//	RUNNER_START... is the starting posiiton of the runner
//	RUNNER_END... is the ending position of the runner
//
// Output:
// WEIGHT
// R_0 C_0 
// ...
// R_N-1 C_N-1
// ---------------
// Where:
//	WEIGHT is minimum weight to traverse from source to destination
//	R_0 C_0 represent the traversal of the player through the graph

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <deque>
#include <utility>
#include <tuple>

using namespace std;

typedef tuple<int, int, int> Node; // {distance, row, col}

// Helper Function
void update(Node cur, pair<int, int> np, int weight, 
		vector< vector<int>>& dist,
		vector< vector< pair<int,int> > >& parent,
		priority_queue<Node, vector<Node>, greater<Node>>& pq) {

	int new_dist = get<0>(cur) + weight;

	if (new_dist < dist.at(np.first).at(np.second)) {
		dist.at(np.first).at(np.second) = new_dist;
		parent.at(np.first).at(np.second) = {get<1>(cur), get<2>(cur)};
		pq.push({new_dist, np.first, np.second});
	}
}

// Main Execution

int main(int argc, char *argv[]) {

	// -- Data Collection: Start -- //
	int n_type;
	int n_rows;
	int n_cols;

	char symbol;
	int  weight;

	pair<int, int> src;
	pair<int, int> dst;

	unordered_map<char, int> types;
	vector< vector<char> >  map;

	cin >> n_type;

	for (int i = 0; i < n_type; i++) {
		cin >> symbol >> weight;
		types.insert({symbol, weight});
	}

	cin >> n_rows >> n_cols;
	map.resize(n_rows);
	for (int r = 0; r < n_rows; r++) {
		for (int c = 0; c < n_cols; c++) {
			cin >> symbol;
			map.at(r).push_back(symbol);
		}
	}

	cin >> src.first >> src.second;
	cin >> dst.first >> dst.second;
	// -- Data Collection: End -- //


	// -- Dijkstra's Setup -- //
	priority_queue<Node, vector<Node>, greater<Node>> pq;	
	Node start;

	vector< vector <int > >    dist(n_rows, vector<int >(n_cols, 1e9  ));
	vector< vector < pair<int, int> > > parent(n_rows, vector<pair<int,int>>(n_cols, {-1, -1}));

	dist.at(src.first).at(src.second) = 0;

	start = {0, src.first, src.second};
	pq.push(start);

	while (!pq.empty()) {

		Node cur = pq.top();
		pq.pop();

		int r = get<1>(cur);
		int c = get<2>(cur);
		int w = types.at(map.at(r).at(c));


		// If end is reached, print results and break
		if (get<1>(cur) == dst.first && get<2>(cur) == dst.second) {
			cout << get<0>(cur) << endl;

			deque<pair<int,int>> path;
			path.push_front({dst.first, dst.second});
			while (parent.at(r).at(c).first != -1) {

				path.push_front(parent.at(r).at(c));

				pair<int,int> next_pos = parent.at(r).at(c);
				r = next_pos.first;
				c = next_pos.second;
			}

			for (size_t i = 0; i < path.size(); i++) {
				cout << path.at(i).first << " ";
				cout << path.at(i).second << endl;
			}

			break;
		}

		// Safely access and push adjacent nodes to queue
		if (r != 0) {
			update(cur, {r - 1, c}, w, dist, parent, pq); 
		}
		if (r != n_rows - 1) {
			update(cur, {r + 1, c}, w, dist, parent, pq); 
		}
		if (c != 0) {
			update(cur, {r, c - 1}, w, dist, parent, pq); 
		}
		if (c != n_cols - 1) {
			update(cur, {r, c + 1}, w, dist, parent, pq); 
		}
	}
	// -- Dijkstra's End -- //


	return 0;
}

