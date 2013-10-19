/**
 * acyclic.h
 * Functions checking if a graph is acyclic. For directed graphs it uses topological sort, for undirected - simple DFS.
 * complexity O(V + E)
 *
 * @author Mateusz Śmiech
 * @version 0.0.0
 */

#include "topologicalSortDfs.h"

template<class Vertex, class Edge>	bool Graph<Vertex, Edge>::isAcyclicDirected()
{
	topoSort();
	REP(SIZE(g)) //Iterate every edge.
	{
		FOREACH(it, g[i])
		{
			if (g[i].t >= g[it->destination].t) //Check if every edge connects vertex with lesser number with vertex with greater number.
				return false;
		}
	}
	return true;
}

template<class Vertex, class Edge> bool Graph<Vertex, Edge>::isAcyclicUndirected()
{
	acyclic = true;
	vis.resize(SIZE(g), 0);
	REP(SIZE(g))
	{
		if (!vis[i])
			acyclicDfs(i, 0);
	}
	return acyclic;
}

template<class Vertex, class Edge> void Graph<Vertex, Edge>::acyclicDfs(int v, Edge *e)
{
	if (!vis[v])
	{
		vis[v] = true;
		FOREACH(it, g[v])
		{
			if (&*it != e) //We don't want to go back the edge we have come from.
				acyclicDfs(it->destination, &g[it->destination][it->rev]);
		}
	}
	else
		acyclic = false;
}

struct EdgeUndirected
{
	int rev;
};
