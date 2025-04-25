#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Vec2.hpp"

class Player
{
public:
  Player();
  Player(Vec2 &&_pos);
  Player(const Vec2 &_pos);

  // DEPRECATED: it doesn't check for collision, and if you do and call this
  // player can get stuck in walls. If we make player aware of the map,
  // we can use it though.
  void movePlayer(float deltaTime);
  void moveX(float deltaTime);
  void moveY(float deltaTime);
  void rotate(float angle, float deltaTime);

  Vec2 pos;
  Vec2 dir;
  Vec2 cameraPlane;
  float moveSpeed = 1.5f;
  float rotateSpeed = 1.5f;

private:
  float m_angle;
  Vec2 m_baseDir;
  Vec2 m_baseCameraPlane;
  float m_fov = 65.0f;

  void rotateCamera();
};

#endif // PLAYER_HPP
