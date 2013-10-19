/**
 * bellmanFord.h
 * Implements Bellman-Ford algorithm for finding shortest paths from a given source in a weighed graph.
 * Edge weighs can be negative.
 * During each iteration every edge is checked. If it can reduce path cost for a vertex, it is reduced.
 * If algorithm keeps correcting distances for some vertices after V - 1 iterations, a cycle of negative weight
 * exists and function returns true.
 * Each vertex's distance from source is kept in field distance, it's predecessor on shortest path to the
 * source is in field ancestor.
 * complexity O(VE)
 *
 * @author Mateusz Śmiech
 * @version 0.0.0
 */

#include "graph.h"

template<class Vertex, class Edge> bool Graph<Vertex, Edge>::BellmanFord(int v)
{
	FOREACH(it, g) //We'll be checking if actual distance > distance after relaxation, thus it has to be big.
		it->distance = INF;
	g[v].distance = 0;
	g[v].ancestor = -1;
	bool changed; //Changed indicates that at least one vertex's distance has been bettered.
	int counter = 0;
	do //While something has changed, but not more than SIZE(g) times.
	{
		changed = false;
		REP(SIZE(g))
		{
			FOREACH(it, g[i]) //Iterate every edge.
			{
				if (g[i].distance + it->weight < g[it->destination].distance) //Relaxes edge.
				{
					g[it->destination].distance = g[i].distance + it->weight; //Update distance.
					g[it->destination].ancestor = i; //Update ancestor.
					changed = true;
				}
			}
		}
	}
	while (changed && ++counter < SIZE(g));
	return counter == SIZE(g); //True if there is a cycle of negative weight.
}

struct VertexBellmanFord
{
	int distance, ancestor;
};

struct EdgeBellmanFord
{
	int weight;
};
