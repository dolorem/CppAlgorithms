#include "../header.h"

template<class Vertex, class Edge> struct Graph //Struktura generyczna reprezentująca graf.
{
	struct EdgeExtended : Edge //Rozszerza dodatkowe informacje o krawędzi o jej wierzchołek docelowy.
	{
		int destination; //Wierzchołek docelowy krawędzi.

		//Konstruktor tworzy nową krawędź i ustala wierzchołek docelowy.
		EdgeExtended(int dest, Edge additional = Edge()) : Edge(additional), destination(dest)
		{

		}
	};

	struct VertexExtended : Vertex, vector<EdgeExtended> //Rozszerza wektor w celu łatwiejszej iteracji.
	{

	};

	vector<VertexExtended> g; //Graf.

	Graph(int n = 0) : g(n)
	{

	}

	//Dodaje wierzchołek nieskierowany do grafu.
	//Pole rev zawiera indeks krawędzi zwrotnej - krawędź nieskierowana reprezentowana jest przez dwie krawędzie skierowane.
	void addUndirectedEdge(int u, int v, Edge eg = Edge())
	{
		EdgeExtended e(u, eg);
		e.rev = SIZE(g[u]) + (u == v); //Szczególny przypadek - krawędź wychodzi z tego samego wierzchołka, do którego wchodzi.
		g[v].PB(e);
		e.destination = v;
		e.rev = SIZE(g[v]) - 1; //Odejmujemy 1, ponieważ ta krawędź już została dodana, a pole zawiera indeks.
		g[u].PB(e);
	}

	//Dodaje krawędź skierowaną do grafu.
	void addDirectedEdge(int u, int v, Edge additional = Edge())
	{
		g[u].PB(EdgeExtended(v, additional));
	}

	//Wypisuje graf w rosnącej kolejności wierzchołków, następnie wierzchołki do których można dojść bezpośrednio z danego wierzchołka.
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
