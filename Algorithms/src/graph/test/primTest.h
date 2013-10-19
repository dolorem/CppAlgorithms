#include "../prim.h"

//Waga - 61
//Krawędzie:  (0,1) (1,2) (0,3) (1,5) (4,5)
void PrimTest()
{
	int n, m, b, e;
	ifstream file("tests/graph/in/prim.in");
	file >> n >> m;
	PrimEdge l;
	Graph<Empty, PrimEdge> g(n);
	REP(m)
	{
		file >> b >> e >> l.weight;
		g.addUndirectedEdge(b, e ,l);
	}
	cout << "Waga - " << g.Prim() << endl;
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

void test()
{
	PrimTest();
}
