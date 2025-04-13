#ifndef LOADING_SCENE_HPP
#define LOADING_SCENE_HPP

#include "../definitions.hpp"
#include "../engine/Scene.hpp"
#include "../engine/Vec2.hpp"

class LoadingScene : public Scene
{
public:
  LoadingScene();
  virtual GameState processInput(float deltaTime) override;
  virtual void render() override;

private:
  // imageData Data; ???
  Vec2 textPos;
  const char *loadingText; // what? need to review string init in c LOL
};

#endif // LOADING_SCENE_HPP
