#include <SFML/Graphics.hpp>

class Particle : public sf::Drawable
{
public:
    Particle(float x, float y, sf::Color color = sf::Color::White);
    ~Particle();
    void applyForce(sf::Vector2f force);
    void update(float dt);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    // debug info
    static int count;

private:
    sf::CircleShape shape;
    sf::Color color;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
};