//
// Created by andre on 31/12/24.
//

#include "Chain.h"

float sgn(float x) {
    if (x > 0)
        return 1.0;
    return -1.0;
}

Chain::Chain(const std::vector<float>& link_sizes) {
    this->links.resize(link_sizes.size());
    this->headDirection = 0;
    this->neckAng = PI;
    float sum = 0;
    for (int i = 0; i < this->links.size(); ++i) {
        this->links[i][0] = 550 + sum;
        this->links[i][1] = 300;
        this->links[i][2] = link_sizes[i];
        sum += link_sizes[i];
    }
}

void Chain::reset() {
    this->headDirection = 0;
    this->neckAng = PI;
    float sum = 0;
    for (int i = 0; i < this->links.size(); ++i) {
        this->links[i][0] = 550 + sum;
        this->links[i][1] = 300;
        sum += this->links[i][2];
    }

}

void Chain::draw(sf::RenderWindow& window) {
    for (auto link : this->links) {
        sf::CircleShape c(link[2]);
        c.setPosition({link[0] - c.getRadius(), 600 - link[1] - c.getRadius()});
        c.setFillColor(sf::Color::Red);
        window.draw(c);
    }
    
    float eyeRadius = 4;
    sf::CircleShape eye(eyeRadius);
    eye.setFillColor(sf::Color::White);
    
    float x = this->links[0][0] + (this->links[0][2] - eyeRadius)*cos(this->neckAng + PI/3);
    float y = this->links[0][1] + (this->links[0][2] - eyeRadius)*sin(this->neckAng + PI/3);
    eye.setPosition({x - eyeRadius, 600 - y - eyeRadius});
    window.draw(eye);
    
    x = this->links[0][0] + (this->links[0][2] - eyeRadius)*cos(this->neckAng - PI/3);
    y = this->links[0][1] + (this->links[0][2] - eyeRadius)*sin(this->neckAng - PI/3);
    eye.setPosition({x - eyeRadius, 600 - y - eyeRadius});
    window.draw(eye);
}

void Chain::move() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
        this->reset();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        this->front();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        this->left();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        this->right();

    if (fabs(this->headDirection) > this->EPS)
        this->headDirection *= 0.99;

}


void Chain::front() {
    float ang = this->neckAng + this->headDirection;
    this->links[0][0] += cos(ang) * this->frontStep;
    this->links[0][1] += sin(ang) * this->frontStep;
    this->applyConstraints();
}

void Chain::left() {
    this->headDirection += this->angleStep;
    if (this->headDirection > this->maxAngle)
        this->headDirection = this->maxAngle;
    // this->links[0][0] = this->links[1][0] + cos(this->headDirection) * this->links[0][2];
    // this->links[0][1] = this->links[1][1] - sin(this->headDirection) * this->links[0][2];
}

void Chain::right() {
    this->headDirection -= this->angleStep;
    if (this->headDirection < -this->maxAngle)
        this->headDirection = -this->maxAngle;
    // this->links[0][0] = this->links[1][0] + cos(this->headDirection) * this->links[0][2];
    // this->links[0][1] = this->links[1][1] - sin(this->headDirection) * this->links[0][2];
}

void Chain::applyConstraints() {
    float x, y, factor;
    for (int i = 1; i < this->links.size(); ++i) {
        x = this->links[i][0] - this->links[i-1][0];
        y = this->links[i][1] - this->links[i-1][1];
        factor = this->links[i-1][2]/sqrt(x*x + y*y); // scaling factor
        this->links[i][0] = this->links[i-1][0] + x*factor;
        this->links[i][1] = this->links[i-1][1] + y*factor;
    }
    x = this->links[0][0] - this->links[1][0];
    y = this->links[0][1] - this->links[1][1];
    this->neckAng = atan2(y, x);
}
