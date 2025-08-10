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


    auto mousePos = sf::Mouse::getPosition(window);
    // Creating the simulation environment
    Environment environment = Environment(XSIZE/SCALE,YSIZE/SCALE,0,0);

    sf::Clock clock;
    unsigned int number_of_threads = 1; //BROKEN DO NOT SET NUMBER OF THREADS OTHER THAN 1
    ThreadPool pool = ThreadPool(number_of_threads);

    unsigned int grid_slice_length = static_cast<unsigned int>((XSIZE/static_cast<float>(SCALE)) * (YSIZE/static_cast<float>(SCALE))) / number_of_threads;
    // running window loop
    while (window.isOpen()) {
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

        for (int i = 0; i < number_of_threads; i++) { //ENVIRONMENT::update is not multithreading safe keep the thread numbers at 1
            pool.enqueue([i,&environment, number_of_threads]() {
                unsigned int yStart = ((YSIZE / SCALE) / number_of_threads) * i;
                unsigned int yEnd = ((YSIZE / SCALE) / number_of_threads) * (i + 1);
                unsigned int xStart = ((XSIZE / SCALE) / number_of_threads) * i;;
                unsigned int xEnd = ((XSIZE / SCALE) / number_of_threads) * (i + 1);
                environment.update(xStart, xEnd, yStart, yEnd);
            });
        }


        // Render
        window.clear();

        environment.draw(window);
        window.display();

        float frameTime = clock.getElapsedTime().asMilliseconds();
        std::cout << "Frame time: " << frameTime << " ms\n";

    }

}
