#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../SDL.h"
#include "vec2.hpp"
#include <cmath>

extern float cosLT[];
extern float sinLT[];

class Player
{
public:
  Player()
  {
    m_angle = 90;
    m_fov = 75.0f;
    m_baseDir = vec2(0.0f, 1.0f);
    dir = vec2(0.0f, 1.0f);
    m_baseCameraPlane = vec2(m_fov / 100.0f, 0.0f);
    cameraPlane = m_baseCameraPlane;
  }

  Player(vec2 &&_pos)
  {
    pos = _pos;
    m_angle = 90;
    m_fov = 75.0f;
    m_baseDir = vec2(0.0f, 1.0f);
    dir = vec2(0.0f, 1.0f);
    m_baseCameraPlane = vec2(m_fov / 100.0f, 0.0f);
    cameraPlane = m_baseCameraPlane;
  }

  void movePlayer(float distance)
  {
    float deltaTime = 0.0007f;
    pos.x += distance * dir.x * deltaTime;
    pos.y += distance * dir.y * deltaTime;
  };

  void rotate(int angle)
  {
    m_angle = abs((m_angle + angle) % 360);

    dir.x = cosLT[m_angle];
    dir.y = sinLT[m_angle];

    rotateCamera();
  }

  vec2 pos;
  vec2 dir;
  vec2 cameraPlane;

private:
  int m_angle;
  vec2 m_baseDir;
  vec2 m_baseCameraPlane;

  float m_fov; // need to choose witch one to use

  void rotateCamera()
  {
    int angle = abs((m_angle - 90) % 360);

    cameraPlane.x = m_baseCameraPlane.x * cosLT[angle] - sinLT[angle] * cameraPlane.y; 
    cameraPlane.y = m_baseCameraPlane.x * sinLT[angle] + cosLT[angle] * cameraPlane.y;
  }
};

#endif // !PLAYER_HPP
