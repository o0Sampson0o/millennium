#include <SFML/Graphics.hpp>
#include <vector>
// forward declaration
class Particle;

class Engine
{
public:
    Engine();
    ~Engine();
    void run();

private:
    void update();
    void render();

    std::vector<Particle *> particles;
    sf::RenderWindow window;
};