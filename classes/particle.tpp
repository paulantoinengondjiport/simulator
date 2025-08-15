//
// Created by paula on 8/7/2025.
//
#pragma once
#include "particle.h"

inline void Particle::draw(sf::RenderWindow &window) const {
    if (this->element != ELEMENT::VOID){
        window.draw(this->visual);
    }
}

inline void Particle::update() {
    this->updated = !this->updated;
}

inline unsigned short Particle::getPosX() const {
    return this->posX;
}

inline unsigned short Particle::getPosY() const {
    return this->posY;
}

inline STATE Particle::getState() const {
    return this->state;
}

inline Particle::Particle(unsigned short posX, unsigned short posY, ELEMENT element, STATE state) {
    this->posX = posX;
    this->posY = posY;
    this->element = element;
    this-> state = state;
    this->updated = false;
    this->visual = sf::VertexArray(sf::PrimitiveType::TriangleStrip, 4);
    visual[0].position = sf::Vector2f((static_cast<float>(this->posX) * SCALE), (static_cast<float>(this->posY) * SCALE));
    visual[1].position = sf::Vector2f((static_cast<float>(this->posX) * SCALE) + SCALE, (static_cast<float>(this->posY) * SCALE));
    visual[2].position = sf::Vector2f((static_cast<float>(this->posX) * SCALE), (static_cast<float>(this->posY) * SCALE) + SCALE);
    visual[3].position = sf::Vector2f((static_cast<float>(this->posX) * SCALE) + SCALE, (static_cast<float>(this->posY) * SCALE) + SCALE);
    this->setFillColor(sf::Color::Black);
}

inline Particle::Particle() {
    this->posX = 0;
    this->posY = 0;
    this->element = ELEMENT::VOID;

    this->visual = sf::VertexArray(sf::PrimitiveType::Triangles, 4);
    visual[0].position = sf::Vector2f((static_cast<float>(this->posX) * SCALE), (static_cast<float>(this->posY) * SCALE));
    visual[1].position = sf::Vector2f((static_cast<float>(this->posX) * SCALE) + SCALE, (static_cast<float>(this->posY) * SCALE));
    visual[2].position = sf::Vector2f((static_cast<float>(this->posX) * SCALE), (static_cast<float>(this->posY) * SCALE) + SCALE);
    visual[3].position = sf::Vector2f((static_cast<float>(this->posX) * SCALE) + SCALE, (static_cast<float>(this->posY) * SCALE) + SCALE);
    this->setFillColor(sf::Color{0,0,0});
    this->state = STATE::GAS;
    this->updated = false;
}

inline void Particle::transformInto(ELEMENT element) {
    this->element = element;
    switch (this->element) {
        case ELEMENT::VOID:
            this->setFillColor(sf::Color{0,0,0});
            this->state = STATE::GAS;
            break;

        case ELEMENT::DIRT:
            this->setFillColor(sf::Color{155,118,83});
            this->state = STATE::SOLID;
            break;

        case ELEMENT::WATER:
            this->setFillColor(sf::Color{0,105,148});
            this->state = STATE::LIQUID;
            break;
    }
}

inline ELEMENT Particle::getElement() const {
    return this->element;
}

inline bool Particle::hasBeenUpdated() const {
    return this->updated;
}

inline void Particle::resetUpdated() {
    this->updated = false;
}

inline void Particle::setFillColor(sf::Color color) {
    for (int i = 0; i < 4; i++) {
        this->visual[i].color = color;
    }

}

inline void Particle::setX(int posX) {
    this->posX = posX;
}

inline void Particle::setY(int posY) {
    this->posY = posY;
}


