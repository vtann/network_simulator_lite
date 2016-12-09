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


    font_size = 20;
    text.setFont(font);
    text.setCharacterSize(font_size); // in pixels
    text.setStyle(sf::Text::Regular);
    
    default_nodeColor = sf::Color(0,0,255);
    default_fillColor = sf::Color(47,79,79);
    
    node_radius = 25;
    
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

void ns_gui::draw_nodes(){
    sf::CircleShape node_shape(node_radius);
    
    for (auto& node : to_draw_nodeList) {
        const int& x = node.second.x * zoom + transform_x;
        const int& y = node.second.y * zoom + transform_y;
        
        sf::Color outline_color = default_nodeColor;
        sf::Color fill_color = default_fillColor;
        int thickness = 2;
        
        node_shape.setOutlineColor(outline_color);
        node_shape.setOutlineThickness(thickness);
        node_shape.setFillColor(fill_color);
        node_shape.setOrigin(node_radius, node_radius);
        node_shape.setPosition(x, y);
        window->draw(node_shape);
        
        text.setString(std::to_string((node.first->get_node_id())));
        text.setPosition(x - text.getLocalBounds().width / 2, y - font_size / 2);
        text.setCharacterSize(18);
        text.setColor(sf::Color::White);
        window->draw(text);
    }
}

void ns_gui::draw_links(){
    for (auto& link : to_draw_linkList) {
        
        //int source_id = link->get_src_router()->get_node_id();
        //int source_if_id = link->get_src_if()->get_interface_id();
        //int dest_id = link->get_dst_router()->get_node_id();
        //int dest_if_id = link->get_dst_if()->get_interface_id();
        
        auto link_start = to_draw_nodeList.at(link->get_src_router());
        auto link_end = to_draw_nodeList.at(link->get_dst_router());
        
        //sf::Color link_color = sf::Color(128,128,128,128);
        sf::Color link_color = sf::Color(192, 192, 192);
        
        // Line between nodes
        double x1 = link_start.x * zoom + transform_x;
        double y1 = link_start.y * zoom + transform_y;
        double x2 = link_end.x * zoom + transform_x;
        double y2 = link_end.y * zoom + transform_y;
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(x1, y1), link_color),
            sf::Vertex(sf::Vector2f(x2, y2), link_color)
        };
        

        window->draw(line, 2, sf::Lines);
        
        float angle_src2dst = atan2(((y2 - font_size / 2) - (y1 - font_size / 2)), ((x2 - text.getLocalBounds().width / 2) - (x1 - text.getLocalBounds().width / 2)));
        
        double xx1 = (x1 - text.getLocalBounds().width / 2)+cos(angle_src2dst) * 80;
        double yy1 = (y1 - font_size / 2)+sin(angle_src2dst) * 80;
        text.setColor(sf::Color(255,255,51));
        text.setCharacterSize(11);
        
        text.setString(link->get_src_if()->get_network_address());
        text.setPosition(xx1, yy1);
        window->draw(text);
        
        float angle_dst2src = atan2(((y1 - font_size / 2)-(y2 - font_size / 2)), ((x1 - text.getLocalBounds().width / 2)-(x2 - text.getLocalBounds().width / 2)));
        
        double xx2 = (x2 - text.getLocalBounds().width / 2)+cos(angle_dst2src) * 80;
        double yy2 = (y2 - font_size / 2)+sin(angle_dst2src) * 80;
        
        text.setString(link->get_dst_if()->get_network_address());
        text.setPosition(xx2, yy2);
        window->draw(text);
    }
}

void ns_gui::draw_textBoxes(){
    
    double margin = font_size / 2;
    sf::Color box_color = sf::Color(50,205,50);
    
    std::stringstream ss;
    //add information to stringstream for display
    
    for (auto node : router_list ) {
        std::stringstream ss;
        ss<<"Helloo"<<std::endl<<"World";
        
        text.setString(ss.str());
        text.setColor(sf::Color(220,20,60));
        sf::FloatRect text_bounds = text.getLocalBounds();
        
        int x = to_draw_nodeList.at(node).x * zoom + transform_x - text_bounds.width / 2;
        int y = to_draw_nodeList.at(node).y * zoom + transform_y - text_bounds.height - margin * 5;
        
        text.setPosition(x, y);
        
        // Box
        sf::RectangleShape text_infoBox(sf::Vector2f(text_bounds.width + margin * 2, text_bounds.height + margin * 3));
        
        text_infoBox.setFillColor(sf::Color(0, 0, 0, 128));
        text_infoBox.setOutlineColor(box_color);
        text_infoBox.setOutlineThickness(1);
        text_infoBox.setPosition(x - margin, y - margin);
        
        // Pointing triangle
        sf::ConvexShape pointer(3);
        
        sf::FloatRect text_infoBox_bounds = text_infoBox.getLocalBounds();
        pointer.setPoint(0, sf::Vector2f(-5, 0));
        pointer.setPoint(1, sf::Vector2f(5, 0));
        pointer.setPoint(2, sf::Vector2f(0, 5));
        pointer.setPosition(x - margin + text_infoBox_bounds.width / 2, y - margin + text_infoBox_bounds.height);
        
        pointer.setFillColor(box_color);
        pointer.setOutlineColor(box_color);
        pointer.setOutlineThickness(1);

        window->draw(pointer);
        window->draw(text_infoBox);
        window->draw(text);
    }
}

void ns_gui::create_gui(){
    while (!window_exists()) {
        // wait
    }

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
        draw_textBoxes();
        draw_links();
        window->display();
    }
}