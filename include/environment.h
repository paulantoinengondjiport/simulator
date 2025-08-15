//
// Created by paula on 8/7/2025.
//
#pragma once
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "particle.h"
#include "grid.h"
#include "SFML/Graphics/RenderWindow.hpp"

#endif //ENVIRONMENT_H


class Environment {
    private:
    unsigned short width;
    unsigned short height;
    unsigned short posX;
    unsigned short posY;
    Grid<Particle> grid;

    [[nodiscard]] bool isOnTop(const Particle &particle) const;
    [[nodiscard]] bool isOnBottom(const Particle &particle) const;
    [[nodiscard]] bool isOnLeft(const Particle &particle) const;
    [[nodiscard]] bool isOnRight(const Particle &particle) const;
    void updateSolidParticles(unsigned short xStart,unsigned short xEnd,unsigned short yStart,unsigned short yEnd);

    public:
    Environment(unsigned short width,unsigned short height, unsigned short posX, unsigned short posY);
    void draw(sf::RenderWindow &window);
    void placeParticle(unsigned short posX, unsigned short posY, ELEMENT element);
    void update(unsigned short xStart,unsigned short xEnd,unsigned short yStart,unsigned short yEnd);
    void checkAndReplaceSolid(Grid<Particle>::grid_iterator &current_it, Grid<Particle>::grid_iterator &scout_it, const Grid<Particle>::grid_iterator &end_it);
};

#include "environment.tpp"
