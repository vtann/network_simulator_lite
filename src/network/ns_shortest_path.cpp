#include "ns_shortest_path.h"

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

bool shortest_path::check_remove_dup_edge(ns_ns::graph_type graph, int src_vertex, int dst_vertex, double cost)
{
    bool result = true;
    bool is_new_link_dup = false;
    std::vector< std::pair<int, double> >::iterator index;
    
    for (index = adjacency_list[src_vertex].begin(); index != adjacency_list[src_vertex].end(); index++)
    {
        if (dst_vertex == index->first)
        {
            if (cost < index->second)
            {
                result = false; 
                break;
            }
            else
            {
                is_new_link_dup = true;
            }   
        }  
    }
    if (false == result)
    {
        adjacency_list[src_vertex].erase(index);
    }
    
    if (UNDIRECTED_GRAPH == graph)
    {
        result = true;
        for (index = adjacency_list[dst_vertex].begin(); index != adjacency_list[dst_vertex].end(); index++)
        {
            if (src_vertex == index->first)
            {
                if (cost < index->second)
                {
                    result = false; 
                    break;
                }
                else 
                {
                    is_new_link_dup = true;
                }   
            }  
        }
        if (false == result)
        {
            adjacency_list[dst_vertex].erase(index);
        }
    }
    else
    { 
        return is_new_link_dup;
    } 
    return is_new_link_dup;
}

void shortest_path::print_edges()
{
    std::vector< std::pair<int, double> >::iterator index2;
    for (int index = 0; index < vertices; index++)
    {
        for (index2 = adjacency_list[index].begin(); index2 != adjacency_list[index].end(); index2++)
        {
            std::cout << "Src vertex: " << index 
                      << " Dst vertex: " <<  index2->first  
                      << " Cost: " << index2->second << std::endl; 
        }
    }
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
    return OK;       
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
    min_distance.resize(vertices, 0);
    previous.clear();
    previous.resize(vertices, -1);
    std::vector<int> evaluated_nodes; 
    std::vector<int> unreachable_nodes; 
    std::vector<std::pair<std::pair<int, int>, double> > vertex_queue;

    evaluated_nodes.push_back(source);
    min_distance[source] = 0;  
 
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
       
        /*std::cout << "-----------------------" << std::endl;
        for (std::vector<std::pair <std::pair<int, int>, double> >::const_iterator index = vertex_queue.begin(); index != vertex_queue.end(); index++)
        {  
            std::pair<int, int> v = (*index).first;
            std::cout << "Source Vertex: " << v.first;
            std::cout << " Dest Vertex: " << v.second;
            std::cout << " Vertex distance: " <<(*index).second << std::endl;
        }
        std::cout << "-----------------------" << std::endl;*/

        vertex_queue.erase(vertex_queue.begin());
        
        if (std::find(evaluated_nodes.begin(), evaluated_nodes.end(), dst) != evaluated_nodes.end())
        {
            continue;
        }
        else
        {
            unreachable_nodes.erase(std::remove(unreachable_nodes.begin(), unreachable_nodes.end(), dst), unreachable_nodes.end()); 
            evaluated_nodes.push_back(dst);
            
	    if (dist < min_distance[dst]) 
            {
                //std::cout << "***********************" << std::endl;
	        min_distance[dst] = dist;
                //std::cout << "Min distance[" << src << "]: " << min_distance[src] << std::endl;  
                //std::cout << "Distance: " << dist << std::endl;  
                //std::cout << "Min distance[" << dst << "]: " << min_distance[dst] << std::endl;  
	        previous[dst] = src;
                //std::cout << "Previous distance: " << previous[dst] << std::endl; 
                for (std::vector<std::pair <int, double> >::const_iterator neighbor_iter = adjacency_list[dst].begin();
                     neighbor_iter != adjacency_list[dst].end();
                     neighbor_iter++)
                {
                    vertex_queue.push_back(std::make_pair(std::make_pair(dst, (*neighbor_iter).first), ((*neighbor_iter).second + min_distance[dst])));  
                }
                sort_vertex_queue(vertex_queue);
                //std::cout << "***********************" << std::endl;
	    }
        }
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
 
void shortest_path::log_dijkstra_paths(int source, const std::vector<int> &previous, std::ostream& sp_file)
{
    std::vector<int> path;  
    sp_file << "=====================================================================================================================" << std::endl;

    for (auto index = 0; index < vertices; index++)
    {
        dijkstra_get_shortest_path_to(path, index, previous);
        
          
       sp_file << "Path from Node: " << source
               << " to Node: " << index << std::endl; 
        for (int index2 = (int) (path.size() - 1); index2 != -1; index2--)
        { 
            sp_file << path[index2] 
                    << " "; 
        }
        sp_file << std::endl;
        path.clear();
    }
    sp_file << "=====================================================================================================================" << std::endl;
}
