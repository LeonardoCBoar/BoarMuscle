#pragma once

// built in
#include <cstdint>
#include <math.h>
#include <iostream>

namespace BMuscle 
{
    template <typename NumberT>
    class Vector2
    {
    public:
        NumberT x;
        NumberT y;
    public:
        Vector2(const NumberT x=0, const NumberT y=0)
            : x{x}, y{y}
            {

            }

        Vector2<NumberT> operator+(const Vector2<NumberT> other) const
        {
            return Vector2<NumberT>
            {
                this->x + other.x,
                this->y + other.y
            };
        }

        template<class OtherNumberT>
        Vector2<NumberT> operator-(const Vector2<OtherNumberT> other) const
        {
            return Vector2<NumberT>
            {
                this->x - other.x,
                this->y - other.y
            };
        }

        Vector2<NumberT> operator*(const Vector2<NumberT> other) const
        {
            return Vector2<NumberT>
            {
                this->x * other.x,
                this->y * other.y
            };
        }

        Vector2<NumberT> operator*(const NumberT number) const
        {
            return Vector2<NumberT>
            {
                this->x * number,
                this->y * number
            };
        }

        Vector2<NumberT> operator/(const Vector2<NumberT> other) const
        {
            return Vector2<NumberT>
            {
                this->x / other.x,
                this->y / other.y
            };
        }
        
        Vector2<NumberT> operator/(NumberT divisor) const
        {
            return Vector2<NumberT>
            {
                this->x / divisor,
                this->y / divisor
            };
        }

        double length() const
        {
            return sqrt( (this->x*this->x) + (this->y*this->y) );
        }

        template<class OtherNumberT>
        double distance_to(const Vector2<OtherNumberT> other) const
        {
            return (*this - other).length();
        }

        Vector2<NumberT> normalized() const
        {
            return (*this)/this->length();
        }

        bool inside_rect(const Vector2<NumberT> origin, const Vector2<NumberT> size) const
        {
            if(this->x < origin.x || this->y < origin.y) return false;
            if(this->x > origin.x + size.x || this->y > origin.y + size.y) return false;
            return true;
        }

    };

    typedef Vector2<double> Vector2d;
    typedef Vector2<float>  Vector2f;
    typedef Vector2<int32_t> Vector2i32;
    typedef Vector2<uint32_t> Vector2u32;
    
    template<class NumberT>
    std::ostream& operator <<(std::ostream& ostream, const Vector2<NumberT>& vector)
    {
        return ostream << '(' << vector.x << ',' << vector.y << ')';
    }
}