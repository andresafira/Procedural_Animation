//
// Created by andre on 01/01/25.
//

#ifndef PROCEDURALANIMATION_LEGS_H
#define PROCEDURALANIMATION_LEGS_H
#define PI 3.141592653589793

#include <vector>
#include <iostream>
#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

class Legs {
public:
    Legs(float L1, float L2, bool anklePos);
    void draw(sf::RenderWindow& window);
    void update(float linkX, float linkY, float refX, float refY);
private:
    float baseX, baseY;
    float L1, L2;
    float q1, q2;
    float pointX, pointY;

    bool stepping;
    float stepBaseX, stepBaseY;
    float stepT;
    
    bool anklePos;

    void inverseKinematics(float x, float y);

    const float dt = 0.002;
};

#endif //PROCEDURALANIMATION_LEGS_H
