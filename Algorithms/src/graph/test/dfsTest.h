#include "../dfs.h"

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
	ifstream file("tests/graph/in/dfs.in");
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

void test()
{
	DFSTest();
}
