#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <cfloat>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include "../ns_namespace.h"

#include "../network/ns_network.h"

using namespace ns_ns;

class ns_gui{
public:
    ns_gui();
    
    ~ns_gui();
    
    void generate_layout(router_network* rn);
    
    void draw_nodes();
    
    void draw_textBoxes();
    
    void draw_links();

    bool window_exists();
    
    void create_gui();
    
protected:
    sf::RenderWindow* window;
    sf::Font font;
    sf::Text text;
    sf::Color default_nodeColor;
    sf::Color default_fillColor;
    
    unsigned int font_size;
    unsigned int node_radius;
    unsigned int window_width;
    unsigned int window_height;
    double transform_x;
    double transform_y;
    double zoom;
    
    struct ns_gui_axis {
        double x;
        double y;
    };
    
    std::map<router*,ns_gui_axis> to_draw_nodeList;
    std::vector<router*> router_list;
    std::vector<router_link*> to_draw_linkList;
    
};
