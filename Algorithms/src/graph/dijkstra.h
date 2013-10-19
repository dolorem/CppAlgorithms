/**
 * dijkstra.h
 * Implementation of Dijkstra's algorithm for finding single-source shortest paths in a weighed graph.
 * Edge weighs mustn't be negative.
 * During each iteration a previously unvisited vertex of minimal distance from source is chosen and all outgoing
 * edges are relaxed.
 * After completion, each vertex contains distance and ancestor in appropriate fields.
 *
 * complexity O(E log V + V log V)
 * Fibonacci Heaps may change complexity to O(E + V log V)
 *
 * @author Mateusz Śmiech
 * @version 0.0.0
 */

#include "graph.h"

template<class Vertex, class Edge> struct Graph<Vertex, Edge>::DijkstraComparator //Comparator for use in set.
{
	bool operator() (const VertexExtended *a, const VertexExtended *b) const
	{
		if (a->distance == b->distance)
			return a < b;
		return (a->distance) < (b->distance);
	}
};

template<class Vertex, class Edge> void Graph<Vertex, Edge>::Dijkstra(int s)
{
	set<VertexExtended*, DijkstraComparator> q; //Priority queue as set. It contains pointers to vertices (not their indices).
	FOREACH(it, g) //Initialize default values.
	{
		it->distance = INF;
		it->ancestor = -1;
	}
	g[s].distance = 0;
	q.insert(&g[s]);
	VertexExtended *v; //Pointer to the actually processed vertex.
	while (!q.empty())
	{
		v = *(q.begin()); //top() equivalent
		q.erase(q.begin()); //pop() equivalent
		FOREACH(it, *v) //Iterate outgoing edges.
		{
			if (g[it->destination].distance > v->distance + it->weight) //Relax edges.
			{
				//Unfortunately, we cannot edit value in the set. We have to remove vertex and add it again with updated distance.
				q.erase(&g[it->destination]);
				g[it->destination].distance = v->distance + it->weight;
				g[it->destination].ancestor = v - &g[0]; //Pointer subtraction (distance in vector (index)).
				q.insert(&g[it->destination]);
			}
		}
	}
}

struct VertexDijkstra
{
	int distance, ancestor;
};

struct EdgeDijkstra
{
	int weight, rev;
};
