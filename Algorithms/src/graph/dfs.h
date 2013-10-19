/**
 * dfs.h
 * Recursive implementation of the Depth-first search algorithm.
 * During any point, unvisited vertex's children are processed before its siblings.
 * complexity(V + E)
 *
 * @author Mateusz Śmiech
 * @version 0.0.0
 */

#include "graph.h"

template<class Vertex, class Edge> void Graph<Vertex, Edge>::DFS(int source = -1)
{
	FOREACH(it, g) //Set default pre- and post-visit times as well as ancestor.
					it->pre = it->post = it->ancestor = -1;
	int time = 0; //Time counter for pre- and post-visit times.
	if (source != -1)
		time = DFSVisit(source, time);
	REP(SIZE(g))
	{
		if (g[i].pre == -1) //Vertex hasn't been visited yet.
			time = DFSVisit(i, time); //Create new tree in the depth-first search forest.
	}
}

template<class Vertex, class Edge> int Graph<Vertex, Edge>::DFSVisit(int source, int time)
{
	g[source].pre = time++;
	FOREACH(it, g[source])
	{
		if (g[it->destination].pre == -1) //Vertex hasn't been visited yet.
		{
			g[it->destination].ancestor = source; //Set ancestor.
			time = DFSVisit(it->destination, time); //Recursively visit child, update time.
		}
	}
	g[source].post = time++;
	return time;
}

struct VertexDFS
{
	int ancestor, pre, post;
};

struct Empty
{

};
