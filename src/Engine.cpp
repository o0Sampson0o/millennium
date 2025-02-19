#include "settings.hpp"
#include "Engine.hpp"

Engine::Engine()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, WINDOW_STYLE)
{
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
    }
    update();
    render();
}

void Engine::update()
{
}

void Engine::render()
{
    window.clear();
    window.display();
}
