#include "collisions.hpp"

// builtin
#include <iostream>
#include <optional>

// local
#include "geometry.hpp"

using namespace BMuscle;
using namespace BMuscle::Collisions;

std::optional<CollisionData> BMuscle::Collisions::collides(const Circle& circle_a, const Circle& circle_b)
{
    const double distance = circle_a.center.distance_to(circle_b.center);

    const double minimum_collision_dist = circle_a.radius + circle_b.radius;

    if(distance <  minimum_collision_dist)
    {
        CollisionData data{};
        data.depth = minimum_collision_dist - distance + 0.1;
        data.direction = (circle_b.center - circle_a.center).normalized();
        return std::optional<CollisionData>{data};
    }

    return std::nullopt;


}
