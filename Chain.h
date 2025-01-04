//
// Created by andre on 31/12/24.
//

#ifndef PROCEDURALANIMATION_CHAIN_H
#define PROCEDURALANIMATION_CHAIN_H
#define PI 3.141592653589793

#include <vector>
#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

class Chain {
public:
    Chain(const std::vector<float>& link_sizes);
    void draw(sf::RenderWindow& window);
    void move();
    std::vector<std::array<float, 3>> links; // [x, y, radius]

private:

    float headDirection;
    float neckAng;
    
    void reset();

    void front();
    void left();
    void right();

    const float frontStep = 0.1;
    const float angleStep = 0.002;
    const float maxAngle = PI/2;
    const float EPS = angleStep / 5;

    void applyConstraints();
};

#endif //PROCEDURALANIMATION_CHAIN_H
