#include "graph.h"

//Suruktura definiująca niemalejący porządek wierzchołków względem ich odległości od źródła.
template<class Vertex, class Edge> struct Graph<Vertex, Edge>::DijkstraComparator
{
	bool operator() (const VertexExtended *a, const VertexExtended *b) const
	{
		if (a->distance == b->distance)
			return a < b;
		return (a->distance) < (b->distance);
	}
};

//Algorytm Dijkstry znajdowania najkrótszych ścieżek z danego źródła w grafie ważonym.
//WAŻNE!! Wagi nie mogą być ujemne.
template<class Vertex, class Edge> void Graph<Vertex, Edge>::Dijkstra(int s)
{
	set<VertexExtended*, DijkstraComparator> q; //kolejka priorytetowa w postaci zbioru, ulepszeniem byłby kopiec Fibonacciego, ale jest to doś skomplikowana struktura danych
	FOREACH(it, g)
	{
		it->distance = INF;
		it->ancestor = -1;
	}
	g[s].distance = 0;
	q.insert(&g[s]); //Dodajemy źródło do kolejki.
	VertexExtended *v; //Wskaźnik do aktualnie przetwarzanego wierzchołka.
	while (!q.empty())
	{
		v = *(q.begin()); //Odpowiednik top()
		q.erase(q.begin()); //Odpowiednik pop()
		FOREACH(it, *v) //Sprawdzamy wszystkie krawędzie.
		{
			if (g[it->destination].distance > v->distance + it->weight) //Dana krawędź może zmniejszyć wartość odległości dla wierzchołka docelowego.
			{
				//Tutaj wymagany jest myk z erase() i insert() - set nie obsługuje automatycznej obserwacji zmian elementów, musimy go usunąć i wstawić ponownie aby przetwarzał właściwą odległość.
				q.erase(&g[it->destination]);
				g[it->destination].distance = v->distance + it->weight;
				g[it->destination].ancestor = v - &g[0]; //Odejmowanie wskaźników - odległość między elementami w tablicy (wektorze).
				q.insert(&g[it->destination]);
			}
		}
	}
}

struct VertexDijkstra
{
	int distance, ancestor;
};

struct EdgeDijkstra
{
	int weight, rev;
};
