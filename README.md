Project 04: Path Finding
========================

This project implements a [Dijkstra's Algorithm] to perform rudimentary path
finding on a 2D tile-based map.

[Dijkstra's Algorithm]: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm


Input
-----

    TILES_N
    TILE_NAME_0	TILE_COST_0
    ...
    TILE_NAME_N-1	TILE_COST_N-1

    MAP_ROWS MAP_COLUMNS
    TILE_0_0    ...
    ...

    TRAVELER_START_ROW TRAVELER_START_COL
    TRAVELER_END_ROW   TRAVELER_END_COL

Output
------

    Cost
    [(ROW_0, COL_0), ...]

Usage
-----
Run make
Use generate_map executable (./generate_map <N>) to produce standard input of a random N x N map for the dijkstras program.
Example: ./generate_map 100 | ./dijkstras
Additional information on source .cpp files.

Results
-------
| N             | Median Elapsed Time (seconds) | Median Memory (KB)|   
----------------|-------------------------------|-------------------|      
| 10            | 0.00                          | 3360              |           
| 20            | 0.00                          | 3360              |           
| 50            | 0.01                          | 3360              |           
| 100           | 0.02                          | 3360              |           
| 200           | 0.05                          | 3808              |           
| 500           | 0.32                          | 6496              |           
| 1000          | 1.32                          | 15904             |    

Summary
----------
Representation:
The map was represented as a 2D matrix. Each vertex represents a tile at a specific (r, c) position. Neighboring vertices are determined by accessing adjacent elements in the matrix. No adjacency matrix or list was used; edges were created and derived as needed. 
Data Structures: 
A priority_queue of Nodes (priority_queue<Node, vector<Node>, greater<Node>>), where Node = {distance, row, col}, was chosen to act as a min-heap. It allows the algorithm to greedily extract unvisited nodes with the lowest accumulated travel cost in O(logV) time.
A 2D vector (vector<vector<int>>) was used to track the minimum known distance from the source to every grid coordinate, initialized to a large infinity value (1e9).
A 2D vector (vector<vector<pair<int,int>>>) was used to track predecessor coordinates for every cell, which enables efficient backward path reconstruction once the destination is reached.
A deque (deque<pair<int,int>>) was used during path reconstruction with push_front so that the final path coordinates can be easily gathered in the correct order (from src to dst) without requiring manual reverse pass.
Time Complexity:
In terms of vertices (V) and edges (E), the time complexity is O((V+E)logV) because we use a binary min-heap. Each vertex is extracted from the priority queue once (O(VlogV)), and each edge/neighbor is examined and potentially updated once (O(ElogV)).
In terms of grid dimension (N), the number of vertices is V=N^2, and the maximum number of edges is E<=4N^2 (up to 4 orthogonal neighbors per cell). Substituting this yields O(N^2*logN).
Space Complexity: 
Space complexity is O(V) or O(N^2).
    The 2D map stores N^2 elements
    The distance table stores N^2 integers
    The parent tracking table stores N^2 pairs
    The priority queue can hold up to O(V) entries
Time Scalability:
From N=100 to N=500 (5x increase in dimension, 25x increase in grid cells), time jumps from 0.02s to 0.32s (~16x increase)
From N=500 to N=1000 (2x increase in dimension, 4x increase in grid cells), time jumps from 0.32s to 1.32s (~4.1x increase)
Time growth perfectly mirrors the theoretical O(N^2logN) bound. As N doubles, N^2 quadruples, and the log factor adds a small extra multiplier
Memory Scalability:
At N = 100 (10,000 cells), memory overhead beyond baseline is negligible
At N = 500 (250,000 cells), peak memory rises to 6.5 MB
At N = 1000 (1,000,000 cells), peak memory rises to 15.9 MB
Subtracting the 3.3 MB base program overhead, N=500 reaches about 3.1 MB, while N=1000 reaches about 12.5 MB. This is a 4x increase in active memory usage when moving from N=500 to N=1000 which aligns with the expected O(N^2) space complexity.
