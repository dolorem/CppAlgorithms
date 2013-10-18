#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <set>
#include <stack>
#include <algorithm>

using namespace std;

typedef vector<int> VI;
typedef vector<bool> VB;
typedef pair<int, int> PII;

#define VAR(v,n) typeof(n) v=(n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define REP(x) for(int i = 0; i < x; i++)
#define SIZE(x) x.size()
#define PB push_back
#define ALL(x) x.begin(), x.end()
#define MP make_pair
#define ND second
// (int) 2147483647 + (int) 2147483647 = -2
const int INF = 1000000001;

template<class Vertex, class Edge> struct Graph //Struktura generyczna reprezentująca graf.
{
	struct EdgeExtended : Edge //Rozszerza dodatkowe informacje o krawędzi o jej wierzchołek docelowy.
	{
		int destination; //Wierzchołek docelowy krawędzi.

		//Konstruktor tworzy nową krawędź i ustala wierzchołek docelowy.
		EdgeExtended(int dest, Edge additional = Edge()) : Edge(additional), destination(dest)
		{

		}
	};

	struct VertexExtended : Vertex, vector<EdgeExtended> //Rozszerza wektor w celu łatwiejszej iteracji.
	{

	};

	vector<VertexExtended> g; //Graf.

	Graph(int n = 0) : g(n)
	{

	}

	//Dodaje wierzchołek nieskierowany do grafu.
	//Pole rev zawiera indeks krawędzi zwrotnej - krawędź nieskierowana reprezentowana jest przez dwie krawędzie skierowane.
	void addUndirectedEdge(int u, int v, Edge eg = Edge())
	{
		EdgeExtended e(u, eg);
		e.rev = SIZE(g[u]) + (u == v); //Szczególny przypadek - krawędź wychodzi z tego samego wierzchołka, do którego wchodzi.
		g[v].PB(e);
		e.destination = v;
		e.rev = SIZE(g[v]) - 1; //Odejmujemy 1, ponieważ ta krawędź już została dodana, a pole zawiera indeks.
		g[u].PB(e);
	}

	//Dodaje krawędź skierowaną do grafu.
	void addDirectedEdge(int u, int v, Edge additional = Edge())
	{
		g[u].PB(EdgeExtended(v, additional));
	}

	//Wypisuje graf w rosnącej kolejności wierzchołków, następnie wierzchołki do których można dojść bezpośrednio z danego wierzchołka.
	void write()
	{
		REP(SIZE(g))
		{
			cout << "Wierzchołek " << i << ": ";
			FOREACH(it, g[i])
				cout << it->destination << " ";
			cout << endl;
		}
	}

	//Przeszukiwanie grafu w głab od zadanego źródła.
	void BFS(int source)
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

	//Przeszukiwanie grafu w głąb z zadanego źródła.
	void DFS(int source = -1)
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
	int DFSVisit(int source, int time)
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

	//Struktura definiująca niemalejący porządek wierzchołków względem ich odległości od źródła.
	struct DijkstraComparator
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
	void Dijkstra(int s)
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

	//Algorytm Kosaraju - podwójny DFS. Stos jest symulowany za pomocą wektora.
	//Obserwacja - graf transponowany ma silnie spójne składowe tożsame z oryginalnym.
	//Θ(V+E) w przypadku list sąsiedztwa.
	VI visited;
	Graph<Vertex, Edge> *sccRes;

	//W pierwszej fazie ustala porządek dla drugiej, później tworzy graf silnie spójnych składowych.
	void sccDfs(int v, int nr, bool firstPhase)
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

	Graph<Vertex, Edge> scc()
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

	//Sortowanie topologiczne, zwraca wektor zawierający wierzchołki w posortowanej kolejności.
	VI topoSortV()
	{
		VI sorted(SIZE(g));
		topoSort();
		REP(SIZE(g))
			sorted[g[i].t] = i;
		return sorted;
	}

	//Sortuje topologicznie, kolejność będzie zawarta w polu t.
	void topoSort()
	{
		int index = SIZE(g) - 1;
		FOREACH(it, g)
		it->t = 0;
		for (int i = SIZE(g) - 1; i >= 0; i--)
			index = topoDfs(i, index);
	}

	//DFS do sortowania topologicznego.
	int topoDfs(int v, int index)
	{
		if (!g[v].t)
		{
			g[v].t = 1;
			FOREACH(it, g[v])
				index = topoDfs(it->destination, index);
			g[v].t = index--;
		}
		return index;
	}

	//Sprawdza, czy dany graf skierowany jest acykliczny.
	bool isAcyclicDirected()
	{
		topoSort(); //Najpierw sortuje go topologicznie.
		REP(SIZE(g))
		{
			FOREACH(it, g[i])
			{
				if (g[i].t >= g[it->destination].t) //Sprawdza czy wszystkie wierzchołki prowadzą do wierzchołków o mniejszym numerze.
					return false;
			}
		}
		return true;
	}

	VB vis;
	bool acyclic;

	//Sprawdza czy dany graf nieskierowany jest acykliczny.
	bool isAcyclicUndirected()
	{
		acyclic = true;
		vis.resize(SIZE(g), 0);
		REP(SIZE(g))
		{
			if (!vis[i])
				acyclicDfs(i, 0);
		}
		return acyclic;
	}

	void acyclicDfs(int v, Edge *e)
	{
		if (!vis[v]) //Wierzchołek nie był odwiedzony, jest ok.
		{
			vis[v] = true;
			FOREACH(it, g[v])
			{
				if (&*it != e) //Nie chcemy się cofnąć krawędzią z której przyszliśmy.
					acyclicDfs(it->destination, &g[it->destination][it->rev]);
			}
		}
		else //Wierzchołek był odwiedzony, znaleziono cykl.
			acyclic = false;
	}

	
	bool EulerDirected(VI &path)
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
	bool EulerUndirected(VI &path)
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

	//Wyznacza minimalne drzewo rozpinające za pomocą algorytmu Prima.
	//Pole span zawiera true jeśli krawędź należy do MST.
	//Zwraca wagę drzewa.
	int MinSpanTree()
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

	
	bool BellmanFord(int v)
	{
		FOREACH(it, g)
			it->distance = INF;
		g[v].distance = 0;
		g[v].ancestor = -1;
		int change, cnt = 0;
		do //Dopóki dokonana została poprawa, ale nie więcej niż SIZE(g) razy.
		{
			change = 0;
			REP(SIZE(g))
			{
				FOREACH(it, g[i])
				{
					if (g[i].distance + it->weight < g[it->destination].distance) //Relaksuje krawędzie.
					{
						g[it->destination].distance = g[i].distance + it->weight;
						g[it->destination].ancestor = i;
						change = 1;
					}
				}
			}
		}
		while (change && ++cnt < SIZE(g));
		return cnt == SIZE(g); //true jeśli istnieje cykl o ujemnej wadze.
	}
};

