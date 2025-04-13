#ifndef SCENE_HPP
#define SCENE_HPP

#include "../definitions.hpp"

class Scene
{
public:
  Scene() = default;
  virtual void render() = 0;
  virtual GameState processInput(const bool *buttonsState, const bool *buttonsJustPressed, float deltaTime) = 0;

protected:
  void clearScreen();
};

#endif // SCENE_HPP
