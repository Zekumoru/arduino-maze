#include "vec2.hpp"
#include <cmath>

vec2::vec2() : x(0), y(0) { }

vec2::vec2(float _x, float _y) : x(_x), y(_y) { }

vec2::vec2(float value) : x(value), y(value) { }

vec2::vec2(const vec2 &vec) : x(vec.x), y(vec.y) { }

vec2::vec2(const vec2 &&vec) : x(vec.x), y(vec.y) { }

vec2::vec2(int _x, int _y) : x((float)_x), y((float)_y) { }

void vec2::operator=(const vec2 &vec)
{
    x = vec.x;
    y = vec.y;
}

void vec2::operator=(const vec2&& vec)
{
    x = vec.x;
    y = vec.y;
}

vec2 vec2::operator+(const vec2 &vec)
{
    return vec2(x + vec.x, y + vec.y);
}

vec2 vec2::operator+(const int value)
{
    return vec2(x + (float)value, y + (float)value);
}

vec2 vec2::operator+(const float value)
{
    return vec2(x + value, y + value);
}

vec2 vec2::operator-(const vec2& vec)
{
    return vec2(x - vec.x, y - vec.y);
}

vec2 vec2::operator-(const int value)
{
    return vec2(x - (float)value, y - (float)value);
}

vec2 vec2::operator-(const float value)
{
    return vec2(x - value, y - value);
}

vec2 vec2::operator*(const int value)
{
    return vec2(x * (float)value, y * (float)value);
}

vec2 vec2::operator*(const float value)
{
    return vec2(x * value, y * value);
}

vec2 vec2::operator/(float value)
{
    return vec2(x / value, y / value);
}

vec2 vec2::operator/(const int value)
{
    return vec2(x / (float)value, y / (float)value);
}

float vec2::dot(const vec2 &left, const vec2 &right)
{
    float leftLengt = sqrt(left.x * left.x + left.y * left.y);
    float rightLength = sqrt(right.x * right.x + right.y * right.y);

    vec2 unitLeft = left / leftLengt;
    vec2 unitRight = right / rightLength;

    return unitLeft.x * unitRight.x + unitLeft.y * unitRight.y;
}

vec2 operator/(const vec2 &vec, float value)
{
    return vec2(vec.x / value, vec.y / value);
}