struct Empty
{

};

struct VertexBFS
{
	int distance, ancestor;
};

struct VertexDFS
{
	int ancestor, pre, post;
};

struct VertexDijkstra
{
	int distance, ancestor;
};

struct EdgeDijkstra
{
	int weight, rev;
};

struct EdgeUndirected
{
	int rev;
};

struct VertexScc
{
	int t;
};

struct MSTEdge
{
	int rev, weight;
	bool span;
};

struct VertexBellmanFord
{
	int distance, ancestor;
};

struct EdgeBellmanFord
{
	int weight;
};

//Wierzchołek 0: 1
//Wierzchołek 1: 2
//Wierzchołek 2: 4
//Wierzchołek 3: 4 2
//Wierzchołek 4: 1 0 3
void graphTest()
{
	ifstream file("graphTest.txt");
	int a, b, c, d;
	file >> a >> b;
	Graph<Empty, Empty> g(a);
	REP(b)
	{
		file >> c >> d;
		g.addDirectedEdge(c, d);
	}
	g.write();
}

//0 - distance 0 ancestor -1
//1 - distance 1 ancestor 0
//2 - distance 1 ancestor 0
//3 - distance 2 ancestor 1
//4 - distance 2 ancestor 1
//5 - distance 2 ancestor 2
//6 - distance 2 ancestor 2
void BFSTest()
{
	int a, b, c, d, s;
	ifstream file("BFS.in");
	file >> a >> b >> s;
	Graph<VertexBFS, Empty> g(a);
	REP(b)
	{
		file >> c >> d;
		g.addDirectedEdge(c, d);
	}
	g.BFS(s);
	REP(a)
	cout << i << " - distance " << g.g[i].distance << " ancestor " << g.g[i].ancestor << endl;
}

//0 - pre 0 post 13 ancestor -1
//1 - pre 1 post 6 ancestor 0
//2 - pre 7 post 12 ancestor 0
//3 - pre 2 post 3 ancestor 1
//4 - pre 4 post 5 ancestor 1
//5 - pre 8 post 9 ancestor 2
//6 - pre 10 post 11 ancestor 2
void DFSTest()
{
	int a, b, c, d, s;
	ifstream file("BFS.in");
	file >> a >> b >> s;
	Graph<VertexDFS, Empty> g(a);
	REP(b)
	{
		file >> c >> d;
		g.addDirectedEdge(c, d);
	}
	g.DFS(s);
	REP(a)
	cout << i << " - pre " << g.g[i].pre << " post " << g.g[i].post << " ancestor " << g.g[i].ancestor << endl;
}

