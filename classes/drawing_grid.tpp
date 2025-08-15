//
// Created by paula on 8/13/2025.
//
#pragma once
#include <vector>

#include "drawing_grid.h"


inline DrawingGrid::DrawingGrid(unsigned short width, unsigned short height, Grid<Particle> &grid) : associated_grid(grid) {
    this->width = width;
    this->height = height;
    this->associated_grid = grid;
}

inline Grid<int> DrawingGrid::labelClusters(ELEMENT element) {
    int label = 0;
    auto label_array = Grid<int>(this->width,this->height,0);
    auto status_array = Grid<bool>(this->width,this->height,0);
    auto label_it = Grid<int>::grid_iterator(label_array,0,0);
    auto status_it = Grid<bool>::grid_iterator(status_array,0,0);
    auto data_it = Grid<Particle>::grid_iterator(this->associated_grid,0,0);
    std::vector<Particle> queue1;
    std::vector<Particle> queue2;
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            if (!(*status_it)) {
                if ((*data_it).getElement() == element) {
                    label = this->outerCheckFourNeighbours(label_it, status_it, data_it, element, queue1, queue2, label);
                    (*label_it) = label;
                    (*status_it) = true;
                    while (!queue1.empty()) {
                        this->innerCheckFourNeighbours(label_it, status_it, data_it, element, queue1, queue2, label);
                        (*label_it) = label;
                        (*status_it) = true;
                        queue1.pop_back();
                        queue1 = queue2; queue2 = std::vector<Particle>();
                    } // End While
                    label += 1;
                }

                else {
                    (*status_it) = true;
                }

            }
            ++label_it;
            ++status_it;
            ++data_it;
        }
    }
    return label_array;
}

inline void DrawingGrid::innerCheckFourNeighbours(
    Grid<int>::grid_iterator &label_it,
    Grid<bool>::grid_iterator &status_it,
    Grid<Particle>::grid_iterator &data_it,
    ELEMENT &element,
    std::vector<Particle> &queue1,
    std::vector<Particle> &queue2,
    int label
) {
    if ((*data_it).getPosY() > 0) {
        data_it.up();
        status_it.up();
        label_it.up();
        if (!(*status_it)) {
            if ((*data_it).getElement() == element) {
                queue2.push_back(*data_it);
            } else {
                (*status_it) = true;
            }
        }
        data_it.down();
        status_it.down();
        label_it.down();
    }
    if ((*data_it).getPosY() < (this->height-1)) {
        data_it.down();
        status_it.down();
        label_it.down();
        if (!(*status_it)) {
            if ((*data_it).getElement() == element) {
                queue2.push_back(*data_it);
            } else {
                (*status_it) = true;
            }
        }
        data_it.up();
        status_it.up();
        label_it.up();
    }
    if ((*data_it).getPosX() > 0) {
        data_it.left();
        status_it.left();
        label_it.left();
        if (!(*status_it)) {
            if ((*data_it).getElement() == element) {
                queue2.push_back(*data_it);
            } else {
                (*status_it) = true;
            }
        }
        data_it.right();
        status_it.right();
        label_it.right();
    }
    if ((*data_it).getPosX() < (this->width-1)) {
        data_it.right();
        status_it.right();
        label_it.right();
        if (!(*status_it)) {
            if ((*data_it).getElement() == element) {
                queue2.push_back(*data_it);
            } else {
                (*status_it) = true;
            }
        }
        data_it.left();
        status_it.left();
        label_it.left();
    }
}

inline int DrawingGrid::outerCheckFourNeighbours(Grid<int>::grid_iterator &label_it,
                                                  Grid<bool>::grid_iterator &status_it,
                                                  Grid<Particle>::grid_iterator &data_it, ELEMENT &element,
                                                  std::vector<Particle> &queue1,
                                                  std::vector<Particle> &queue2, int label) {
    if ((*data_it).getPosY() > 0) {
        data_it.up();
        status_it.up();
        label_it.up();
        if (!(*status_it)) {
            if ((*data_it).getElement() == element) {
                queue1.push_back(*data_it);
            } else {
                (*status_it) = true;
            }
        }
        data_it.down();
        status_it.down();
        label_it.down();
    }

    if ((*data_it).getPosY() < (this->height - 1)) {
        data_it.down();
        status_it.down();
        label_it.down();
        if (!(*status_it)) {
            if ((*data_it).getElement() == element) {
                queue1.push_back(*data_it);
            } else {
                (*status_it) = true;
            }
        }
        data_it.up();
        status_it.up();
        label_it.up();
    }

    if ((*data_it).getPosX() > 0) {
        data_it.left();
        status_it.left();
        label_it.left();
        if (!(*status_it)) {
            if ((*data_it).getElement() == element) {
                queue1.push_back(*data_it);
            } else {
                (*status_it) = true;
            }
        }
        data_it.right();
        status_it.right();
        label_it.right();
    }
    if ((*data_it).getPosX() < (this->width - 1)) {
        data_it.right();
        status_it.right();
        label_it.right();
        if (!(*status_it)) {
            if ((*data_it).getElement() == element) {
                queue1.push_back(*data_it);
            } else {
                (*status_it) = true;
            }
        }
        data_it.left();
        status_it.left();
        label_it.left();
    }
    return label;
}

template<typename T>
std::vector<T> DrawingGrid::copyVectorIntoAnother(std::vector<T> a, std::vector<T> b) {

    std::size_t insertionPoint = a.size() + 1;
    std::size_t elemCount = std::max(insertionPoint + b.size(), a.size());
    a.resize(elemCount);
    std::copy(std::cbegin(b), std::cend(b), std::begin(a) + insertionPoint);

    return a;
}

