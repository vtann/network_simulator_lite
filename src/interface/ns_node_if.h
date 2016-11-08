#include <iostream>

class node_interface
{
    public:
    node_interface(int if_id) 
    {
        interface_id = if_id; 
    };
    
    ~node_interface() { };

    int get_interface_id() const
    {
        return interface_id;
    }
    
    int set_interface_id(int if_id)
    {
        interface_id = if_id;   
    }    

    private:
    int interface_id;
}; 
