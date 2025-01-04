#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include "Chain.h"
#include "Legs.h"
#include <SFML/Graphics.hpp>

int main() {
    std::vector<float> sizes = {20, 15, 20, 25, 25, 25, 25, 20, 20, 17, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 10, 10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1};
    
    auto C = Chain(sizes);
    auto L1 = Legs(30, 30, true);
    auto L2 = Legs(30, 30, false);
    auto L3 = Legs(30, 30, true);
    auto L4 = Legs(30, 30, false);

    float x, y, angle;

    sf::RenderWindow window(sf::VideoMode({1100, 600}), "SFML works!");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        angle = atan2(C.links[2][1] - C.links[3][1], C.links[2][0] - C.links[3][0]) - 3.1415/2;
        float a2 = angle + 3.1415/2;
        float o = 0;
        float o2 = 0;
        x = C.links[3][0] + C.links[3][2]*cos(angle);
        y = C.links[3][1] + C.links[3][2]*sin(angle);
        L1.update(x, y, x+40*cos(angle)  +o*cos(a2), y+40*sin(angle)  +o*sin(a2));     
        x = C.links[3][0] - C.links[3][2]*cos(angle);
        y = C.links[3][1] - C.links[3][2]*sin(angle);
        L2.update(x, y, x-40*cos(angle) -o2*cos(a2), y-40*sin(angle) -o2*sin(a2));     
        
        angle = atan2(C.links[4][1] - C.links[5][1], C.links[4][0] - C.links[5][0]) - 3.1415/2;
        x = C.links[5][0] + C.links[5][2]*cos(angle);
        y = C.links[5][1] + C.links[5][2]*sin(angle);
        L3.update(x, y, x+40*cos(angle)  -o/3*cos(a2), y+40*sin(angle)  -o/3*sin(a2));     
        x = C.links[5][0] - C.links[5][2]*cos(angle);
        y = C.links[5][1] - C.links[5][2]*sin(angle);
        L4.update(x, y, x-40*cos(angle)  +o2*cos(a2), y-40*sin(angle)  +o2*sin(a2));     
        
        C.move();
        window.clear();
        C.draw(window);
        L1.draw(window);
        L2.draw(window);
        L3.draw(window);
        L4.draw(window);
        window.display();
    }

    return 0;
}
