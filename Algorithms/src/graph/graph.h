/**
 * graph.h
 * Template structure representing a graph. Adjacency lists are used.
 * Undirected graphs are represented as directed graphs with double edges.
 *
 * @author Śmiech Mateusz
 * @version 0.0.0
 */

#include "../header.h"

template<class Vertex, class Edge> struct Graph
{
	struct EdgeExtended : Edge
	{
		int destination;

		EdgeExtended(int dest, Edge additional = Edge()) : Edge(additional), destination(dest)
		{

		}
	};

	struct VertexExtended : Vertex, vector<EdgeExtended> //Extends vector class to make iteration easier.
	{

	};

	vector<VertexExtended> g; //Graph.

	Graph(int n = 0) : g(n)
	{

	}

	//Rev field contains index of return edge.
	void addUndirectedEdge(int u, int v, Edge eg = Edge())
	{
		EdgeExtended e(u, eg);
		e.rev = SIZE(g[u]) + (u == v); //Special case - source = destination.
		g[v].PB(e);
		e.destination = v;
		e.rev = SIZE(g[v]) - 1;
		g[u].PB(e);
	}

	void addDirectedEdge(int u, int v, Edge additional = Edge())
	{
		g[u].PB(EdgeExtended(v, additional));
	}

	void write()
	{
		REP(SIZE(g))
		{
			cout << "Wierzchołek " << i << ": ";
			FOREACH(it, g[i])
				cout << it->destination << " ";
			cout << endl;
		}
	}

	void BFS(int);
	void DFS(int);
	int DFSVisit(int, int);
	struct DijkstraComparator;
	void Dijkstra(int);
	void sccDfs(int, int, bool);
	Graph<Vertex, Edge> scc();
	VI visited;
	Graph<Vertex, Edge> *sccRes;
	VI topoSortV();
	void topoSort();
	int topoDfs(int, int);
	VB vis;
	bool acyclic;
	bool isAcyclicUndirected();
	bool isAcyclicDirected();
	void acyclicDfs(int, Edge*);
	bool EulerUndirected(VI&);
	bool EulerDirected(VI&);
	int Prim();
	bool BellmanFord(int);
};
