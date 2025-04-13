#ifndef MAIN_MENU_SCENE_HPP
#define MAIN_MENU_SCENE_HPP

#include "../definitions.hpp"
#include "../engine/Scene.hpp"
#include "../engine/Vec2.hpp"

class MainMenuScene : public Scene
{
public:
  MainMenuScene();
  virtual void render() override;
  virtual GameState processInput(const bool *buttonsState, const bool *buttonsJustPressed, float deltaTime) override;

private:
  Vec2 m_TextPos;
};

#endif // MAIN_MENU_SCENE_HPP
