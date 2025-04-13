#include "GameScene.hpp"

#include "../definitions.hpp"
#include "../engine/Input.hpp"
#include "../engine/Player.hpp"
#include "../engine/Scene.hpp"
#include "../engine/Vec2.hpp"
#include "../libs/Adafruit_ILI9341.hpp"
#include "map.hpp"

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
  clearScreen();
  drawFloor();
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
      if (map[(int)player.pos.y][(int)player.pos.x] == END)
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
  if (!(map[(int)nextPos.y][(int)player.pos.x] == Tile::WALL ||
        map[(int)nextPos.y][(int)player.pos.x] == Tile::WALL_BLUE))
  {
    player.moveY(deltaTime);
  }

  if (!(map[(int)player.pos.y][(int)nextPos.x] == Tile::WALL ||
        map[(int)player.pos.y][(int)nextPos.x] == Tile::WALL_BLUE))
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

    deltaDist.x = (rayDir.x == 0.0f) ? 1e30f : std::abs(1 / rayDir.x);
    deltaDist.y = (rayDir.y == 0.0f) ? 1e30f : std::abs(1 / rayDir.y);

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

      if (map[mapY][mapX] != Tile::EMPTY && map[mapY][mapX] != Tile::END && !hit)
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
    switch (map[mapY][mapX])
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

void GameScene::drawVertLine(int x, int lenght, int color)
{
  int lineStartY = (SCREEN_HEIGHT - lenght) / 2;
  tft.drawFastVLine(x, lineStartY, lenght, color);
}
