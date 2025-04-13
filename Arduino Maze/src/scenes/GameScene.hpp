#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "../definitions.hpp"
#include "../engine/Scene.hpp"
#include "../engine/Vec2.hpp"

class GameScene : public Scene
{
public:
  GameScene();
  virtual void render() override;
  virtual GameState processInput(float deltaTime) override;

private:
  void movePlayer(Vec2 &nextPos, float deltaTime);
  void rayCasting();
  void drawFloor();
  void drawVertLine(int x, int lenght, int color);
};

#endif // GAME_SCENE_HPP
