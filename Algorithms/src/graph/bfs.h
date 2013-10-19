/**
 * bfs.h
 * Implements Breadth-First search algorithm. Traverses the graph and calculates distance from given
 * source for each vertex as well as its ancestor on the shortest path to the source. This informations are
 * stored in fields distance and ancestor.
 * During any point, unvisited vertex's siblings are processed before its children.
 * complexity O(V + E)
 *
 * @autor Mateusz Śmiech
 * @version 0.0.0
 */

#include "graph.h"

template<class Vertex, class Edge> void Graph<Vertex, Edge>::BFS(int source)
{
	FOREACH(it, g)
		it->ancestor = it->distance = -1; //Set default distance and ancestor. If at any point vertex.distance = -1,
	//it means that the vertex hasn't been yet processed.
	g[source].distance = 0;
	queue<int> q;  //FIFO queue containing vertex indices, not pointers.
	q.push(source);
	while (!q.empty())
	{
		source = q.front(); //Source is actually processed vertex.
		q.pop();
		FOREACH(it, g[source]) //Iterate edges going out of source
		{
			if (g[it->destination].distance == -1) //Vertex hasn't been visited yet.
			{
				g[it->destination].distance = g[source].distance + 1; //Update distance, graph isn't weighed.
				g[it->destination].ancestor = source; //Update ancestor.
				q.push(it->destination); //Add vertex to the queue.
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
