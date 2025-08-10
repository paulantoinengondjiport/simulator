//
// Created by paula on 8/8/2025.
//

#include "grid.h"


Grid::Grid(const unsigned short width, const unsigned short height) {
    for (unsigned short i = 0; i < height; i++) {
        for (unsigned short j = 0; j < width; j++) {
            this->data.emplace_back(j,i,ELEMENT::VOID, STATE::GAS);

        }
    }
    this->width = width;
    this->height = height;
}

Grid::grid_iterator::grid_iterator(Grid &associated_grid, unsigned short posX,unsigned short posY): grid(associated_grid) {
    ;
    unsigned short index = posX + posY * grid.width;
    this->iterator = grid.data.begin() + index;

}

Grid::grid_iterator::grid_iterator(const grid_iterator &other) : iterator(other.iterator), grid(other.grid) {}

void Grid::grid_iterator::up() {
    for (unsigned short i = 0; i < this->grid.width; i++) {
        this->operator--();
    }
}

void Grid::grid_iterator::down() {
    for (unsigned short i = 0; i < this->grid.width; i++) {
        this->operator++();
    }
}

void Grid::grid_iterator::right() {
    this->operator++();
}

void Grid::grid_iterator::left() {
    this->operator--();
}

Particle& Grid::grid_iterator::operator*() const {
    return *this->iterator;
}

void Grid::grid_iterator::operator++() {
    ++this->iterator;
}

void Grid::grid_iterator::operator--() {
    --this->iterator;
}

Grid::grid_iterator Grid::grid_iterator::operator+(const int amount) const {
    Grid::grid_iterator newOne = Grid::grid_iterator(this->grid,this->iterator->getPosX(),this->iterator->getPosY());
    newOne.iterator = newOne.iterator + amount;
    return newOne;
}

bool Grid::grid_iterator::operator==(const Grid::grid_iterator &other) const {
    return this->iterator == other.iterator;
}

bool Grid::grid_iterator::operator!=(const Grid::grid_iterator &other) const {
    return this->iterator != other.iterator;
}

bool Grid::grid_iterator::operator<(const Grid::grid_iterator &other) const {
    return this->iterator < other.iterator;
}

bool Grid::grid_iterator::operator>(const Grid::grid_iterator &other) const {
    return this->iterator > other.iterator;
}