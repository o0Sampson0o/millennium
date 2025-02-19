#include <SFML/Graphics.hpp>

class Engine
{
public:
    Engine();
    ~Engine();
    void run();

private:
    void update();
    void render();
    sf::RenderWindow window;
};