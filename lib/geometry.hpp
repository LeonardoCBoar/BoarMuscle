#pragma once

// local
#include "vector.hpp"

namespace BMuscle 
{
    struct Circle
    {
        BMuscle::Vector2d center{0,0};
        double radius = 0;

        Circle(const BMuscle::Vector2d center, const double radius)
            :center{center}, radius{radius}
            {
                
            }
    };

}