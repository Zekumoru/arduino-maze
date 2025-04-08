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
    m_fov = 65.0f;
    m_baseDir = vec2(cosLT[(int)m_angle], sinLT[(int)m_angle]);
    dir = vec2(0.0f, 1.0f);
    m_baseCameraPlane = vec2(m_fov / 100.0f, 0.0f);
    cameraPlane = m_baseCameraPlane;
  }

  Player(vec2 &&_pos)
  {
    pos = _pos;
    m_angle = 90;
    m_fov = 65.0f;
    m_baseDir = vec2(cosLT[(int)m_angle], sinLT[(int)m_angle]);
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

  void rotate(float angle)
  {
    m_angle += angle;

    if (m_angle >= 360)
      m_angle = m_angle - 360;
    if (m_angle < 0)
      m_angle = 360 + angle;

    dir.x = cosLT[(int)m_angle];
    dir.y = sinLT[(int)m_angle];

    rotateCamera();
  }

  vec2 pos;
  vec2 dir;
  vec2 cameraPlane;

private:
  float m_angle;
  vec2 m_baseDir;
  vec2 m_baseCameraPlane;

  float m_fov; // need to choose witch one to use

  void rotateCamera()
  {
    float angle = m_angle - 90;

    if (angle >= 360)
      angle = angle - 360;
    if (angle < 0)
      angle = 360 + angle;


    cameraPlane.x = m_baseCameraPlane.x * cosLT[(int)angle] -
                    sinLT[(int)angle] * m_baseCameraPlane.y; 
    cameraPlane.y = m_baseCameraPlane.x * sinLT[(int)angle] +
                    cosLT[(int)angle] * m_baseCameraPlane.y;
  }
};

#endif // !PLAYER_HPP
