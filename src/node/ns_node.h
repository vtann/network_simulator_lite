#include <iostream>

class node
{
    public:
    node(int id) 
    {
        node_id = id; 
    }
    
    ~node() { };
 
    int get_node_id() const 
    {
        return node_id; 
    }

    private:
    int node_id; 
};

