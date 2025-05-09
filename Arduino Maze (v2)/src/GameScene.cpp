#include "GameScene.hpp"

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
extern Vec2 playerStartPos;

GameScene::GameScene()
{
  player.pos = playerStartPos;
  setMiniMap((int)player.pos.x, (int)player.pos.y);
}

void GameScene::render()
{
#ifdef IS_USING_SDL
  // These two will be replaced since they're slow and create a wobbling effect in Arduino:
  clearScreen();
  drawFloor();
#endif

  rayCasting();
}

GameState GameScene::processInput(const bool *buttonsState, const bool *buttonsJustPressed, float deltaTime)
{
  GameState newState = GameState::GAME_VIEW;

  if (buttonsState[KEY_UP])
  {
    Vec2 predictedPos = player.pos + player.dir;

    if (((int)predictedPos.x < MAP_WIDTH && (int)predictedPos.y < MAP_HEIGHT) &&
        ((int)predictedPos.x >= 0 && (int)predictedPos.y >= 0))
    {
      movePlayer(predictedPos, deltaTime);
      if (getMazeTile(player.pos.y, player.pos.x) == END)
      {
        newState = GameState::GAME_OVER;
      }
      else
      {
        unlockMiniMapArea((int)player.pos.x, (int)player.pos.y);
      }
    }
  }

  if (buttonsState[KEY_LEFT])
  {
    player.rotate(-90, deltaTime);
  }

  if (buttonsState[KEY_RIGHT])
  {
    player.rotate(90, deltaTime);
  }

  if (buttonsJustPressed[KEY_OPTION])
  {
    newState = GameState::MAP_VIEW;
  }

  return newState;
}

void GameScene::movePlayer(Vec2 &nextPos, float deltaTime)
{
  if (!(getMazeTile((int)nextPos.y, (int)player.pos.x) == Tile::WALL ||
        getMazeTile((int)nextPos.y, (int)player.pos.x) == Tile::WALL_BLUE))
  {
    player.moveY(deltaTime);
  }

  if (!(getMazeTile(player.pos.y, (int)nextPos.x) == Tile::WALL ||
        getMazeTile(player.pos.y, (int)nextPos.x) == Tile::WALL_BLUE))
  {
    player.moveX(deltaTime);
  }
}

void GameScene::rayCasting()
{
  Vec2 rayDir;

  for (int x = 0; x < SCREEN_WIDTH; x++)
  {
    float cameraX = 2.0f * x / (float)SCREEN_WIDTH - 1;
    rayDir.x = player.dir.x + player.cameraPlane.x * cameraX;
    rayDir.y = player.dir.y + player.cameraPlane.y * cameraX;

    int mapX = (int)player.pos.x;
    int mapY = (int)player.pos.y;

    Vec2 sideDist;
    Vec2 deltaDist;
    float perpDist;

    deltaDist.x = (rayDir.x == 0.0f) ? 1e30f : (float)fabs(1 / rayDir.x);
    deltaDist.y = (rayDir.y == 0.0f) ? 1e30f : (float)fabs(1 / rayDir.y);

    int stepY;
    int stepX;

    bool hit = false;
    int side;

    if (rayDir.x < 0)
    {
      stepX = -1;
      sideDist.x = (player.pos.x - mapX) * deltaDist.x;
    }
    else
    {
      stepX = 1;
      sideDist.x = (mapX + 1.0f - player.pos.x) * deltaDist.x;
    }

    if (rayDir.y < 0)
    {
      stepY = -1;
      sideDist.y = (player.pos.y - mapY) * deltaDist.y;
    }
    else
    {
      stepY = 1;
      sideDist.y = (mapY + 1.0f - player.pos.y) * deltaDist.y;
    }

    while (!hit)
    {
      if (sideDist.x < sideDist.y)
      {
        sideDist.x += deltaDist.x;
        mapX += stepX;
        side = 0;
      }
      else
      {
        sideDist.y += deltaDist.y;
        mapY += stepY;
        side = 1;
      }

      if (mapY >= MAP_HEIGHT)
      {
        mapY = MAP_HEIGHT - 1;
        sideDist.y = 1e10;
        hit = true;
      }
      else if (mapY < 0)
      {
        mapY = 0;
        sideDist.y = 1e10;
        hit = true;
      }

      if (mapX >= MAP_WIDTH)
      {
        mapX = MAP_WIDTH - 1;
        sideDist.x = 1e10;
        hit = true;
      }
      else if (mapX < 0)
      {
        mapX = 0;
        sideDist.x = 1e10;
        hit = true;
      }

      if (getMazeTile(mapY, mapX) != Tile::EMPTY && getMazeTile(mapY, mapX) != Tile::END && !hit)
      {
        hit = true;
      }
    }

    if (!side)
    {
      perpDist = sideDist.x - deltaDist.x;
    }
    else
    {
      perpDist = sideDist.y - deltaDist.y;
    }

    int lineHeight = (int)(SCREEN_HEIGHT / perpDist);

    if (lineHeight > MAX_LINE_LEN)
    {
      lineHeight = MAX_LINE_LEN;
    }

    int color = 0;
    switch (getMazeTile(mapY, mapX))
    {
    case 1:
      if (side)
        color = COL_YELLOW;
      else
        color = COL_ORANGE;
      break;
    case 2:
      color = COL_BLUE;
      break;
    default:
      break;
    }

    drawVertLine(SCREEN_WIDTH - 1 - x, lineHeight, color);
  }
}

void GameScene::drawFloor()
{
  tft.fillRect(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, COL_GREY);
}

void GameScene::drawVertLine(int x, int length, int color)
{
  int lineStartY = (SCREEN_HEIGHT - length) / 2;

#ifdef IS_USING_SDL
  // This will be replaced in Arduino since it's slow, creating 6 operations Assembly-wise.
  tft.drawFastVLine(x, lineStartY, length, color);
#else
  tft.drawFastVLine(x, 0, lineStartY - 1, COL_BLACK);                                // draw black bg
  tft.drawFastVLine(x, lineStartY, length, color);                                   // draw vert line
  tft.drawFastVLine(x, lineStartY + length, (SCREEN_HEIGHT - length) / 2, COL_GREY); // draw floor
#endif
}
