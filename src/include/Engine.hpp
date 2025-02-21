#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <QuadTree.hpp>
// forward declaration
class Particle;

class Engine
{
public:
    Engine();
    ~Engine();
    void run();

private:
    void update(sf::Time elapsed);
    void render();
    void calculateForces();

    // MemoryPool<QuadTree> quadTreePool;
    sf::RenderWindow window;
    sf::View camera;
    std::vector<Particle *> particles;
    QuadTree quadTree;
};