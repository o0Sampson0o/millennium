#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include <Particle.hpp>
#include <settings.hpp>
// #include <MemoryPool.hpp>

class QuadTree : public sf::Drawable
{
public:
    QuadTree(const sf::FloatRect &boundary,/*, MemoryPool<QuadTree> &pool*/ int capacity = MAX_CAPACITY);
    ~QuadTree();

    bool insert(Particle *particle);
    void clear();
    void query(const sf::FloatRect &range, std::vector<Particle *> &found);

    bool isDivided() const { return divided; }

    float getSize() const { return boundary.width; }
    QuadTree *getNW() const { return nw; }
    QuadTree *getNE() const { return ne; }
    QuadTree *getSW() const { return sw; }
    QuadTree *getSE() const { return se; }

    sf::Vector2f getCOM() const { return com; }
    float getTotalMass() const { return totalMass; }
    void applyForce(sf::Vector2f &force);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    void subdivide();
    bool contains(const sf::FloatRect &boundary, const Particle &particle);

    sf::Vector2f com{};
    float totalMass = 0.f;
    size_t size = 0;

    sf::FloatRect boundary;
    size_t capacity;
    std::array<Particle *, MAX_CAPACITY> particles{};
    bool divided = false;
    QuadTree *nw = nullptr;
    QuadTree *ne = nullptr;
    QuadTree *sw = nullptr;
    QuadTree *se = nullptr;
};