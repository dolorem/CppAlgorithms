#include "graph.h"

template<class Vertex, class Edge> bool Graph<Vertex, Edge>::BellmanFord(int v)
{
	FOREACH(it, g)
		it->distance = INF;
	g[v].distance = 0;
	g[v].ancestor = -1;
	int change, cnt = 0;
	do //Dopóki dokonana została poprawa, ale nie więcej niż SIZE(g) razy.
	{
		change = 0;
		REP(SIZE(g))
		{
			FOREACH(it, g[i])
			{
				if (g[i].distance + it->weight < g[it->destination].distance) //Relaksuje krawędzie.
				{
					g[it->destination].distance = g[i].distance + it->weight;
					g[it->destination].ancestor = i;
					change = 1;
				}
			}
		}
	}
	while (change && ++cnt < SIZE(g));
	return cnt == SIZE(g); //true jeśli istnieje cykl o ujemnej wadze.
}

struct VertexBellmanFord
{
	int distance, ancestor;
};

struct EdgeBellmanFord
{
	int weight;
};
