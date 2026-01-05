#include <SFML/Graphics.hpp>
#include <iostream>

#include "constants.h"
#include "gap_gen.h"


// check window border hit
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

// move pipe function
void movePipe(sf::RectangleShape& topPipe, sf::RectangleShape& bottomPipe, float dt) {
    // sf::Vector2f pipePosition = topPipe.getPosition();
    // pipePosition.x -= PIPE_SPEED * dt;
    // pipe.setPosition(pipePosition);

    float x = topPipe.getPosition().x - PIPE_SPEED * dt;

    topPipe.setPosition(x, topPipe.getPosition().y);
    bottomPipe.setPosition(x, bottomPipe.getPosition().y);


}


// reset pipe pairs
void resetPipes(sf::RectangleShape& topPipe, sf::RectangleShape& bottomPipe) {

    float x = topPipe.getPosition().x;

    if (x + PIPE_WIDTH < 0) {
        
        int gapY = gapGen();

        topPipe.setPosition(WINDOW_WIDTH, gapY - PIPE_HEIGHT);
        bottomPipe.setPosition(WINDOW_WIDTH, gapY + PIPE_GAP);
    }
}

int main() {


    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Flappy bird c++");

    // Clock to measure time between frames (deltaTime)
    sf::Clock clock;

    std::srand(static_cast<unsigned>(std::time(nullptr)));


    // Bird Object
    sf::CircleShape Bird(25.f);
    Bird.setFillColor(sf::Color::Green);
    Bird.setPosition(100.f, 300.f);


    // PIPE PAIR 1
    // Top pipe
    sf::RectangleShape topPipe(sf::Vector2f(PIPE_WIDTH, PIPE_HEIGHT));
    topPipe.setFillColor(sf::Color::Red);
    topPipe.setPosition(800.f,0);

    // Bottom pipe
    sf::RectangleShape bottomPipe(sf::Vector2f(PIPE_WIDTH, PIPE_HEIGHT));
    bottomPipe.setFillColor(sf::Color::Red);
    bottomPipe.setPosition(800,600-PIPE_HEIGHT);

    // PIPE PAIR 2
    sf::RectangleShape topPipe2(sf::Vector2f(PIPE_WIDTH, PIPE_HEIGHT));
    sf::RectangleShape bottomPipe2(sf::Vector2f(PIPE_WIDTH, PIPE_HEIGHT));

    topPipe2.setFillColor(sf::Color::Red);
    bottomPipe2.setFillColor(sf::Color::Red);

    // Spawn it further to the right
    topPipe2.setPosition(WINDOW_WIDTH + 400, 0);
    bottomPipe2.setPosition(WINDOW_WIDTH + 400, WINDOW_HEIGHT - PIPE_HEIGHT);



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

        checkBorderHit(Bird);

        movePipe(topPipe, bottomPipe, dt);
        movePipe(topPipe2, bottomPipe2, dt);

        resetPipes(topPipe, bottomPipe);
        resetPipes(topPipe2, bottomPipe2);

        window.clear();
        window.draw(Bird);
        window.draw(topPipe);
        window.draw(bottomPipe);
        window.draw(topPipe2);
        window.draw(bottomPipe2);
        window.display();
    }
}
