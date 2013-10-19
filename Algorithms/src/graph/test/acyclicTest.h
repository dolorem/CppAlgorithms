#include "../acyclic.h"

//0
//1
void AcyclicTest()
{
	int a, b, c, d;
	ifstream file("tests/graph/in/acyclic.in");
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

void test()
{
	AcyclicTest();
}
