#include <Particle.hpp>
#include <settings.hpp>
#include <Logger.hpp>
#include <cmath>

int Particle::count = 0;

Particle::Particle(float x, float y, sf::Color color)
    : position(x, y), velocity(0.f, 0.f), acceleration(0.f, 0.f)
{
    shape.setRadius(PARTICLE_RADIUS);
    shape.setFillColor(color);
    shape.setOrigin(PARTICLE_RADIUS, PARTICLE_RADIUS);
    shape.setPosition(x, y);

    this->color = color;

    count++;
}

Particle::~Particle()
{
}

void Particle::applyForce(sf::Vector2f force)
{
    acceleration += force / PARTICLE_MASS;
}

void Particle::update(float dt)
{
    velocity += acceleration * dt;
    position += velocity * dt;
    shape.setPosition(position);

    acceleration = sf::Vector2f(0.f, 0.f);

    handleWallCollision();
}

void Particle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape, states);
}

// periodic boundary conditions
void Particle::handleWallCollision()
{
    if (position.x < 0)
        position.x += UNIVERSE_SIZE;
    else if (position.x > UNIVERSE_SIZE)
        position.x -= UNIVERSE_SIZE;

    if (position.y < 0)
        position.y += UNIVERSE_SIZE;
    else if (position.y > UNIVERSE_SIZE)
        position.y -= UNIVERSE_SIZE;
}
