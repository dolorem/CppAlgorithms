#include "graph.h"

template<class Vertex, class Edge> void Graph<Vertex, Edge>::BFS(int source)
{
	FOREACH(it, g)
		it->ancestor = it->distance = -1; //Ustawiamy domyślne wartości przodka i odległości.
	g[source].distance = 0; //d(u, u) = 0; - własność odległości (nie do końca, bo może istnieć krawędź o ujemnej wadze z wierzchołka do niego samego, ale to się prawie nie zdarza.
	queue<int> q; //Kolejka z wierzchołkami do przetworzenia.
	q.push(source); //Od czegoś trzeba zacząć.
	while (!q.empty())
	{
		source = q.front(); //Aktualny wierzchołek.
		q.pop();
		FOREACH(it, g[source])
		{
			if (g[it->destination].distance == -1) //Wierzchołek nie został jeszcze odwiedzony
			{
				g[it->destination].distance = g[source].distance + 1; //Aktualizujemy odległość.
				g[it->destination].ancestor = source; //Ustawiamy rodzica w drzewie przeszukiwań wszerz.
				q.push(it->destination); //I dodajemy wierzchołek do przetworzenia.
			}
		}
	}

}

struct Empty
{

};

struct VertexBFS
{
	int distance, ancestor;
};
