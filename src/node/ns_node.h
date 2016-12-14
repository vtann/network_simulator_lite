#include <iostream>

#ifndef __NS_NODE_H__
#define __NS_NODE_H__

/*! 
 *  \brief     Class to create node e.g) router, switch
 *  \details   This class creates a node used in the network simulation.
 *  \author    Karthika Krishnamurthy.
 *  \version   1.0
 *  \date      2016
 *  \pre       N/A.
 *  \bug       Not all memory is freed when deleting an object of this class.
 *  \warning   Improper use can crash your application
 *  \copyright GNU Public License.
 */
class node
{
    public:
   
    // Constructor to create node 
    node(int id) 
    {
        node_id = id; 
    }  
   
    // Destructor to free memory  
    ~node() { };

    // Funcion to get node id 
    int get_node_id() const 
    {
        return node_id; 
    }

    private:
    
    // Node id must be unique
    int node_id; 
};

#endif //  __NS_NODE_H__
