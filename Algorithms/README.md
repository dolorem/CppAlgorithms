CppAlgorithms
=============

Set of algorithms and data structures which may be useful in programming contests, written in C++.

## Conventions ##

1.	Each problem class (graph, number theory, sort etc.) is placed in separate folder.
2.	Each algorithm is placed in separate header file.
3.	Each algorithm has _exactly_ one test case, usually loaded from a separate file placed in /tests folder.
4.	Each non-testing function has possibly most comprehensible variable names, if it's impossible, their usage is commented.

## Algorithms implemented ##
1. Graph
	1. Breadth-First Search
	2. Depth-First Search
	3. Euler Path
	4. Topological Sort using DFS
	5. Acyclic Test (uses Topological Sort)
	6. Kosajaru Algorithm for finding Strongly Connected Components
	7. Prim Algorithm for finding Minimal Spanning Tree
	8. Dijkstra Algorithm for finding shortest paths from one source in non-negatively weighed graphs.
	9. Bellman-Ford Algorithm for finding stortest paths from one source in weighed graphs.

	
## Data structures implemented ##
1. Graph (undirected is represented as directed with double edges - (a, b) and (b, a)

## TODO ##
Way too much to write in here...

