#include "../dijkstra.h"

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
	ifstream file("tests/graph/in/dijkstra.in");
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

void test()
{
	DijkstraTest();
}
