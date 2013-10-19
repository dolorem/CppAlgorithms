#include "../bellmanFord.h"

//0 - distance 0 ancestor -1
//1 - distance 3 ancestor 0
//2 - distance -2 ancestor 1
//3 - distance 5 ancestor 1
//4 - distance 7 ancestor 3
void BellmanFordTest()
{
	int n, m, s, b, e;
	EdgeBellmanFord ed;
	ifstream file("tests/graph/in/bellmanFord.in");
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
}

int test()
{
	BellmanFordTest();
}