//0 - distance 0 ancestor -1
//1 - distance 10 ancestor 0
//2 - distance 15 ancestor 0
//3 - distance 20 ancestor 2
//4 - distance 30 ancestor 3
//5 - distance 32 ancestor 4
void DijkstraTest()
{
	int n, m, s, b, e;
	EdgeDijkstra ed;
	ifstream file("Dijkstra.in");
	file >> n >> m >> s;
	Graph<VertexDijkstra, EdgeDijkstra> g(n);
	REP(m)
	{
		file >> b >> e >> ed.weight;
		g.addUndirectedEdge(b, e, ed);
	}
	g.Dijkstra(s);
	REP(n)
	cout << i << " - distance " << g.g[i].distance << " ancestor " << g.g[i].ancestor << endl;
}

//0 2 3 4 5 3 6 2 1 0
//3 4 5 3 2 0 1 2 6
void EulerTest()
{
	VI res;
	int n, m, b, e;
	ifstream file("eulerTest.txt");
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

//0
//1
void AcyclicTest()
{
	int a, b, c, d;
	ifstream file("acyclicTest.txt");
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

//Kolejność topologiczna wierzchołków: 0 1 3 4 2 5
//Wierzchołek 0 ma pozycję 0 w porządku topologicznym.
//Wierzchołek 1 ma pozycję 1 w porządku topologicznym.
//Wierzchołek 2 ma pozycję 4 w porządku topologicznym.
//Wierzchołek 3 ma pozycję 2 w porządku topologicznym.
//Wierzchołek 4 ma pozycję 3 w porządku topologicznym.
//Wierzchołek 5 ma pozycję 5 w porządku topologicznym.
void TopoTest()
{
	ifstream file("topoTest.txt");
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

//Wierzchołek 0 silnie spójna składowa nr 0
//Wierzchołek 1 silnie spójna składowa nr 0
//Wierzchołek 2 silnie spójna składowa nr 2
//Wierzchołek 3 silnie spójna składowa nr 2
//Wierzchołek 4 silnie spójna składowa nr 2
//Wierzchołek 5 silnie spójna składowa nr 1
//Wierzchołek 6 silnie spójna składowa nr 3
//Wierzchołek 7 silnie spójna składowa nr 4
//Graf silnie spójnych składowych:
//Wierzchołek 0: 2 3 4
//Wierzchołek 1: 2
//Wierzchołek 2:
//Wierzchołek 3: 4
//Wierzchołek 4:
void SccTest()
{
	ifstream file("sccTest.txt");
	int a, b, c, d;
	file >> a >> b;
	Graph<VertexScc, Empty> g(a);
	REP(b)
	{
		file >> c >> d;
		g.addDirectedEdge(c, d);
	}
	Graph<VertexScc, Empty> scc = g.scc();
	REP(a)
	cout << "Wierzchołek " << i << " silnie spójna składowa nr " << g.g[i].t << endl;
	cout << "Graf silnie spójnych składowych:" << endl;
	scc.write();
}

//Waga - 61
//Krawędzie:  (0,1) (1,2) (0,3) (1,5) (4,5)
void MSTTest()
{
	int n, m, b, e;
	ifstream file("MST.in");
	file >> n >> m;
	MSTEdge l;
	Graph<Empty, MSTEdge> g(n);
	REP(m)
	{
		file >> b >> e >> l.weight;
		g.addUndirectedEdge(b, e ,l);
	}
	cout << "Waga - " << g.MinSpanTree() << endl;
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

//0 - distance 0 ancestor -1
//1 - distance 3 ancestor 0
//2 - distance -2 ancestor 1
//3 - distance 5 ancestor 1
//4 - distance 7 ancestor 3
void BellmanFordTest()
{
	int n, m, s, b, e;
	EdgeBellmanFord ed;
	ifstream file("BellmanFord.in");
	file >> n >> m >> s;
	Graph<VertexBellmanFord, EdgeBellmanFord> g(n);
	REP(m)
	{
		file >> b >> e >> ed.weight;
		g.addDirectedEdge(b, e, ed);
	}
	g.BellmanFord(s);
	REP(n)
		cout << i << " - distance " << g.g[i].distance << " ancestor " << g.g[i].ancestor << endl;
}

int main()
{
	graphTest();
	cout << endl;
	BFSTest();
	cout << endl;
	DFSTest();
	cout << endl;
	DijkstraTest();
	cout << endl;
	SccTest();
	cout << endl;
	TopoTest();
	cout << endl;
	AcyclicTest();
	cout << endl;
	EulerTest();
	cout << endl;
	MSTTest();
	cout << endl;
	BellmanFordTest();
}
