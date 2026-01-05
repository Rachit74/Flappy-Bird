#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "constants.h"
#include "gap_gen.h"

struct PipePair {
    sf::RectangleShape top;
    sf::RectangleShape bottom;


    PipePair(float start_x_position) {
        top.setSize({PIPE_WIDTH, PIPE_HEIGHT});
        bottom.setSize({PIPE_WIDTH, PIPE_HEIGHT});
        
        top.setFillColor(sf::Color::Red);
        bottom.setFillColor(sf::Color::Red);

        int gapY = gapGen();
        top.setPosition(start_x_position, gapY - PIPE_HEIGHT);
        bottom.setPosition(start_x_position, gapY + PIPE_GAP);

    }

    void update(float dt) {
        float x = top.getPosition().x - PIPE_SPEED * dt;

        top.setPosition(x, top.getPosition().y);
        bottom.setPosition(x, bottom.getPosition().y);
    }

    void reset() {
        float x = top.getPosition().x;

        if (x + PIPE_WIDTH < 0) {
            int gapY = gapGen();

            top.setPosition(WINDOW_WIDTH, gapY - PIPE_HEIGHT);
            bottom.setPosition(WINDOW_WIDTH, gapY + PIPE_GAP);
        }
    }

    bool collidesWith(const sf::CircleShape& bird) const {
        return bird.getGlobalBounds().intersects(top.getGlobalBounds()) || bird.getGlobalBounds().intersects(bottom.getGlobalBounds());
    }
};


// check window border hit
// checks if the bird has hit top and bottom window borders
void checkBorderHit(sf::CircleShape& Bird) {
    float radius = Bird.getRadius();
    float diameter = radius * 2;

    sf::Vector2f birdPosition = Bird.getPosition();

    if (birdPosition.y < 0) {
        birdPosition.y = 0;
        Bird.setPosition(birdPosition);
    }

    if (birdPosition.y > WINDOW_HEIGHT-diameter) {
        birdPosition.y = WINDOW_HEIGHT-diameter;
        Bird.setPosition(birdPosition);
    }
}


int main() {

    // Pipes Vector;
    std::vector<PipePair> pipes;
    pipes.emplace_back(WINDOW_WIDTH);
    pipes.emplace_back(WINDOW_WIDTH + 400);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Flappy bird c++");

    // Clock to measure time between frames (deltaTime)
    sf::Clock clock;


    // Bird Object
    sf::CircleShape Bird(25.f);
    Bird.setFillColor(sf::Color::Green);
    Bird.setPosition(100.f, 300.f);



    // How fast the bird is moving up/down
    float velocity = 0.f;

    const float g = 700.f;

    // game loop
    while (window.isOpen()) {
        
        // event loop
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Space) {
            velocity = -350.f;
        }
        }


        // Time passed since last frame (in seconds)
        float dt = clock.restart().asSeconds();

        // Gravity makes the bird fall faster every frame
        velocity += g * dt;

        // Get the bird's current position
        // Move the bird down using its speed
        // Apply the new position to the bird
        sf::Vector2f birdPosition = Bird.getPosition();
        birdPosition.y += velocity * dt;
        Bird.setPosition(birdPosition);




        for (auto& pipe: pipes) {
            pipe.update(dt);
            pipe.reset();
            if (pipe.collidesWith(Bird)) {
                std::cout << "Hit\n";
            } else {
                std::cout << "Not Hitting\n";
            }
            
        }

        window.clear();

        for (const auto& pipe: pipes) {
            window.draw(pipe.top);
            window.draw(pipe.bottom);
        }

        window.draw(Bird);
        window.display();
    }
}
