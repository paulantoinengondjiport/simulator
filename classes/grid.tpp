//
// Created by paula on 8/8/2025.
//
#pragma once
#include "grid.h"

template <typename T>
Grid<T>::Grid(unsigned short width, unsigned short height, T fillerData) {
    for (unsigned short i = 0; i < height; i++) {
        for (unsigned short j = 0; j < width; j++) {
            this->data.emplace_back(fillerData);

        }
    }
    this->width = width;
    this->height = height;
}

template <typename T>
Grid<T>::grid_iterator::grid_iterator(Grid &associated_grid, unsigned short posX,unsigned short posY): grid(associated_grid) {
    ;
    unsigned short index = posX + posY * grid.width;
    this->iterator = grid.data.begin() + index;

}

template <typename T>
Grid<T>::grid_iterator::grid_iterator(const grid_iterator &other) : iterator(other.iterator), grid(other.grid) {}

template <typename T>
void Grid<T>::grid_iterator::up() {
    for (unsigned short i = 0; i < this->grid.width; i++) {
        this->operator--();
    }
}

template <typename T>
void Grid<T>::grid_iterator::down() {
    for (unsigned short i = 0; i < this->grid.width; i++) {
        this->operator++();
    }
}

template <typename T>
void Grid<T>::grid_iterator::right() {
    this->operator++();
}

template <typename T>
void Grid<T>::grid_iterator::left() {
    this->operator--();
}

template <typename T>
T& Grid<T>::grid_iterator::operator*() const {
    return *this->iterator;
}

template <typename T>
void Grid<T>::grid_iterator::operator++() {
    ++this->iterator;
}

template <typename T>
void Grid<T>::grid_iterator::operator--() {
    --this->iterator;
}

template <typename T>
typename Grid<T>::grid_iterator Grid<T>::grid_iterator::operator+(const int amount) const {
    Grid<T>::grid_iterator newOne = Grid<T>::grid_iterator(this->grid,this->iterator->getPosX(),this->iterator->getPosY());
    newOne.iterator = newOne.iterator + amount;
    return newOne;
}

template <typename T>
bool Grid<T>::grid_iterator::operator==(const Grid<T>::grid_iterator &other) const {
    return this->iterator == other.iterator;
}

template <typename T>
bool Grid<T>::grid_iterator::operator!=(const Grid<T>::grid_iterator &other) const {
    return this->iterator != other.iterator;
}

template <typename T>
bool Grid<T>::grid_iterator::operator<(const Grid<T>::grid_iterator &other) const {
    return this->iterator < other.iterator;
}

template <typename T>
bool Grid<T>::grid_iterator::operator>(const Grid<T>::grid_iterator &other) const {
    return this->iterator > other.iterator;
}