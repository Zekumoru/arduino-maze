#ifndef MINI_MAP_SCENE_HPP
#define MINI_MAP_SCENE_HPP

#include "../definitions.hpp"
#include "../engine/Scene.hpp"

class MiniMapScene : public Scene
{
public:
  MiniMapScene();
  virtual void render() override;
  virtual GameState processInput(float deltaTime) override;

private:
  int playerSizeMiniMap; // still not sure about this, i wanted to use an
                         // odd lenght square, but cell size is even FML
  void renderMiniMap();
  void drawCell(int x, int y, int color);
  void renderPlayer();
  void renderPlayerDir(int x, int y);
};

#endif // MINI_MAP_SCENE_HPP
