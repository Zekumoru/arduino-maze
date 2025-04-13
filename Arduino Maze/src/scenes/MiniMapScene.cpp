#include "MiniMapScene.hpp"

#include "../definitions.hpp"
#include "../engine/Input.hpp"
#include "../engine/Player.hpp"
#include "../engine/Scene.hpp"
#include "../libs/Adafruit_ILI9341.hpp"
#include "map.hpp"

extern Adafruit_ILI9341 tft;

extern Player player;
extern int map[MAP_HEIGHT][MAP_WIDTH];
extern int miniMap[MAP_HEIGHT][MAP_WIDTH];

MiniMapScene::MiniMapScene() : playerSizeMiniMap(4)
{
  resetMiniMap();
}

void MiniMapScene::render()
{
  clearScreen();
  renderMiniMap();
  renderPlayer();
}

GameState MiniMapScene::processInput(float deltaTime)
{
  // TODO: Perhaps to swap GAME_VIEW and MAP_VIEW?
  GameState newGamestate = GameState::GAME_VIEW;

  const bool *buttonsState = getButtonsState();
  if (buttonsState[KEY_OPTION])
  {
    newGamestate = GameState::MAP_VIEW;
  }

  return newGamestate;
}

void MiniMapScene::renderMiniMap()
{
  int color = 0;
  for (int y = 0; y < MAP_HEIGHT; y++)
  {
    for (int x = 0; x < MAP_WIDTH; x++)
    {
      if (!miniMap[y][x])
        continue;

      switch (map[y][x])
      {
      case Tile::EMPTY:
        color = COL_DARKGREY;
        break;
      case Tile::WALL:
      case Tile::WALL_BLUE:
        color = COL_WHITE;
        break;
      case Tile::END:
        color = COL_BLUE;
        break;
      default:
        color = COL_MAGENTA;
        break;
      }
      drawCell(x, y, color);
    }
  }
}

void MiniMapScene::drawCell(int x, int y, int color)
{
  int xPos = x * CELL_SIZE;
  int yPos = y * CELL_SIZE;
  int sideLength = CELL_SIZE - 2;
  tft.fillRect(xPos + 1, yPos + 1, sideLength, sideLength, color);
}

void MiniMapScene::renderPlayer()
{
  int posX = (int)player.pos.x * CELL_SIZE;
  int posY = (int)player.pos.y * CELL_SIZE;
  tft.fillRect(posX + 3, posY + 3, playerSizeMiniMap, playerSizeMiniMap, COL_GREEN); // to be tested
  renderPlayerDir(posX, posY);
}

void MiniMapScene::renderPlayerDir(int x, int y)
{
  int posX = (int)((x + CELL_SIZE / 2) + 3 * player.dir.x);
  int posY = (int)((y + CELL_SIZE / 2) + 3 * player.dir.y);
  tft.drawPixel(posX, posY, COL_GREEN);
}
