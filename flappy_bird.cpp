#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "constants.h"
#include "gap_gen.h"


enum GameState {
    STATE_PLAYING,
    STATE_OVER,
};

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
    float velocity = 0.f;

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

    void checkBorderHit(GameState& current_game_state) {
        float radius = bird.getRadius();
        float diameter = radius * 2;

        sf::Vector2f pos = bird.getPosition();

        if (pos.y < 0) {
            // pos.y = 0;
            // bird.setPosition(pos);
            current_game_state = STATE_OVER;
        }

        if (pos.y > WINDOW_HEIGHT-diameter) {
            // pos.y = WINDOW_HEIGHT-diameter;
            current_game_state = STATE_OVER;
            // bird.setPosition(pos);
        }
    }

};


void drawGameOverScreen(sf::RenderWindow& window, sf::Font& font) {
    sf::Text gameOverText;
    gameOverText.setFont(font); 
    gameOverText.setString("GAME OVER! Press R to Restart.");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(window.getSize().x / 2.f - gameOverText.getGlobalBounds().width / 2.f, 
                             window.getSize().y / 2.f);

    window.draw(gameOverText);
}


int main() {

    sf::Font font;
    if (!font.loadFromFile("ubuntu-font.ttf")) {
        std::cerr << "Unable to load font!\n";
    }

    GameState current_game_state = STATE_PLAYING;

    // Pipes Vector;
    std::vector<PipePair> pipes;
    pipes.emplace_back(WINDOW_WIDTH);
    pipes.emplace_back(WINDOW_WIDTH + 400);


    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Flappy bird c++");

    // Clock to measure time between frames (deltaTime)
    sf::Clock clock;

    Bird Bird{100.f,300.f};


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

        window.clear();

        // state handling
        if (current_game_state == STATE_PLAYING) {
            
            Bird.update(dt);
            Bird.checkBorderHit(current_game_state);



            for (auto& pipe: pipes) {
                pipe.update(dt);
                pipe.reset();
                if (pipe.collidesWith(Bird.bird)) {
                    current_game_state = STATE_OVER;
                }            
            }
        }

        for (const auto& pipe: pipes) {
            window.draw(pipe.top);
            window.draw(pipe.bottom);
        }
        window.draw(Bird.bird);

        if (current_game_state == STATE_OVER) {
            drawGameOverScreen(window, font);
        }

        window.display();
    }
}
