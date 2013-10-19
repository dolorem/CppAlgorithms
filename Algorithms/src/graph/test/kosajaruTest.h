#include "../kosajaru.h"

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
	ifstream file("tests/graph/in/kosajaru.in");
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

void test()
{
	SccTest();
}
