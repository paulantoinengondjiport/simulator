//
// Created by paula on 8/8/2025.
//
#pragma once
#ifndef GRID_H
#define GRID_H
#include <vector>
#include "particle.h"



class Grid {
    protected:
    std::vector<Particle> data;
    unsigned short width;
    unsigned short height;

    public:
    Grid(unsigned short width,unsigned short height);

    class grid_iterator {
        public:
        std::vector<Particle>::iterator iterator;
        grid_iterator(Grid &associated_grid, unsigned short posX,unsigned short posY);
        grid_iterator(const grid_iterator &other);
        void up();
        void down();
        void left();
        void right();
        void operator++();
        void operator--();
        grid_iterator operator+(int amount) const;
        Particle& operator*() const;
        bool operator==(const grid_iterator &other) const;
        bool operator!=(const grid_iterator &other) const;
        bool operator<(const grid_iterator &other) const;
        bool operator>(const grid_iterator &other) const;
        private:
        Grid &grid;
    };

};



#endif //GRID_H
