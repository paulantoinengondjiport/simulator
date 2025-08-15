//
// Created by paula on 8/13/2025.
//

#pragma once
#ifndef DRAWING_GRID_H
#define DRAWING_GRID_H
#endif //DRAWING_GRID_H
#include <vector>
#include "grid.h"

#include "SFML/Graphics/VertexArray.hpp"


class DrawingGrid {
    private :
        std::vector<sf::VertexArray> drawings = std::vector<sf::VertexArray>();
        Grid<Particle> &associated_grid;
        unsigned short width,height;
        Grid<int> labelClusters(ELEMENT element); // Connected Components Labelling Algorithm, adapted wikipedia's pseudo code
        void innerCheckFourNeighbours(Grid<int>::grid_iterator &label_it, Grid<bool>::grid_iterator &status_it,
                                      Grid<Particle>::grid_iterator &data_it, ELEMENT &element,
                                      std::vector<Particle> &queue1,
                                      std::vector<Particle> &queue2, int label);
        int outerCheckFourNeighbours(Grid<int>::grid_iterator &label_it, Grid<bool>::grid_iterator &status_it,
                              Grid<Particle>::grid_iterator &data_it, ELEMENT &element,
                              std::vector<Particle> &queue1,
                              std::vector<Particle> &queue2, int label);

        template<typename T>
        std::vector<T> copyVectorIntoAnother(std::vector<T> a, std::vector<T> b);

    public:
        DrawingGrid(unsigned short width, unsigned short height, Grid<Particle> &grid);



};


#include "drawing_grid.tpp"
