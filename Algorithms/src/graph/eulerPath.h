/**
 * eulerPath.h
 * Finds Eulerian path in a graph.
 *
 * @author Śmiech Mateusz
 * @version 0.0.0
 */

#include "graph.h"

template<class Vertex, class Edge> bool Graph<Vertex, Edge>::EulerDirected(VI &path)
{
	path.clear(); //Reset path vector.
	int edges = 1, v = -1, h;
	stack<int> s;
	VI degree(SIZE(g), 0); //Contains vertices out degree.
	REP(SIZE(g))
	{
		FOREACH(it, g[i])
						degree[it->destination]++; //Increase out degree by 1.
	}
	REP(SIZE(g)) //Designates start vertex.
	{
		if ((h = degree[i]) > SIZE(g[i])) //In-degree > out-degree => new start candidate.
			v = i;
		else if (v == -1 && h) //Vertex isn't isolated and no candidate is set.
			v = i;
		edges += h; //Update number of edges in the graph.
	}
	if (v != -1) //There is a start vertex.
		s.push(v);
	while (!s.empty()) //While stack isn't empty, do DFS.
	{
		if (!degree[v = s.top()]) //All edges have been processed, return adding edges to eulerian path.
		{
			s.pop();
			path.PB(v);
		}
		else
			s.push(g[v][--degree[v]].destination);
	}
	reverse(ALL(path)); //Path is reversed.
	return edges == SIZE(path); //true if all edges are in the path.
}

//Algorithm works in the same way, but it has to store visited edges - there exist both normal and transpose edges.
template<class Vertex, class Edge> bool Graph<Vertex, Edge>::EulerUndirected(VI &path)
{
	int v = -1;
	path.clear();
	VI degree(SIZE(g), 0), edges(SIZE(g) + 1, 0);
	stack<int> s;
	REP(SIZE(g))
	{
		edges[i + 1] = edges[i] + (degree[i] = SIZE(g[i]));
		if (degree[i] || (v == -1 && degree[i]))
			v = i;
	}
	vector<bool> used(edges[SIZE(g)], 0);
	if (v != -1)
		s.push(v);
	while (!s.empty())
	{
		v = s.top();
		while (degree[v] && used[edges[v] + degree[v] - 1])
			--degree[v];
		if (!degree[v])
		{
			s.pop();
			path.PB(v);
		}
		else
		{
			int u = g[v][--degree[v]].destination;
			used[edges[u] + g[v][degree[v]].rev] = 1;
			s.push(v = u);
		}
	}
	return 2 * (SIZE(path) - 1) == edges[SIZE(g)];
}

struct Empty
{

};

struct EdgeUndirected
{
	int rev;
};
