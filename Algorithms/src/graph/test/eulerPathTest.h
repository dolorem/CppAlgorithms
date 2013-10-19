#include "../eulerPath.h"

//0 2 3 4 5 3 6 2 1 0
//3 4 5 3 2 0 1 2 6
void EulerTest()
{
	VI res;
	int n, m, b, e;
	ifstream file("tests/graph/in/euler.in");
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

void test()
{
	EulerTest();
}
