#include <iostream>
#include <string>
#include "ns_gui.h"

ns_gui::ns_gui(){
    // Create window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;

    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    window_width = videoMode.width;
    window_height = videoMode.height;
    window = new sf::RenderWindow(sf::VideoMode(window_width, window_height), "nsLite - Delay Analyzer Beta", sf::Style::Default, settings);
    
    font.loadFromFile("gui/arial.ttf");
    
    transform_x = window_width / 2.0;
    transform_y = window_height / 2.0;
    zoom = 1.0;
}
    
ns_gui::~ns_gui(){
    window->close();
}

void ns_gui::generate_layout(router_network* rn){
    to_draw_nodeList.clear();
    
    double x_max = -DBL_MAX;
    double y_max = -DBL_MAX;
    double x_sum = 0.0;
    double y_sum = 0.0;
    int count = 0;
    
    for (auto& node : rn->get_all_routers()) {
        double x = node->get_xAxis();
        double y = node->get_yAxis();
        x_sum += x;
        y_sum += y;

        if (std::abs(x) > x_max) x_max = x;
        if (std::abs(y) > y_max) y_max = y;

        count++;
    }
    
    // Mid point
    double center_x = x_sum / count;
    double center_y = y_sum / count;
    
    // Apply scaling so that original aspect ratio is retained
    // and everything fits on the screen
    double x_ratio = 0.75 * (window_width) / (x_max != 0.0 ? x_max : window_width);
    double y_ratio = 0.75 * (window_height) / (y_max != 0.0 ? y_max : window_height);
    double scale_ratio;
    
    if (x_ratio < y_ratio) scale_ratio = x_ratio;
    else scale_ratio = y_ratio;
    
    for (auto& node : rn->get_all_routers()) {
        double x = scale_ratio * (node->get_xAxis() - center_x);
        double y = scale_ratio * (node->get_yAxis() - center_y);
        
        to_draw_nodeList.insert({node, {x, y}});
        router_list.push_back(node);
    }
    
    for (auto& link : rn->get_all_links()) {
        to_draw_linkList.push_back(link);
    }
    
}
    
void ns_gui::create_gui(){
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            
            if (event.type == sf::Event::KeyPressed)
                switch (event.key.code) {
                    case sf::Keyboard::Q:
                    case sf::Keyboard::Escape:
                        window->close();
                        
                    default: //to hide warning: enumeration value '<unused keys>' not handled in switch [-Wswitch]
                        break;
                }
            
        }

        window->clear(sf::Color::Black);
    
        draw_nodes();
        draw_links();
        draw_textBoxes();
        window->display();
    }
}