//
// Created by paula on 8/7/2025.
// Created by paula on 8/7/2025.
//
#pragma once
#include "environment.h"

inline Environment::Environment(unsigned short width,unsigned short height, unsigned short posX, unsigned short posY): grid(width,height, Particle()) {

    this->width = width;
    this->height = height;
    this->posX = posX;
    this->posY = posY;
    Grid<Particle>::grid_iterator it = Grid<Particle>::grid_iterator(this->grid,0,0);
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            (*it) = Particle(j,i,ELEMENT::VOID,STATE::GAS);
            ++it;
        }
    }
}

inline void Environment::draw(sf::RenderWindow &window){
    auto iterator = Grid<Particle>::grid_iterator(this->grid,0,0);
    for (int i = 0; i < this->width * this->height; i++) {

        (*iterator).draw(window);
        ++iterator;

    }
}

inline void Environment::placeParticle(unsigned short posX, unsigned short posY, ELEMENT element) {
    Grid<Particle>::grid_iterator iterator = Grid<Particle>::grid_iterator(this->grid,0,0);

    for (int i = 0; i < posX + this->width * posY ; i++) {
        ++iterator;
    }
    Particle& current_particle = *iterator;
    current_particle.transformInto(element);
}

inline bool Environment::isOnTop(const Particle &particle) const{
    return particle.getPosY() == 0;
}

inline bool Environment::isOnBottom(const Particle &particle) const {
    return particle.getPosY() == this->height - 1;
}

inline bool Environment::isOnLeft(const Particle &particle) const{
    return particle.getPosX() == 0;
}

inline bool Environment::isOnRight(const Particle& particle) const{
    return particle.getPosX() == this->width - 1;
}

inline void Environment::update(unsigned short xStart,unsigned short xEnd,unsigned short yStart,unsigned short yEnd) {
    unsigned int chunk_size = (yEnd-yStart) * width + (xEnd-xStart);

    this->updateSolidParticles(xStart,xEnd,yStart,yEnd);



    auto update_iterator = Grid<Particle>::grid_iterator(this->grid,0,0);
    for (int i = 0; i < chunk_size; i++) {
        (*update_iterator).resetUpdated();
        ++update_iterator;
    }
}

inline void Environment::updateSolidParticles(unsigned short xStart,unsigned short xEnd,unsigned short yStart,unsigned short yEnd) {
    const int chunk_size = (yEnd-yStart) * width + (xEnd-xStart);

    auto current_it = Grid<Particle>::grid_iterator(this->grid,0,0);
    auto scout_it = Grid<Particle>::grid_iterator(current_it);
    const Grid<Particle>::grid_iterator end_it = current_it + chunk_size;
    this->checkAndReplaceSolid(current_it,scout_it,end_it);
}

inline void Environment::checkAndReplaceSolid(Grid<Particle>::grid_iterator &current_it, Grid<Particle>::grid_iterator &scout_it, const Grid<Particle>::grid_iterator &end_it) {

    while (current_it < end_it) {
        ELEMENT tmp_elem = (*current_it).getElement();

        if (!this->isOnBottom(*current_it) && !(*current_it).hasBeenUpdated() && (*current_it).getState() == STATE::SOLID) {

            scout_it.down();

            if (((*scout_it).getState() == STATE::GAS || (*scout_it).getState() == STATE::LIQUID) && scout_it < end_it) {
                (*current_it).transformInto((*scout_it).getElement());
                (*scout_it).transformInto(tmp_elem);
                (*scout_it).update();
            }

            else if (!this->isOnLeft(*current_it) && (*current_it).getState() == STATE::SOLID) {
                scout_it.left();
                if (((*scout_it).getState() == STATE::GAS || (*scout_it).getState() == STATE::LIQUID) && scout_it < end_it) {
                    (*current_it).transformInto((*scout_it).getElement());
                    (*scout_it).transformInto(tmp_elem);
                    (*scout_it).update();
                }
                else if (!this->isOnRight(*current_it) && (*current_it).getState() == STATE::SOLID) {
                    scout_it.right();scout_it.right();
                    if (((*scout_it).getState() == STATE::GAS || (*scout_it).getState() == STATE::LIQUID) && scout_it < end_it) {
                        (*current_it).transformInto((*scout_it).getElement());
                        (*scout_it).transformInto(tmp_elem);
                        (*scout_it).update();
                    }
                    scout_it.left();scout_it.left();
                }
                scout_it.right();
            }
            if (this->isOnLeft(*current_it) && (*current_it).getState() == STATE::SOLID) {
                scout_it.right();
                if (((*scout_it).getState() == STATE::GAS || (*scout_it).getState() == STATE::LIQUID) && scout_it < end_it) {
                    (*current_it).transformInto((*scout_it).getElement());
                    (*scout_it).transformInto(tmp_elem);
                    (*scout_it).update();
                }
                scout_it.left();
            }

            scout_it.up();
        }
        ++scout_it;
        ++current_it;
    }

}