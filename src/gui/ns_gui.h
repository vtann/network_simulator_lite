#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <cfloat>
#include <memory>

// dependency/library for sfml
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include "../ns_namespace.h"
#include "../sim/ns_delay_calculator.h"
#include "../network/ns_network.h"

using namespace ns_ns;

/**
 * Handles the graphical representation of the network simulation and results
 */
class ns_gui {
public:
    ns_gui();

    ~ns_gui();

    /**
     * Generate basic layout and apply scaling for GUI
     */
    void generate_layout(std::shared_ptr<router_network> rn);

    /**
     * Render node
     */
    void draw_nodes();

    /**
     * Render text boxes to display results
     */
    void draw_textBoxes();

    /**
     * Render links between nodes and interface ip addresses
     */
    void draw_links();

    /**
     * Return true if rendering window is created, else false
     */
    bool window_exists();

    /**
     * Calls rendering functions
     */
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

    // Contain updated scaled-out axis positions
    struct ns_gui_axis {
        double x;
        double y;
    };

    std::map<std::shared_ptr<router>, ns_gui_axis> to_draw_nodeList;
    std::vector<std::shared_ptr<router> > router_list;
    std::vector<std::shared_ptr<router_link> > to_draw_linkList;

};
