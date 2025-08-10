//
// Created by paula on 8/7/2025.
//
#include "particle.h"


void Particle::draw(sf::RenderWindow &window) const {
    if (this->element != ELEMENT::VOID){
        window.draw(this->visual);
    }
}

void Particle::update() {
    this->updated = !this->updated;
}

unsigned short Particle::getPosX() const {
    return this->posX;
}

unsigned short Particle::getPosY() const {
    return this->posY;
}

STATE Particle::getState() const {
    return this->state;
}

Particle::Particle(unsigned short posX, unsigned short posY, ELEMENT element, STATE state) {
    this->posX = posX;
    this->posY = posY;
    this->visual = sf::RectangleShape({SCALE,SCALE});
    this->element = element;
    this->visual.setPosition({static_cast<float>(this->posX * SCALE), static_cast<float>(this->posY * SCALE)});
    this->visual.setFillColor(sf::Color{0,0,0});
    this-> state = state;
    this->updated = false;

}

Particle::Particle() {
    this->posX = 0;
    this->posY = 0;
    this->element = ELEMENT::VOID;
    this->visual = sf::RectangleShape({SCALE,SCALE});
    this->visual.setPosition({static_cast<float>(this->posX * SCALE), static_cast<float>(this->posY * SCALE)});
    this->visual.setFillColor(sf::Color{0,0,0});
    this->state = STATE::GAS;
    this->updated = false;
}
void Particle::transformInto(ELEMENT element) {
    this->element = element;
    switch (this->element) {
        case ELEMENT::VOID:
            this->visual.setFillColor(sf::Color{0,0,0});
            this->state = STATE::GAS;
            break;

        case ELEMENT::DIRT:
            this->visual.setFillColor(sf::Color{155,118,83});
            this->state = STATE::SOLID;
            break;

        case ELEMENT::WATER:
            this->visual.setFillColor(sf::Color{0,105,148});
            this->state = STATE::LIQUID;
            break;
    }
}

ELEMENT Particle::getElement() const {
    return this->element;
}

bool Particle::hasBeenUpdated() const {
    return this->updated;
}

void Particle::resetUpdated() {
    this->updated = false;
}