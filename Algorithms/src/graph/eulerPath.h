#include "graph.h"

template<class Vertex, class Edge> bool Graph<Vertex, Edge>::EulerDirected(VI &path)
{
	path.clear(); //Resetujemy wektor.
	int edges = 1, v = -1, h;
	stack<int> s;
	VI degree(SIZE(g), 0); //Będzie zawierał stopnie wyjściowe wierzchołków.
	REP(SIZE(g))
	{
		FOREACH(it, g[i])
						degree[it->destination]++; //Które teraz ustawiamy.
	}
	REP(SIZE(g)) //Wyznaczamy wierzchołek początkowy.
	{
		if ((h = degree[i]) > SIZE(g[i])) //Jeśli ma większy stopień wyjściowy od wejściowego, zostaje nowym kandydatem na wierzchołek startowy.
			v = i;
		else if (v == -1 && h) //Jeśli nie jest izolowany i nie ma jeszcze wierzchołka startowego, to samo.
			v = i;
		edges += h;
	}
	if (v != -1) //Znaleziono wierzchołek początkowy, algorytm może przejść do następnego kroku.
		s.push(v);
	while (!s.empty()) //Dopóki stos nie jest pusty, przeszukuje graf w głąb.
	{
		if (!degree[v = s.top()]) //Wszystkie krawędzie zostały przetworzone, cofamy się dodając krawędzie powrotne do ścieżki Eulera.
		{
			s.pop();
			path.PB(v);
		}
		else
			s.push(g[v][--degree[v]].destination);
	}
	reverse(ALL(path)); //Ścieżka Eulera wyznaczona jest w odwrotnym kierunku.
	return edges == SIZE(path); //Prawda, jeśli wszyskie krawędzie należą do ścieżki.
}

//Algorytm działa tak samo jak dla grafów skierowanych, ale musi dodatkowo odznaczać wykorzystane krawędzie (występują niejako podwójnie - normalna i transponowana).
template<class Vertex, class Edge> bool Graph<Vertex, Edge>::EulerUndirected(VI &path)
{
	int v = -1;
	path.clear();
	VI degree(SIZE(g), 0), edges(SIZE(g) + 1, 0);
	stack<int> s;
	REP(SIZE(g))
	{
		edges[i + 1] = edges[i] + (degree[i] = SIZE(g[i]));
		if (degree[i] || (v == -1 && degree[i]))
			v = i;
	}
	vector<bool> used(edges[SIZE(g)], 0); //Wektor służący do odznaczania wykorzystanych krawędzi.
	if (v != -1)
		s.push(v);
	while (!s.empty())
	{
		v = s.top();
		while (degree[v] && used[edges[v] + degree[v] - 1])
			--degree[v];
		if (!degree[v])
		{
			s.pop();
			path.PB(v);
		}
		else
		{
			int u = g[v][--degree[v]].destination;
			used[edges[u] + g[v][degree[v]].rev] = 1;
			s.push(v = u);
		}
	}
	return 2 * (SIZE(path) - 1) == edges[SIZE(g)];
}

struct Empty
{

};

struct EdgeUndirected
{
	int rev;
};
