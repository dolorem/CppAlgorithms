/**
 * kosajaru.h
 * Kosajaru's algorithm for finding a graph of strongly connected components of another graph.
 * Algorithm uses Depth-first search twice. First time it is done on the original graph and vertices are added
 * to vector<int> visited in order of their post-process times. Then the graph is transposed and searched in
 * order of decreasing post-process times. Each root in depth-first search forest starts new strongly connected
 * component and if an edge between component with greater and lower number is found, it is added to the scc graph.
 * After completion each vertex has number of its SCC in the t field.
 * complexity O(V + E)
 *
 * @author Śmiech Mateusz
 * @version 0.0.0
 */

#include "graph.h"

template<class Vertex, class Edge> void Graph<Vertex, Edge>::sccDfs(int v, int nr, bool firstPhase)
{
	g[v].t = 1; //Mark it as visited.
	if (!firstPhase)
		visited[v] = nr; //SCC number.
	FOREACH(it, g[v]) //Iterate edges going out of v.
	{
		if (g[it->destination].t == -1) //Vertex hasn't been visited yet.
			sccDfs(it->destination, nr, firstPhase);
		else if (!firstPhase && nr > visited[it->destination]) //Vertex has been visited. If it connects component of higher number with one with lower number, an edge is added.
			sccRes->addDirectedEdge(g[it->destination].t, visited[it->destination] = nr);
	}
	if (firstPhase)
		visited.PB(v); //Vertex's processing has been finished, we can append it to the vector (it serves as a stack).
	else
		g[v].t = nr; //Second phase - update vertex's SCC number.
}

template<class Vertex, class Edge> Graph<Vertex, Edge> Graph<Vertex, Edge>::scc()
{
	//gt - transpose graph
	//*tab[] points to the graph which has to be processed (either original or transpose)
	//res - SCC graph
	Graph<Vertex, Edge> gt(SIZE(g)), res(SIZE(g)), *tab[] = {this, &gt};
	visited.clear();
	gt.visited.resize(SIZE(g), -1);
	gt.sccRes = &res;
	REP(SIZE(g)) //Creates transpose graph.
	{
		FOREACH(it, g[i])
						gt.addDirectedEdge(it->destination, i);
	}
	REP(2)
	{
		FOREACH(it, tab[i]->g)
						it->t = -1; //Indicates if vertex has been visited. After second iteraton it contains number of SCC the vertex belongs to.
		int counter = 0, v; //Counter is the number of SCCs, v - actually processed vertex.
		for (int j = SIZE(g) - 1; j >= 0; j--) //Decreasing order is important during second iteration.
		{
			if (tab[i]->g[v = i ? visited[j] : j].t == -1) //During first iteration we're visiting vertex j, during second - vertex which has been processed as j.
				tab[i]->sccDfs(v, counter++, 1 - i);
		}
		if (i)
			res.g.resize(counter);
	}
	REP(SIZE(g))
		g[i].t = gt.g[i].t; //Sets SCC numbers basing on the transpose graph.
	return res;
}

struct VertexScc
{
	int t;
};

struct Empty
{

};
