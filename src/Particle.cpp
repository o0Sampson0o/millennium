#include <Particle.hpp>
#include <settings.hpp>
#include <Logger.hpp>

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

    if (position.x < 0 || position.x > WINDOW_WIDTH)
    {
        Logger::debug("Particle hit the wall");
        velocity.x = -velocity.x;
        position.x = std::max(0.f, std::min(position.x, static_cast<float>(WINDOW_WIDTH)));
    }

    if (position.y < 0 || position.y > WINDOW_HEIGHT)
    {
        Logger::debug("Particle hit the wall");
        velocity.y = -velocity.y;
        position.y = std::max(0.f, std::min(position.y, static_cast<float>(WINDOW_HEIGHT)));
    }
}

void Particle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape, states);
}
