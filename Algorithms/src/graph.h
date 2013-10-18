#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <fstream>

using namespace std;

typedef vector<int> VI;

#define VAR(a, b) typeof(a) b = (a)
#define FOREACH(it, col) for(VAR((col).begin(), it); it != (col).end(); ++it)
#define REP(x) for(int i = 0; i < x; i++)
#define PB push_back
#define ST first
#define ND second
#define SIZE(x) x.size()

template<class Vertex, class Edge> struct Graph
{
	struct EdgeExtended : Edge
	{
		int v;

		EdgeExtended(int destination, Edge additional) : Edge(additional), v(destination)
		{

		}
	};

	struct VertexExtended : Vertex, vector<EdgeExtended>
	{

	};

	vector<VertexExtended> g;

	Graph(int n = 0) : g(n)
	{

	}

	void addDirectedEdge(int u, int v, Edge additional = Edge())
	{
		g[u].PB(EdgeExtended(v, additional));
	}

	void addUndirectedEdge(int u, int v, Edge additional = Edge())
	{
		EdgeExtended e(v, additional);
		e.rev = SIZE(g[v]) + (u == v);
		g[u].PB(e);
		e.v = u;
		e.rev = SIZE(g[u]) - 1;
		g[v].PB(e);
	}

	void write()
	{
		REP(SIZE(g))
		{
			cout << i << ": ";
			FOREACH(it, g[i])
				cout << it->v << " ";
			cout << endl;
		}
	}

	void BFS(int s)
	{
		queue<int> Q;
		FOREACH(it, g)
			it->distance = it->ancestor = -1;
		Q.push(s);
		g[s].distance = 0;
		while (!Q.empty())
		{
			s = Q.front();
			Q.pop();
			FOREACH(it, g[s])
			{
				if (g[it->v].distance == -1)
				{
					g[it->v].distance = g[s].distance + 1;
					g[it->v].ancestor = s;
					Q.push(it->v);
				}
			}
		}
	}

	void DFS(int s = -1)
	{
		FOREACH(it, g)
			it->pre = it->post = it->ancestor = -1;
		int time = 0;
		if (s != -1)
			time = DFSVisit(s, time);
		REP(SIZE(g))
		{
			if (g[i].pre == -1)
				time = DFSVisit(i, time);
		}
	}

	int DFSVisit(int v, int time)
	{
		g[v].pre = time++;
		FOREACH(it, g[v])
		{
			if (g[it->v].pre == -1)
			{
				g[it->v].ancestor = v;
				time = DFSVisit(it->v, time);
			}
		}
		g[v].post = time++;
		return time;
	}
};

struct VertexBFS
{
	int distance, ancestor;
};

struct Empty
{

};

struct VertexDFS
{
	int pre, post, ancestor;
};


//Wierzchołek 0: 1
//Wierzchołek 1: 2
//Wierzchołek 2: 4
//Wierzchołek 3: 4 2
//Wierzchołek 4: 1 0 3
void graphTest()
{
	ifstream file("graphTest.txt");
	int a, b, c, d;
	file >> a >> b;
	Graph<Empty, Empty> g(a);
	REP(b)
	{
		file >> c >> d;
		g.addDirectedEdge(c, d);
	}
	g.write();
}

//0 - distance 0 ancestor -1
//1 - distance 1 ancestor 0
//2 - distance 1 ancestor 0
//3 - distance 2 ancestor 1
//4 - distance 2 ancestor 1
//5 - distance 2 ancestor 2
//6 - distance 2 ancestor 2
void BFSTest()
{
	int a, b, c, d, s;
	ifstream file("BFS.in");
	file >> a >> b >> s;
	Graph<VertexBFS, Empty> g(a);
	REP(b)
	{
		file >> c >> d;
		g.addDirectedEdge(c, d);
	}
	g.BFS(s);
	REP(a)
	cout << i << " - distance " << g.g[i].distance << " ancestor " << g.g[i].ancestor << endl;
}

