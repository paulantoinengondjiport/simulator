//
// Created by paula on 8/7/2025.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <X11/Xlib.h>

#include "environment.h"
#include "threadpool.h"

int main() {

    // Window creation
    sf::RenderWindow window;
    window.create(sf::VideoMode({XSIZE, YSIZE}), "My window");
    window.setPosition(sf::Vector2i(0, 0));  // Adjust coordinates as needed
    window.setFramerateLimit(60);

    // Setting up FPS count
    sf::Font font("./font/arial.ttf");
    sf::Text fpsCount = sf::Text(font, "", sf::Text::Bold);
    fpsCount.setPosition({0,0});
    fpsCount.setCharacterSize(XSIZE/50);
    fpsCount.setFillColor(sf::Color::White);

    auto mousePos = sf::Mouse::getPosition(window);
    // Creating the simulation environment
    Environment environment = Environment(XSIZE/SCALE,YSIZE/SCALE,0,0);
    unsigned int yStart = 0;
    unsigned int yEnd = (YSIZE / SCALE);
    unsigned int xStart = 0;
    unsigned int xEnd = (XSIZE / SCALE);

    sf::Clock clock;
    unsigned int number_of_threads = 5;
    ThreadPool pool = ThreadPool(number_of_threads);

    // running window loop
    while (window.isOpen()) {
        window.clear();
        // Checking events

        while (const std::optional event = window.pollEvent()) {
            // Check if window need to be closed
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return EXIT_SUCCESS;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            mousePos = sf::Mouse::getPosition(window);
            if (mousePos.x < XSIZE && mousePos.y < YSIZE && mousePos.x > 0 && mousePos.y > 0) {
                environment.placeParticle(mousePos.x/SCALE,mousePos.y/SCALE,ELEMENT::DIRT);
            }
        }


        // Draw then update every particle in the particle vector


        clock.restart();

        // for (int i = 0; i < number_of_threads; i++) { //ENVIRONMENT::update is not multithreading safe keep the thread numbers at 1
        //     pool.enqueue([i,&environment, number_of_threads]() {
        //         unsigned int yStart = ((YSIZE / SCALE) / number_of_threads) * i;
        //         unsigned int yEnd = ((YSIZE / SCALE) / number_of_threads) * (i + 1);
        //         unsigned int xStart = ((XSIZE / SCALE) / number_of_threads) * i;;
        //         unsigned int xEnd = ((XSIZE / SCALE) / number_of_threads) * (i + 1);
        //         environment.update(xStart, xEnd, yStart, yEnd);
        //     });
        // }

        pool.enqueue([&environment,xStart,xEnd,yStart,yEnd]() {

            environment.update(xStart, xEnd, yStart, yEnd);
        });



        // Render



        environment.draw(window);
        window.draw(fpsCount);
        window.display();

        pool.enqueue([&clock,&fpsCount]() {
            int framePerSecond = 1000000 / clock.getElapsedTime().asMicroseconds();
            fpsCount.setString("FPS: " + std::to_string(framePerSecond));
        });

        // FPS counter



    }

}
