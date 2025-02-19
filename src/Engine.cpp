#include <settings.hpp>
#include <Engine.hpp>
#include <Particle.hpp>
#include <iostream>

Engine::Engine()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, WINDOW_STYLE)
{
    Particle *particle = new Particle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    particle->applyForce(sf::Vector2f(1.f, 1.f));
    particles.push_back(particle);
    std::cout << "Particle count: " << Particle::count << std::endl;
}

Engine::~Engine()
{
}

void Engine::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        update();
        render();
    }
}

void Engine::update()
{
    for (auto particle : particles)
    {
        particle->update(1.f);
    }
}

void Engine::render()
{
    window.clear(sf::Color::Black);
    for (auto particle : particles)
    {
        particle->update(0.1f);
        window.draw(*particle);
    }
    window.display();
}
