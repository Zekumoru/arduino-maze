#ifndef VEC2_H
#define VEC2_H

struct Vec2
{
  float x, y;

  Vec2();
  Vec2(float _x, float _y);
  Vec2(float value);
  Vec2(const Vec2 &vec);
  Vec2(const Vec2 &&vec) noexcept;
  Vec2(int _x, int _y);

  void operator=(const Vec2 &vec);
  void operator=(const Vec2 &&vec) noexcept;
  void operator=(const int value) = delete;
  void operator=(const float value) = delete;

  Vec2 operator+(const Vec2 &vec);
  Vec2 operator+(const int value);
  Vec2 operator+(const float value);

  Vec2 operator-(const Vec2 &vec);
  Vec2 operator-(const int value);
  Vec2 operator-(const float value);

  Vec2 operator*(const Vec2 &vec) = delete;
  Vec2 operator*(const int value);
  Vec2 operator*(const float value);

  Vec2 operator/(const Vec2 &vec) = delete;
  Vec2 operator/(float value);
  Vec2 operator/(const int value);
  friend Vec2 operator/(const Vec2 &vec, float value);

  static float dot(const Vec2 &left, const Vec2 &right);
  float lenght() const noexcept;
};

#endif // !VEC2_H