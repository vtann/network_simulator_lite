#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <limits> 
#include <set>
#include <utility> 
#include <algorithm>
#include <iterator>
 
#include "../ns_namespace.h"

#ifndef __NS_SHORTEST_PATH_H__
#define __NS_SHORTEST_PATH_H__ 

class shortest_path 
{
    public:
    shortest_path(int vertices);

    int add_edge(ns_ns::graph_type graph, int src_vertex, int dst_vertex, double cost);

    bool check_remove_dup_edge(ns_ns::graph_type graph, int src_vertex, int dst_vertex, double cost);
    
    void dijikstra_compute_paths(int source,
                                 std::vector<double> &min_distance,
                                 std::vector<int> &previous);
    
    void dijkstra_get_shortest_path_to(std::vector<int> &path, int vertex, const std::vector<int> &previous);
    
    void form_routing_vertices(int vertex);

    void print_edges();
    
    void sort_vertex_queue(std::vector<std::pair<std::pair<int, int>, double> > &vertex);
     
    private:
    int vertices;
    std::vector<int> routing_vertices;
    std::vector<std::pair <int, double> > *adjacency_list;
}; 

bool compare(const std::pair<std::pair<int, int>, double> &i, const std::pair<std::pair<int, int>, double> &j);

#endif // __NS_SHORTEST_PATH_H__
