//
// Created by paula on 8/8/2025.
//
#pragma once
#ifndef GRID_H
#define GRID_H
#include <vector>
#include "particle.h"


template <typename T>
class Grid {
    protected:
    std::vector<T> data;
    unsigned short width;
    unsigned short height;

    public:
    Grid(unsigned short width, unsigned short height, T fillerData);

    class grid_iterator {
        public:
        typename std::vector<T>::iterator iterator;
        grid_iterator(Grid &associated_grid, unsigned short posX,unsigned short posY);
        grid_iterator(const grid_iterator &other);
        void up();
        void down();
        void left();
        void right();
        void operator++();
        void operator--();
        grid_iterator operator+(int amount) const;
        T& operator*() const;
        bool operator==(const grid_iterator &other) const;
        bool operator!=(const grid_iterator &other) const;
        bool operator<(const grid_iterator &other) const;
        bool operator>(const grid_iterator &other) const;
        private:
        Grid &grid;
    };

};

#include "grid.tpp"
#endif //GRID_H
