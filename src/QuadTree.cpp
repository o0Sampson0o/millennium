#include <QuadTree.hpp>
#include <Particle.hpp>
#include <SFML/Graphics.hpp>
#include <array>

float lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

float map(float value, float start1, float stop1, float start2, float stop2)
{
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}

QuadTree::QuadTree(const sf::FloatRect &boundary, /* MemoryPool<QuadTree> &pool,*/ int capacity)
    : boundary(boundary), capacity(capacity) /*, quadTreePool(pool)*/
{
}

QuadTree::~QuadTree()
{
    clear();
}

bool QuadTree::insert(Particle *particle)
{
    com = (particle->getMass() * particle->getPosition() + totalMass * com) / (totalMass + particle->getMass());
    totalMass += particle->getMass();
    if (!contains(boundary, *particle))
    {
        return false;
    }

    if (divided)
    {
        return nw->insert(particle) || ne->insert(particle) || sw->insert(particle) || se->insert(particle);
    }
    if (size < capacity)
    {
        particles[size] = particle;
        size++;
        return true;
    }

    size = 0;
    subdivide();
    for (auto p : particles)
    {
        nw->insert(p) || ne->insert(p) || sw->insert(p) || se->insert(p);
    }
    return true;
}

void QuadTree::clear()
{

    size = 0;
    if (!divided)
        return;

    nw->clear();
    ne->clear();
    sw->clear();
    se->clear();

    delete nw;
    delete ne;
    delete sw;
    delete se;

    /*
    quadTreePool.deallocate(nw);
    quadTreePool.deallocate(ne);
    quadTreePool.deallocate(sw);
    quadTreePool.deallocate(se);
    */

    nw = nullptr;
    ne = nullptr;
    sw = nullptr;
    se = nullptr;
    divided = false;
}

void QuadTree::query(const sf::FloatRect &range, std::vector<Particle *> &found)
{
    if (!boundary.intersects(range))
    {
        return;
    }

    for (const auto &point : particles)
    {
        if (range.contains(point->getPosition()))
        {
            found.push_back(point);
        }
    }

    if (nw == nullptr)
    {
        return;
    }

    nw->query(range, found);
    ne->query(range, found);
    sw->query(range, found);
    se->query(range, found);
}

void QuadTree::applyForce(sf::Vector2f &force)
{
    if (divided)
    {
        nw->applyForce(force);
        ne->applyForce(force);
        sw->applyForce(force);
        se->applyForce(force);
        return;
    }

    for (int i = 0; i < size; i++)
    {
        particles[i]->applyForce(force);
    }
}

void QuadTree::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (nw != nullptr)
    {
        nw->draw(target, states);
        ne->draw(target, states);
        sw->draw(target, states);
        se->draw(target, states);
        return;
    }

    sf::RectangleShape shape(sf::Vector2f(boundary.width, boundary.height));
    shape.setPosition(boundary.left, boundary.top);
    shape.setFillColor(sf::Color::Transparent);
    sf::Color color = sf::Color(0, 255, 0, 50);
    shape.setOutlineColor(color);
    shape.setOutlineThickness(1.f);
    target.draw(shape, states);
}

void QuadTree::subdivide()
{
    const float x = boundary.left;
    const float y = boundary.top;
    const float w = boundary.width / 2.f;
    const float h = boundary.height / 2.f;

    sf::FloatRect nwBoundary(x, y, w, h);
    sf::FloatRect neBoundary(x + w, y, w, h);
    sf::FloatRect swBoundary(x, y + h, w, h);
    sf::FloatRect seBoundary(x + w, y + h, w, h);

    nw = new QuadTree(nwBoundary, capacity);
    ne = new QuadTree(neBoundary, capacity);
    sw = new QuadTree(swBoundary, capacity);
    se = new QuadTree(seBoundary, capacity);

    /*
    nw = quadTreePool.allocate(nwBoundary, quadTreePool, capacity);
    ne = quadTreePool.allocate(neBoundary, quadTreePool, capacity);
    sw = quadTreePool.allocate(swBoundary, quadTreePool, capacity);
    se = quadTreePool.allocate(seBoundary, quadTreePool, capacity);
    */
    divided = true;
}

bool QuadTree::contains(const sf::FloatRect &boundary, const Particle &particle)
{
    return boundary.contains(particle.getPosition());
}