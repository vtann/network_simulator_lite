#ifndef __NS_SHORTEST_PATH_H__
#define __NS_SHORTEST_PATH_H__ 
#include "ns_shortest_path.h"
#endif // __NS_SHORTEST_PATH_H__

shortest_path::shortest_path(int v)
{
    vertices = v;
    adjacency_list = new std::vector<std::pair <int, double> > [vertices];
} 

int shortest_path::add_edge(int src_vertex, int dst_vertex, double cost)
{
    adjacency_list[src_vertex].push_back(std::make_pair(dst_vertex, cost));
    return 0;       
}

void shortest_path::dijikstra_compute_paths(int source,
                                            std::vector<double> &min_distance,
                                            std::vector<int> &previous)
{
    int n = adjacency_list->size();
    min_distance.clear();
    min_distance.resize(n, std::numeric_limits<double>::infinity());
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    std::set<std::pair<double, int> > vertex_queue;
    vertex_queue.insert(std::make_pair(min_distance[source], source));
 
    while (!vertex_queue.empty()) 
    {
        double dist = vertex_queue.begin()->first;
        int u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());
 
        // Visit each edge exiting u
        for (std::vector<std::pair <int, double> >::const_iterator neighbor_iter = adjacency_list[u].begin();
             neighbor_iter != adjacency_list[u].end();
             neighbor_iter++)
        {
            int v = (*neighbor_iter).first;
            double weight = (*neighbor_iter).second;
            double distance_through_u = dist + weight;
	    if (distance_through_u < min_distance[v]) 
            {
	        vertex_queue.erase(std::make_pair(min_distance[v], v));
	        min_distance[v] = distance_through_u;
	        previous[v] = u;
	        vertex_queue.insert(std::make_pair(min_distance[v], v));
	    }
 
        }
    }
}
 
std::list<int> shortest_path::dijkstra_get_shortest_path_to(int vertex, const std::vector<int> &previous)
{
    std::list<int> path;
    for ( ; vertex != -1; vertex = previous[vertex])
    {
        path.push_front(vertex);
    }
    return path;
}
 
