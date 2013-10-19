#include "topologicalSortDfs.h"

//Sprawdza, czy dany graf skierowany jest acykliczny.
template<class Vertex, class Edge>	bool Graph<Vertex, Edge>::isAcyclicDirected()
{
	topoSort(); //Najpierw sortuje go topologicznie.
	REP(SIZE(g))
	{
		FOREACH(it, g[i])
		{
			if (g[i].t >= g[it->destination].t) //Sprawdza czy wszystkie wierzchołki prowadzą do wierzchołków o mniejszym numerze.
				return false;
		}
	}
	return true;
}

//Sprawdza czy dany graf nieskierowany jest acykliczny.
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
	if (!vis[v]) //Wierzchołek nie był odwiedzony, jest ok.
	{
		vis[v] = true;
		FOREACH(it, g[v])
		{
			if (&*it != e) //Nie chcemy się cofnąć krawędzią z której przyszliśmy.
				acyclicDfs(it->destination, &g[it->destination][it->rev]);
		}
	}
	else //Wierzchołek był odwiedzony, znaleziono cykl.
		acyclic = false;
}

struct EdgeUndirected
{
	int rev;
};
