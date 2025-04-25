#include "Vec2.hpp"
#include <cmath>

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float _x, float _y) : x(_x), y(_y) {}

Vec2::Vec2(float value) : x(value), y(value) {}

Vec2::Vec2(const Vec2 &vec) : x(vec.x), y(vec.y) {}

Vec2::Vec2(const Vec2 &&vec) noexcept : x(vec.x), y(vec.y) {}

Vec2::Vec2(int _x, int _y) : x((float)_x), y((float)_y) {}

void Vec2::operator=(const Vec2 &vec)
{
  x = vec.x;
  y = vec.y;
}

void Vec2::operator=(const Vec2 &&vec) noexcept
{
  x = vec.x;
  y = vec.y;
}

Vec2 Vec2::operator+(const Vec2 &vec) { return Vec2(x + vec.x, y + vec.y); }

Vec2 Vec2::operator+(const int value)
{
  return Vec2(x + (float)value, y + (float)value);
}

Vec2 Vec2::operator+(const float value) { return Vec2(x + value, y + value); }

Vec2 Vec2::operator-(const Vec2 &vec) { return Vec2(x - vec.x, y - vec.y); }

Vec2 Vec2::operator-(const int value)
{
  return Vec2(x - (float)value, y - (float)value);
}

Vec2 Vec2::operator-(const float value) { return Vec2(x - value, y - value); }

Vec2 Vec2::operator*(const int value)
{
  return Vec2(x * (float)value, y * (float)value);
}

Vec2 Vec2::operator*(const float value) { return Vec2(x * value, y * value); }

Vec2 Vec2::operator/(float value) { return Vec2(x / value, y / value); }

Vec2 Vec2::operator/(const int value)
{
  return Vec2(x / (float)value, y / (float)value);
}

float Vec2::dot(const Vec2 &left, const Vec2 &right)
{
  Vec2 unitLeft = left / left.lenght();
  Vec2 unitRight = right / right.lenght();

  return unitLeft.x * unitRight.x + unitLeft.y * unitRight.y;
}

float Vec2::lenght() const noexcept
{
  return sqrtf(x*x + y*y);
}

Vec2 operator/(const Vec2 &vec, float value)
{
  return Vec2(vec.x / value, vec.y / value);
}
