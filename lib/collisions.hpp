#pragma once

// builtin
#include <optional>

// local
#include "vector.hpp"

// forward declarations
namespace BMuscle
{
    struct Circle;
}



namespace BMuscle::Collisions
{
    struct CollisionData
    {
        double depth = 0;
        Vector2d direction{};
    };

    std::optional<CollisionData> collides(const Circle& circle_a, const Circle& circle_b);
}