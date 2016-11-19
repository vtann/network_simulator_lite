#ifndef __NS_SHORTEST_PATH_H__
#define __NS_SHORTEST_PATH_H__ 
#include "ns_shortest_path.h"
#endif // __NS_SHORTEST_PATH_H__

using namespace ns_ns;

shortest_path::shortest_path(int v)
{
    vertices = v;
    adjacency_list = new std::vector<std::pair <int, double> > [vertices];
} 

void shortest_path::form_routing_vertices(int vertex)
{
    for (unsigned int index = 0; index < routing_vertices.size(); index++)
    {
        if (routing_vertices[index] == vertex)
        {
            return;
        }  
    }
    routing_vertices.push_back(vertex);
}

int shortest_path::add_edge(ns_ns::graph_type graph, int src_vertex, int dst_vertex, double cost)
{
    form_routing_vertices(src_vertex);
    form_routing_vertices(dst_vertex);
    if (DIRECTED_GRAPH == graph)
    { 
        adjacency_list[src_vertex].push_back(std::make_pair(dst_vertex, cost));
    }
    else
    {
        adjacency_list[src_vertex].push_back(std::make_pair(dst_vertex, cost));
        adjacency_list[dst_vertex].push_back(std::make_pair(src_vertex, cost));
    }  
    return 0;       
}

bool compare(const std::pair<std::pair<int, int>, double> &i, const std::pair<std::pair<int, int>, double> &j)
{
    return i.second < j.second;
}

void shortest_path::sort_vertex_queue(std::vector<std::pair<std::pair<int, int>, double> > &vertex)
{
    std::sort(vertex.begin(), vertex.end(), compare); 
}

void shortest_path::dijikstra_compute_paths(int source,
                                            std::vector<double> &min_distance,
                                            std::vector<int> &previous)
{
    min_distance.clear();
    min_distance.resize(vertices, std::numeric_limits<double>::infinity());
    //min_distance.resize(vertices, 1000);
    min_distance.resize(vertices, 0);
    previous.clear();
    previous.resize(vertices, -1);
    std::vector<int> evaluated_nodes; 
    std::vector<int> unreachable_nodes; 
    std::vector<std::pair<std::pair<int, int>, double> > vertex_queue;

    evaluated_nodes.push_back(source);
   
    //std::cout << "Number of nodes: " << vertices << std::endl;  
    for (unsigned int index = 0; index < routing_vertices.size(); index++)
    {
        if (routing_vertices[index] != source)
        {
            unreachable_nodes.push_back(routing_vertices[index]);
        }
    }
   
    for (std::vector<std::pair <int, double> >::const_iterator neighbor_iter = adjacency_list[source].begin();
         neighbor_iter != adjacency_list[source].end();
         neighbor_iter++)
    {
        vertex_queue.push_back(std::make_pair(std::make_pair(source, (*neighbor_iter).first), (*neighbor_iter).second));  
    }
    
    // Sort the edges  
    sort_vertex_queue(vertex_queue); 

    while (!vertex_queue.empty()) 
    {
        std::pair<int, int> src_dst = vertex_queue.begin()->first;
        int src = src_dst.first;  
        int dst = src_dst.second;  
        double dist = vertex_queue.begin()->second;
       
        //std::cout << "-----------------------" << std::endl;
        for (std::vector<std::pair <std::pair<int, int>, double> >::const_iterator index = vertex_queue.begin(); index != vertex_queue.end(); index++)
        {  
            //std::pair<int, int> v = (*index).first;
            //std::cout << "Source Vertex: " << v.first;
            //std::cout << " Dest Vertex: " << v.second;
            //std::cout << " Vertex distance: " <<(*index).second << std::endl;
        }

        vertex_queue.erase(vertex_queue.begin());
        
        if (std::find(evaluated_nodes.begin(), evaluated_nodes.end(), dst) != evaluated_nodes.end())
        {
            continue;
        }
        else
        {
            unreachable_nodes.erase(std::remove(unreachable_nodes.begin(), unreachable_nodes.end(), dst), unreachable_nodes.end()); 
            evaluated_nodes.push_back(dst);
            
            //std::cout << "Min distance: " << min_distance[dst] << std::endl;  
	    if (dist < min_distance[dst]) 
            {
	        min_distance[dst] = dist + min_distance[src];
	        previous[dst] = src;
                //std::cout << "Previous distance: " << previous[dst] << std::endl; 
                for (std::vector<std::pair <int, double> >::const_iterator neighbor_iter = adjacency_list[dst].begin();
                     neighbor_iter != adjacency_list[dst].end();
                     neighbor_iter++)
                {
                    //std::cout << "Source Vertex: " << dst;
                    //std::cout << " Dest Vertex: " << (*neighbor_iter).first;
                    //std::cout << " Vertex distance: " <<(*neighbor_iter).second;
                    //std::cout << " Total distance: " << dist << std::endl;
                    vertex_queue.push_back(std::make_pair(std::make_pair(dst, (*neighbor_iter).first), ((*neighbor_iter).second + dist)));  
                }
                sort_vertex_queue(vertex_queue);
	    }
        }
        //std::cout << "-----------------------" << std::endl;
    }
}
 
void shortest_path::dijkstra_get_shortest_path_to(std::vector<int>&path, int vertex, const std::vector<int> &previous)
{
    while (vertex != -1) 
    {
        //std::cout << "Vertex1: " << vertex << std::endl;
        path.push_back(vertex);
        vertex = previous[vertex];
    }
}
 
