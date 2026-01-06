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


struct Bird {
    sf::CircleShape bird;
    float velocity;

    Bird(float start_x_position, float start_y_position) {
        bird.setRadius(20.f);
        bird.setPosition(start_x_position, start_y_position);
    }

    void update(float dt) {
        velocity += GRAVITY * dt;
        float y = bird.getPosition().y;
        float x = bird.getPosition().x;
        y += velocity * dt;
        bird.setPosition(x,y);
        
    }

    void jump() {
        velocity = -350.f;
    }

    void checkBorderHit() {
        float radius = bird.getRadius();
        float diameter = radius * 2;

        sf::Vector2f pos = bird.getPosition();

        if (pos.y < 0) {
            pos.y = 0;
            bird.setPosition(pos);
        }

        if (pos.y > WINDOW_HEIGHT-diameter) {
        pos.y = WINDOW_HEIGHT-diameter;
        bird.setPosition(pos);
        }
    }

};




int main() {

    // Pipes Vector;
    std::vector<PipePair> pipes;
    pipes.emplace_back(WINDOW_WIDTH);
    pipes.emplace_back(WINDOW_WIDTH + 400);


    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Flappy bird c++");

    // Clock to measure time between frames (deltaTime)
    sf::Clock clock;

    Bird Bird{100.f,300.f};



    // How fast the bird is moving up/down
    float velocity = 0.f;


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
                Bird.jump();
        }
        }


        // Time passed since last frame (in seconds)
        float dt = clock.restart().asSeconds();

        // Gravity makes the bird fall faster every frame
        


        Bird.update(dt);
        Bird.checkBorderHit();



        for (auto& pipe: pipes) {
            pipe.update(dt);
            pipe.reset();
            if (pipe.collidesWith(Bird.bird)) {
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

        window.draw(Bird.bird);
        window.display();
    }
}
