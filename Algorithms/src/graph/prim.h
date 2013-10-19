/**
 * prim.h
 * Implementation of Prim's algorithm for finding Minimal Spanning Tree.
 * It starts with a spanning tree containing only one vertex and keeps on adding vertices which aren't already
 * in the tree. They're added in order of increasing distances from the tree.
 * complexity O((V + E) log V)
 * Using Fibonacci Heaps will reduce asymptotic complexity to O(E + V log V) but real execution time may be
 * longer for normal graph size.
 * Each edge contains span field indicating whether it belongs to the computed MST.
 * Function returns weight of the MST.
 *
 * @author Mateusz Śmiech
 * @version 0.0.0
 */

#include "graph.h"

template<class Vertex, class Edge> int Graph<Vertex, Edge>::Prim()
{
	int r = 0, d[SIZE(g)]; //For each vertex not belonging to the MST it stores length of the shortest edge connecting it with any vertex already in the tree.
	bool added[SIZE(g)]; //added[i] = true <=> vertex i has already been added to the MST
	REP(SIZE(g)) //Initialize distance; no vertex have been added to the MST.
	{
		d[i] = INF;
		added[i] = 0;
	}
	set<PII> s; //Priority queue containing vertices reachable from the MST in order of increasing edge weights.
	//First element of a pair contains distance (set sorts by it), second - vertex number.
	s.insert(MP(d[0] = 0, 0));
	while (!s.empty())
	{
		int v = (s.begin())->ND; //Vertex which addition is the cheapest.
		s.erase(s.begin()); //Remove it from the queue.
		bool t = 0;
		added[v] = 1; //Mark it as added.
		r += d[v];  //Update tree weight.
		FOREACH(it, g[v]) //Iterate every edge going out of v.
		{
			it->span = 0;
			if (!t && added[it->destination] && it->weight == d[v]) //Edge has already been added to the MST.
				t = it->span = g[it->destination][it->rev].span = 1;
			else if (!added[it->destination] && d[it->destination] > it->weight) //Update distances of other vertices.
			{
				s.erase(MP(d[it->destination], it->destination)); //Unfortunately we can't update a vertex that already is in the
				//set, so we have to remove it and add again with new key.
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
