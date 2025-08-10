//
// Created by paula on 8/7/2025.
//
#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H
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
    public:
    unsigned short posX, posY;
    sf::RectangleShape visual;
    ELEMENT element;
    STATE state;
    bool updated;

    public:
    Particle(unsigned short posX, unsigned short posY, ELEMENT element, STATE state);
    Particle();
    void draw(sf::RenderWindow &window) const;
    void update();
    unsigned short getPosX() const;
    unsigned short getPosY() const;
    STATE getState() const;
    void transformInto(ELEMENT element);
    ELEMENT getElement() const;
    bool hasBeenUpdated() const;
    void resetUpdated();

};

#endif //PARTICLE_H
