#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../SDL.h"
#include "vec2.hpp"

extern float cosLT[];
extern float sinLT[];

class Player
{
public:
  Player()
  {
    m_angle = 90;
    m_fov = 75.0f;
    dir = vec2(0.0f, 1.0f);
    cameraPlane = vec2(m_fov / 100.0f, 0.0f);
  }

  Player(vec2 &&_pos)
  {
    m_angle = 90;
    pos = _pos;
    m_fov = 75.0f;
    dir = vec2(0.0f, 1.0f);
    cameraPlane = vec2(m_fov / 100.0f, 0.0f);
  }

  void movePlayer(float distance)
  {
    float deltaTime = 0.0007f;
    pos.x += distance * dir.x * deltaTime;
    pos.y += distance * dir.y * deltaTime;
  };

  void rotate(int angle)
  {
    m_angle += angle;
    m_angle %= 360;

    dir.x = cosLT[m_angle];
    dir.y = sinLT[m_angle];

    rotateCamera();
  }

  vec2 pos;
  vec2 dir;
  vec2 cameraPlane;

private:
  int m_angle;

  float m_fov; // need to choose witch one to use

  void rotateCamera()
  {
    int angle = m_angle - 90;

    cameraPlane.x = cameraPlane.x * cosLT[angle] - sinLT[angle] * cameraPlane.y;
    cameraPlane.y = cameraPlane.x * sinLT[angle] + cosLT[angle] * cameraPlane.y;
  }
};

#endif // !PLAYER_HPP
