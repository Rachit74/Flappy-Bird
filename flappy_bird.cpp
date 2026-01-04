#include <SFML/Graphics.hpp>

// check window border hit
void checkBorderHit(sf::CircleShape& Bird) {
    float radius = Bird.getRadius();
    float diameter = radius * 2;

    sf::Vector2f birdPosition = Bird.getPosition();

    if (birdPosition.y < 0) {
        birdPosition.y = 0;
        Bird.setPosition(birdPosition);
    }

    if (birdPosition.y > 600-diameter) {
        birdPosition.y = 600-diameter;
        Bird.setPosition(birdPosition);
    }
}

int main() {

    sf::RenderWindow window(sf::VideoMode(800,600), "Flappy bird c++");

    // Clock to measure time between frames (deltaTime)
    sf::Clock clock;

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
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            velocity = -350.f;
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

        window.clear();
        window.draw(Bird);
        window.display();
    }
}
