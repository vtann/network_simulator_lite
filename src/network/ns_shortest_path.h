#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <limits> 
#include <set>
#include <utility> 
#include <algorithm>
#include <iterator>
 
#ifndef __NS_NAMESPACE_H__
#define __NS_NAMESPACE_H__
#include "../ns_namespace.h"
#endif // __NS_NAMESPACE_H__

class shortest_path 
{
    public:
    shortest_path(int vertices);

    int add_edge(int src_vertex, int dst_vertex, double cost);

    void dijikstra_compute_paths(int source,
                                 std::vector<double> &min_distance,
                                 std::vector<int> &previous);
    void dijkstra_get_shortest_path_to(std::vector<int> &path, int vertex, const std::vector<int> &previous);
    void form_routing_vertices(int vertex);
     
    private:
    int vertices;
    std::vector<int> routing_vertices;
    std::vector<std::pair <int, double> > *adjacency_list;
}; 
