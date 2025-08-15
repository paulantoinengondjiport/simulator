//
// Created by paula on 8/7/2025.
//
#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H
#endif //PARTICLE_H
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#define XSIZE 800
#define YSIZE 600
#define SCALE 4

enum ELEMENT {
    DIRT, WATER, VOID
};

enum STATE {
    SOLID, LIQUID, GAS
};

enum TEXTURE {

};

class Particle {
    private:
    unsigned short posX, posY;
    sf::VertexArray visual;
    ELEMENT element;
    STATE state;
    bool updated;
    void setFillColor(sf::Color color);


    public:
    Particle(unsigned short posX, unsigned short posY, ELEMENT element, STATE state);
    Particle();
    void draw(sf::RenderWindow &window) const;
    void update();
    [[nodiscard]] unsigned short getPosX() const;
    [[nodiscard]] unsigned short getPosY() const;
    [[nodiscard]] STATE getState() const;
    void transformInto(ELEMENT element);
    [[nodiscard]] ELEMENT getElement() const;
    [[nodiscard]] bool hasBeenUpdated() const;
    void resetUpdated();
    void setX(int posX);
    void setY(int posY);


};

#include "particle.tpp"
