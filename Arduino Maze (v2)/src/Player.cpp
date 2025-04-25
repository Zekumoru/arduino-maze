#include "Player.hpp"

#include "definitions.hpp"

Player::Player()
{
  m_angle = 90;
  m_baseDir = Vec2(fastCos(m_angle), fastSin(m_angle));
  dir = Vec2(0.0f, 1.0f);
  m_baseCameraPlane = Vec2(m_fov / 100.0f, 0.0f);
  cameraPlane = m_baseCameraPlane;
}

Player::Player(Vec2 &&_pos)
{
  pos = _pos;
  m_angle = 90;
  m_baseDir = Vec2(fastCos(m_angle), fastSin(m_angle));
  dir = Vec2(0.0f, 1.0f);
  m_baseCameraPlane = Vec2(m_fov / 100.0f, 0.0f);
  cameraPlane = m_baseCameraPlane;
}

Player::Player(const Vec2 &_pos)
{
  pos = _pos;
  m_angle = 90;
  m_baseDir = Vec2(fastCos(m_angle), fastSin(m_angle));
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

  dir.x = fastCos(m_angle);
  dir.y = fastSin(m_angle);

  rotateCamera();
}

void Player::rotateCamera()
{
  float angle = m_angle - 90;

  if (angle >= 360)
    angle = angle - 360;
  if (angle < 0)
    angle = 360 + angle;

  cameraPlane.x = m_baseCameraPlane.x * fastCos(angle) -
                  fastSin(angle) * m_baseCameraPlane.y;
  cameraPlane.y = m_baseCameraPlane.x * fastSin(angle) +
                  fastCos(angle) * m_baseCameraPlane.y;
}
