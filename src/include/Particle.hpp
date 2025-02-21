#pragma once

#include <SFML/Graphics.hpp>
#include <settings.hpp>

class Particle : public sf::Drawable
{
public:
    Particle(float x, float y, sf::Color color = sf::Color::White);
    ~Particle();
    void applyForce(sf::Vector2f force);
    void update(float dt);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Vector2f getPosition() const { return position; }
    sf::Vector2f getVelocity() const { return velocity; }
    sf::Vector2f getAcceleration() const { return acceleration; }
    float getMass() const { return mass; }

private:
    void handleWallCollision();

public:
    // debug info
    static int count;

private:
    float mass = PARTICLE_MASS;
    sf::CircleShape shape;
    sf::Color color;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
};