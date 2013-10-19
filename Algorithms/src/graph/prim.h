#include "graph.h"

//Wyznacza minimalne drzewo rozpinające za pomocą algorytmu Prima.
//Pole span zawiera true jeśli krawędź należy do MST.
//Zwraca wagę drzewa.
template<class Vertex, class Edge> int Graph<Vertex, Edge>::Prim()
{
	int r = 0, d[SIZE(g)]; //Dla każdego wierzchołka nienależącego do MST przechowuje długość najkrótszej krawędzi łączącej go z dowolnym wierzchołkiem drzewa.
	bool o[SIZE(g)]; //Odznacza wierzchołki dodane do drzewa.
	REP(SIZE(g))
	{
		d[i] = INF;
		o[i] = 0;
	}
	set<PII> s; //Kolejka priorytetowa wierzchołków osiągalnych z budowanego drzewa, w kolejności niemalejących wag krawędzi.
	s.insert(MP(d[0] = 0, 0));
	while (!s.empty())
	{
		int v = (s.begin())->ND; //Wybiera wierzchołek którego dodanie jest najtańsze.
		s.erase(s.begin()); //Usuwa go z kolejki.
		bool t = 0;
		o[v] = 1; //Zaznacza jako odwiedzony.
		r += d[v];  //Zwiększa wagę drzewa.
		FOREACH(it, g[v])
		{
			it->span = 0;
			if (!t && o[it->destination] && it->weight == d[v]) //Krawędź, którą dodano do drzewa.
				t = it->span = g[it->destination][it->rev].span = 1;
			else if (!o[it->destination] && d[it->destination] > it->weight) //Aktualizujemy odległości pozostałych wierzchołków.
			{
				s.erase(MP(d[it->destination], it->destination));
				s.insert(MP(d[it->destination] = it->weight, it->destination));
			}
		}
	}
	return r;
}

struct PrimEdge
{
	int rev, weight;
	bool span;
};

struct Empty
{

};
