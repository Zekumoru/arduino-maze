#include "Player.hpp"

#include "../definitions.hpp"

extern float cosLT[];
extern float sinLT[];

Player::Player()
{
  m_angle = 90;
  m_baseDir = Vec2(cosLT[(int)m_angle], sinLT[(int)m_angle]);
  dir = Vec2(0.0f, 1.0f);
  m_baseCameraPlane = Vec2(m_fov / 100.0f, 0.0f);
  cameraPlane = m_baseCameraPlane;
}

Player::Player(Vec2 &&_pos)
{
  pos = _pos;
  m_angle = 90;
  m_baseDir = Vec2(cosLT[(int)m_angle], sinLT[(int)m_angle]);
  dir = Vec2(0.0f, 1.0f);
  m_baseCameraPlane = Vec2(m_fov / 100.0f, 0.0f);
  cameraPlane = m_baseCameraPlane;
}

Player::Player(const Vec2 &_pos)
{
  pos = _pos;
  m_angle = 90;
  m_baseDir = Vec2(cosLT[(int)m_angle], sinLT[(int)m_angle]);
  dir = Vec2(0.0f, 1.0f);
  m_baseCameraPlane = Vec2(m_fov / 100.0f, 0.0f);
  cameraPlane = m_baseCameraPlane;
}

void Player::movePlayer(float deltaTime)
{
  pos = pos + dir * moveSpeed * deltaTime;
}

void Player::moveX(float deltaTime)
{
  pos.x += moveSpeed * dir.x * deltaTime;
}

void Player::moveY(float deltaTime)
{
  pos.y += moveSpeed * dir.y * deltaTime;
}

void Player::rotate(float angle, float deltaTime)
{
  m_angle += (angle * rotateSpeed * deltaTime);

  if (m_angle >= 360)
    m_angle = m_angle - 360;
  if (m_angle < 0)
    m_angle = 360 + m_angle;

  dir.x = cosLT[(int)m_angle];
  dir.y = sinLT[(int)m_angle];

  rotateCamera();
}

void Player::rotateCamera()
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
