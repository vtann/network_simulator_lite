#include <iostream>

#ifndef __NS_NODE_H__
#define __NS_NODE_H__

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

#endif //  __NS_NODE_H__
