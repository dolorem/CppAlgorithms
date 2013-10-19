#include "../bfs.h"

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
	ifstream file("tests/graph/in/bfs.in");
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

void test()
{
	BFSTest();
}
