#include "../topologicalSortDfs.h"

//Kolejność topologiczna wierzchołków: 0 1 3 4 2 5
//Wierzchołek 0 ma pozycję 0 w porządku topologicznym.
//Wierzchołek 1 ma pozycję 1 w porządku topologicznym.
//Wierzchołek 2 ma pozycję 4 w porządku topologicznym.
//Wierzchołek 3 ma pozycję 2 w porządku topologicznym.
//Wierzchołek 4 ma pozycję 3 w porządku topologicznym.
//Wierzchołek 5 ma pozycję 5 w porządku topologicznym.
void TopoTest()
{
	ifstream file("tests/graph/in/topological.in");
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

void test()
{
	TopoTest();
}
