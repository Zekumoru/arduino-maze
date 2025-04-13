#ifndef GAME_OVER_SCENE_HPP
#define GAME_OVER_SCENE_HPP

#include "../definitions.hpp"
#include "../engine/Scene.hpp"
#include "../engine/Vec2.hpp"

class GameOverScene : public Scene
{
public:
  GameOverScene();
  virtual void render() override;
  virtual GameState processInput(float deltaTime) override;

private:
  Vec2 m_gameOverTextPos;
  Vec2 m_ButtonPromptTextPos;
};

#endif // GAME_OVER_SCENE_HPP