//0 - pre 0 post 13 ancestor -1
//1 - pre 1 post 6 ancestor 0
//2 - pre 7 post 12 ancestor 0
//3 - pre 2 post 3 ancestor 1
//4 - pre 4 post 5 ancestor 1
//5 - pre 8 post 9 ancestor 2
//6 - pre 10 post 11 ancestor 2
void DFSTest()
{
	int a, b, c, d, s;
	ifstream file("BFS.in");
	file >> a >> b >> s;
	Graph<VertexDFS, Empty> g(a);
	REP(b)
	{
		file >> c >> d;
		g.addDirectedEdge(c, d);
	}
	g.DFS(s);
	REP(a)
	cout << i << " - pre " << g.g[i].pre << " post " << g.g[i].post << " ancestor " << g.g[i].ancestor << endl;
}
/*
//0 - distance 0 ancestor -1
//1 - distance 10 ancestor 0
//2 - distance 15 ancestor 0
//3 - distance 20 ancestor 2
//4 - distance 30 ancestor 3
//5 - distance 32 ancestor 4
void DijkstraTest()
{
	int n, m, s, b, e;
	EdgeDijkstra ed;
	ifstream file("Dijkstra.in");
	file >> n >> m >> s;
	Graph<VertexDijkstra, EdgeDijkstra> g(n);
	REP(m)
	{
		file >> b >> e >> ed.weight;
		g.addUndirectedEdge(b, e, ed);
	}
	g.Dijkstra(s);
	REP(n)
	cout << i << " - distance " << g.g[i].distance << " ancestor " << g.g[i].ancestor << endl;
}

//0 2 3 4 5 3 6 2 1 0
//3 4 5 3 2 0 1 2 6
void EulerTest()
{
	VI res;
	int n, m, b, e;
	ifstream file("eulerTest.txt");
	file >> n >> m;
	Graph<Empty, Empty> g(n);
	Graph<Empty, EdgeUndirected> g2(n);
	REP(m)
	{
		file >> b >> e;
		g.addDirectedEdge(b, e);
	}
	file >> n >> m;
	REP(m)
	{
		file >> b >> e;
		g2.addUndirectedEdge(b, e);
	}
	if (g.EulerDirected(res))
	{
		FOREACH(it, res)
						cout << *it << " ";
		cout << endl;
	}
	else
		cout << "Brak ścieżki Eulera." << endl;
	if (g2.EulerUndirected(res))
	{
		FOREACH(it, res)
						cout << *it << " ";
		cout << endl;
	}
	else
		cout << "Brak ścieżki Eulera." << endl;
}

//0
//1
void AcyclicTest()
{
	int a, b, c, d;
	ifstream file("acyclicTest.txt");
	file >> a >> b;
	Graph<VertexScc, Empty> g(a);
	REP(b)
	{
		file >> c >> d;
		g.addDirectedEdge(c, d);
	}
	cout << g.isAcyclicDirected() << endl;
	file >> a >> b;
	Graph<Empty, EdgeUndirected> g2(a);
	REP(b)
	{
		file >> c >> d;
		g2.addUndirectedEdge(c, d);
	}
	cout << g2.isAcyclicUndirected() << endl;
}

//Kolejność topologiczna wierzchołków: 0 1 3 4 2 5
//Wierzchołek 0 ma pozycję 0 w porządku topologicznym.
//Wierzchołek 1 ma pozycję 1 w porządku topologicznym.
//Wierzchołek 2 ma pozycję 4 w porządku topologicznym.
//Wierzchołek 3 ma pozycję 2 w porządku topologicznym.
//Wierzchołek 4 ma pozycję 3 w porządku topologicznym.
//Wierzchołek 5 ma pozycję 5 w porządku topologicznym.
void TopoTest()
{
	ifstream file("topoTest.txt");
	int a, b, c, d;
	file >> a >> b;
	Graph<VertexScc, Empty> g(a);
	REP(b)
	{
		file >> c >> d;
		g.addDirectedEdge(c, d);
	}
	VI sorted = g.topoSortV();
	cout << "Kolejność topologiczna wierzchołków: ";
	FOREACH(it, sorted)
	cout << *it << " ";
	cout << endl;
	REP(a)
	cout << "Wierzchołek " << i << " ma pozycję " << g.g[i].t << " w porządku topologicznym." << endl;
}

//Wierzchołek 0 silnie spójna składowa nr 0
//Wierzchołek 1 silnie spójna składowa nr 0
//Wierzchołek 2 silnie spójna składowa nr 2
//Wierzchołek 3 silnie spójna składowa nr 2
//Wierzchołek 4 silnie spójna składowa nr 2
//Wierzchołek 5 silnie spójna składowa nr 1
//Wierzchołek 6 silnie spójna składowa nr 3
//Wierzchołek 7 silnie spójna składowa nr 4
//Graf silnie spójnych składowych:
//Wierzchołek 0: 2 3 4
//Wierzchołek 1: 2
//Wierzchołek 2:
//Wierzchołek 3: 4
//Wierzchołek 4:
void SccTest()
{
	ifstream file("sccTest.txt");
	int a, b, c, d;
	file >> a >> b;
	Graph<VertexScc, Empty> g(a);
	REP(b)
	{
		file >> c >> d;
		g.addDirectedEdge(c, d);
	}
	Graph<VertexScc, Empty> scc = g.scc();
	REP(a)
	cout << "Wierzchołek " << i << " silnie spójna składowa nr " << g.g[i].t << endl;
	cout << "Graf silnie spójnych składowych:" << endl;
	scc.write();
}

//Waga - 61
//Krawędzie:  (0,1) (1,2) (0,3) (1,5) (4,5)
void MSTTest()
{
	int n, m, b, e;
	ifstream file("MST.in");
	file >> n >> m;
	MSTEdge l;
	Graph<Empty, MSTEdge> g(n);
	REP(m)
	{
		file >> b >> e >> l.weight;
		g.addUndirectedEdge(b, e ,l);
	}
	cout << "Waga - " << g.MinSpanTree() << endl;
	cout << "Krawędzie: ";
	REP(n)
	{
		FOREACH(it, g.g[i])
		{
			if (it->span && it->destination < i)
				cout << " (" << it->destination << "," << i << ")";
		}
	}
	cout << endl;
}

//0 - distance 0 ancestor -1
//1 - distance 3 ancestor 0
//2 - distance -2 ancestor 1
//3 - distance 5 ancestor 1
//4 - distance 7 ancestor 3
void BellmanFordTest()
{
	int n, m, s, b, e;
	EdgeBellmanFord ed;
	ifstream file("BellmanFord.in");
	file >> n >> m >> s;
	Graph<VertexBellmanFord, EdgeBellmanFord> g(n);
	REP(m)
	{
		file >> b >> e >> ed.weight;
		g.addDirectedEdge(b, e, ed);
	}
	g.BellmanFord(s);
	REP(n)
		cout << i << " - distance " << g.g[i].distance << " ancestor " << g.g[i].ancestor << endl;
}*/

int testAll()
{
	graphTest();
	cout << endl;
	BFSTest();
	cout << endl;
	DFSTest();
	cout << endl;
	/*DijkstraTest();
	cout << endl;
	SccTest();
	cout << endl;
	TopoTest();
	cout << endl;
	AcyclicTest();
	cout << endl;
	EulerTest();
	cout << endl;
	MSTTest();
	cout << endl;
	BellmanFordTest();*/
}
