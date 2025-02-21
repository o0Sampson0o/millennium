#include <Engine.hpp>
#include <settings.hpp>
#include <Particle.hpp>
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <stack>
#include <Logger.hpp>
#include <cmath>

float magnitude(const sf::Vector2f &v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

Engine::Engine()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, WINDOW_STYLE),
      camera({CAMERA_INITIAL_OFFSET_X, CAMERA_INITIAL_OFFSET_Y}, {WINDOW_WIDTH, WINDOW_HEIGHT}),
      quadTree({0.f, 0.f, UNIVERSE_SIZE, UNIVERSE_SIZE}) /*, quadTreePool),
     quadTreePool(PARTICLE_COUNT * 100) */
{
    srand(static_cast<unsigned int>(time(NULL)));
    // set camera
    camera.zoom(CAMERA_INITIAL_ZOOM);
    window.setView(camera);

    // create particles
    particles.reserve(PARTICLE_COUNT);

    for (int i = 0; i < PARTICLE_COUNT; i++)
    {
        const float randPosX = static_cast<float>(rand() % static_cast<int>(UNIVERSE_SIZE));
        const float randPosY = static_cast<float>(rand() % static_cast<int>(UNIVERSE_SIZE));
        const float randAccX = static_cast<float>(rand() % 100) / 2.f - 25.f;
        const float randAccY = static_cast<float>(rand() % 100) / 2.f - 25.f;
        Particle *particle = new Particle(randPosX, randPosY);
        particles.push_back(particle);
        particle->applyForce(sf::Vector2f(randAccX, randAccY));

        quadTree.insert(particle);
    }
    particles[0]->applyForce(sf::Vector2f(800.f * 2, 200.f * 2));
    std::cout << "Particle count: " << Particle::count << std::endl;
}

Engine::~Engine()
{
}

void Engine::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time elapsed = clock.restart();
        update(elapsed);
        render();
        Logger::debug("FPS: " + std::to_string(1.f / elapsed.asSeconds()));
    }
}

void Engine::update(sf::Time elapsed)
{
    quadTree.clear();
    for (auto particle : particles)
    {
        particle->update(elapsed.asSeconds());
    }
    for (auto particle : particles)
    {
        quadTree.insert(particle);
    }
    calculateForces();
}

void Engine::render()
{
    window.clear(sf::Color::Black);
    for (auto particle : particles)
    {
        particle->update(0.1f);
        window.draw(*particle);
    }
    window.draw(quadTree);
    window.display();
}

void Engine::calculateForces()
{

    for (auto particle : particles)
    {
        std::stack<QuadTree *> stack;
        stack.push(&quadTree);
        while (!stack.empty())
        {
            QuadTree *current = stack.top();
            stack.pop();

            sf::Vector2f displacement = particle->getPosition() - current->getCOM();
            const float distance = magnitude(displacement);

            if (distance == 0.f)
                continue;

            const float theta = current->getSize() / distance;
            if (theta <= THETA || !current->isDivided())
            {
                sf::Vector2f direction = displacement / distance;
                float forceMagnitude = (G * particle->getMass() * current->getTotalMass() / ((distance + EPSILON) * (distance + EPSILON)));
                sf::Vector2f force = direction * forceMagnitude;
                current->applyForce(force);
            }
            else
            {
                stack.push(current->getNW());
                stack.push(current->getNE());
                stack.push(current->getSW());
                stack.push(current->getSE());
            }
        }
    }
}
