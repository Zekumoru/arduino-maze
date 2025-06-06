#include "MiniMapScene.hpp"

#include "Input.hpp"
#include "Map.hpp"
#include "Player.hpp"

#ifndef IS_USING_SDL
#include "Adafruit_ILI9341.h"
#else
#include "libs/Adafruit_ILI9341.hpp"
#endif

extern Adafruit_ILI9341 tft;

extern Player player;
extern uint8_t miniMap[MAP_HEIGHT][MAP_WIDTH];

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

GameState MiniMapScene::processInput(const bool *buttonsState, const bool *buttonsJustPressed, float deltaTime)
{
  GameState newGamestate = GameState::MAP_VIEW;

  if (buttonsJustPressed[KEY_OPTION])
  {
    newGamestate = GameState::GAME_VIEW;
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

      switch (getMazeTile(y, x))
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
