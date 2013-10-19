#include "graph.h"

//Sortowanie topologiczne, zwraca wektor zawierający wierzchołki w posortowanej kolejności.
template<class Vertex, class Edge>	VI Graph<Vertex, Edge>::topoSortV()
{
	VI sorted(SIZE(g));
	topoSort();
	REP(SIZE(g))
	sorted[g[i].t] = i;
	return sorted;
}

//Sortuje topologicznie, kolejność będzie zawarta w polu t.
template<class Vertex, class Edge> void Graph<Vertex, Edge>::topoSort()
{
	int index = SIZE(g) - 1;
	FOREACH(it, g)
	it->t = 0;
	for (int i = SIZE(g) - 1; i >= 0; i--)
		index = topoDfs(i, index);
}

//DFS do sortowania topologicznego.
template<class Vertex, class Edge> int Graph<Vertex, Edge>::topoDfs(int v, int index)
{
	if (!g[v].t)
	{
		g[v].t = 1;
		FOREACH(it, g[v])
		index = topoDfs(it->destination, index);
		g[v].t = index--;
	}
	return index;
}

struct VertexScc
{
	int t;
};

struct Empty
{

};
