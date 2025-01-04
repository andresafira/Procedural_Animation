//
// Created by andre on 01/01/25.
//

#include "Legs.h"

float dist2(float x, float y) {
    return x*x + y*y;
}

float dist(float x, float y) {
    return sqrt(dist2(x, y));
}

Legs::Legs(float L1, float L2, bool anklePos): L1(L1), L2(L2), anklePos(anklePos) {
    this->q1 = 0;
    this->q2 = 0;
    this->baseX = 0;
    this->baseY = 0;
    this->pointX = 0;
    this->pointY = 0;
    this->stepping = false;
    this->stepBaseX = 0;
    this->stepBaseY = 0;
    this->stepT = 0;
}

void Legs::inverseKinematics(float x, float y) {
    this->q2 = acos((dist2(x, y) - dist2(this->L1, this->L2))/(2*this->L1*this->L2));
    if (this->anklePos) 
        this->q2 *= -1;
    this->q1 = atan2(y, x) - atan2(this->L2*sin(q2), this->L1 + this->L2*cos(this->q2));
}

void Legs::draw(sf::RenderWindow& window) {
    sf::Vector2f base(this->baseX, 600 - this->baseY);
    sf::Vector2f elbow = base + this->L1 * sf::Vector2f(cos(this->q1), -sin(this->q1));
    sf::Vector2f end(this->pointX, 600 - this->pointY);
    
    float blobRadius = 10.f;
    sf::CircleShape blob(blobRadius);
    blob.setFillColor(sf::Color::Red);

    const float increment = blobRadius/2;
    sf::Vector2f step = base;
    sf::Vector2f unit = (elbow - base).normalized();
    while (dist2(step.x - base.x, step.y - base.y) <= this->L1*this->L1) {
        blob.setPosition({step.x - blobRadius, step.y - blobRadius});
        step += increment * unit;
        window.draw(blob);
    }

    step = elbow;
    unit = (end - elbow).normalized();
    while (dist2(step.x - elbow.x, step.y - elbow.y) <= this->L2*this->L2) {
        blob.setPosition({step.x - blobRadius, step.y - blobRadius});
        step += increment * unit;
        window.draw(blob);
    }
}

void Legs::update(float linkX, float linkY, float refX, float refY) {
    this->baseX = linkX;
    this->baseY = linkY;

    if (this->stepping) {
        this->stepT += this->dt;
        if (this->stepT > 1.f)
            this->stepping = false;
        this->pointX = (refX - this->stepBaseX) * this->stepT + this->stepBaseX;
        this->pointY = (refY - this->stepBaseY) * this->stepT + this->stepBaseY;
    } else if (fabs(this->q2) < 0.15) {
        this->stepBaseX = this->pointX;
        this->stepBaseY = this->pointY;
        this->stepT = 0;
        this->stepping = true;
    }

    this->inverseKinematics(this->pointX - this->baseX, this->pointY - this->baseY);
} 
