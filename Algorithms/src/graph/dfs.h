#include "graph.h"

//Przeszukiwanie grafu w głąb z zadanego źródła.
template<class Vertex, class Edge> void Graph<Vertex, Edge>::DFS(int source = -1)
{
	FOREACH(it, g)
					it->pre = it->post = it->ancestor = -1; //Ustawiamy domyślne wartości czasu pre- i post-visit oraz przodka.
	int time = 0; //Licznik czasu dla pre- i post-visit.
	if (source != -1) //Źródło zostało dane.
		time = DFSVisit(source, time);
	REP(SIZE(g))
	{
		if (g[i].pre == -1) //Wierzchołek nie został jeszcze odwiedzony.
			time = DFSVisit(i, time); //Tworzymy nowe drzewo w lesie przeszukiwań w głąb.
	}
}

//Rekurencyjnie odwiedza graf w głąb.
template<class Vertex, class Edge> int Graph<Vertex, Edge>::DFSVisit(int source, int time)
{
	g[source].pre = time++; //Ustawia czas pre-visit.
	FOREACH(it, g[source])
	{
		if (g[it->destination].pre == -1) //Wierzchołek nie został jeszcze odwiedzony.
		{
			g[it->destination].ancestor = source; //Ustawiamy przodka w lesie przeszukiwań w głąb.
			time = DFSVisit(it->destination, time); //Potrzebna jest rekurencyjna aktualizacja czasu.
		}
	}
	g[source].post = time++; //Ustawia czas post-visit.
	return time;
}

struct VertexDFS
{
	int ancestor, pre, post;
};

struct Empty
{

};
