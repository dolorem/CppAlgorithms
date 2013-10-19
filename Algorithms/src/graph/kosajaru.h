#include "graph.h"

//Algorytm Kosaraju - podwójny DFS. Stos jest symulowany za pomocą wektora.
//Obserwacja - graf transponowany ma silnie spójne składowe tożsame z oryginalnym.
//Θ(V+E) w przypadku list sąsiedztwa.
//W pierwszej fazie ustala porządek dla drugiej, później tworzy graf silnie spójnych składowych.
template<class Vertex, class Edge> void Graph<Vertex, Edge>::sccDfs(int v, int nr, bool firstPhase)
{
	g[v].t = 1; //Oznacza wierzchołek jako odwiedzony.
	if (!firstPhase)
		visited[v] = nr; //Numer silnie spójnej składowej.
	FOREACH(it, g[v])
	{
		if (g[it->destination].t == -1) //Wierzchołek nie był odwiedzony, faza nie ma znaczenia.
			sccDfs(it->destination, nr, firstPhase);
		else if (!firstPhase && nr > visited[it->destination]) //Wierzchołek był odwiedzony, jesteśmy w drugiej fazie i krawędź prowadzi do zakończonej już (mniejszy numer) silnie spójnej składowej - trzeba dodać krawędź do grafu.
			sccRes->addDirectedEdge(g[it->destination].t, visited[it->destination] = nr);
	}
	if (firstPhase)
		visited.PB(v); //Dodaje wierzchołek do wektora
	else
		g[v].t = nr;
}

template<class Vertex, class Edge> Graph<Vertex, Edge> Graph<Vertex, Edge>::scc()
{
	//gt - graf transponowany
	//*tab[] wskazuje który graf (oryginalny czy transponowany) powinien być przetworzony w danej iteracji
	//res - graf silnie spójnych składowych
	Graph<Vertex, Edge> gt(SIZE(g)), res(SIZE(g)), *tab[] = {this, &gt};
	visited.clear();
	gt.visited.resize(SIZE(g), -1); //Wypełnia wektor SIZE(g) minus jedynkami.
	gt.sccRes = &res; //Ustawia referencję do grafu silnie spójnych składowych w grafie transponowanym, na którym wykonywany będzie drugi przebieg algorytmu.
	REP(SIZE(g))
	{
		FOREACH(it, g[i])
						gt.addDirectedEdge(it->destination, i); //Tworzy graf transponowany.
	}
	REP(2)
	{
		FOREACH(it, tab[i]->g)
						it->t = -1; //Pole t decyduje czy wierzchołek był odwiedzony, a po drugiej iteracji zawiera także numer silnie spójnej składowej.
		int counter = 0, v; //Counter zawiera liczbę silnie spójnych składowych, v aktualnie przetwarzany wierzchołek.
		for (int j = SIZE(g) - 1; j >= 0; j--) //W pierwszej iteracji to, że indeksy maleją nie ma znaczenia, ale jest wymagane podczas drugiej - tak działa algorytm.
		{
			if (tab[i]->g[v = i ? visited[j] : j].t == -1) //Podczas pierwszej iteracji odwiedzamy wierzchołek j, podczas drugiej - ten, który był odwiedzony jako j-ty (visited[j]).
				tab[i]->sccDfs(v, counter++, 1 - i);
		}
		if (i)
			res.g.resize(counter);
	}
	REP(SIZE(g))
		g[i].t = gt.g[i].t; //Ustawia numery silnie spójnych składowych w grafie oryginalnym na bazie grafu transponowanego (patrz obserwacja na górze).
	return res;
}

struct VertexScc
{
	int t;
};

struct Empty
{

};
