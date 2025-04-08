/**
 * @brief contains scenes and map data, also function for map manipulatioins and
 * player instance
 *
 */

#ifndef SCENES_HPP
#define SCENES_HPP

#include "../Adafruit_ILI9341.h"
#include "../SDL.h"
#include "defines.hpp"
#include "player.hpp"
#include "vec2.hpp"

#define IS_USING_SDL true

extern Adafruit_ILI9341 tft;

// mapdata
//!!! Will probably opt for a one dim array (map[HEIGHT*WIDTH] for better
//! access(?) to memory)
int map[MAP_HEIGHT][MAP_WIDTH] = {
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

int miniMap[MAP_HEIGHT][MAP_WIDTH];

// minimap utils
void resetMiniMap()
{
  for (int y = 0; y < MAP_HEIGHT; y++)
    for (int x = 0; x < MAP_WIDTH; x++)
      miniMap[y][x] = 0;
}

void unlockMiniMapArea(int xPos, int yPos)
{
  // top row
  miniMap[yPos - 1][xPos - 1] = 1;
  miniMap[yPos - 1][xPos] = 1;
  miniMap[yPos - 1][xPos + 1] = 1;
  // midlle row
  miniMap[yPos][xPos - 1] = 1;
  miniMap[yPos][xPos + 1] = 1;
  // bottom row
  miniMap[yPos + 1][xPos - 1] = 1;
  miniMap[yPos + 1][xPos] = 1;
  miniMap[yPos + 1][xPos + 1] = 1;
}

void setMiniMap(int xPos, int yPos)
{
  miniMap[yPos][xPos] = 1;
  unlockMiniMapArea(yPos, xPos);
}

// button utility, should make arduino calls
Button getButton()
{
  Button button = Button::NONE;

#if IS_USING_SDL
  button = getButtonSDL();
#else
  while (!button)
  {
    button = getButton();
    // Put delay here on Arduino
  }
#endif

  return button;
}

// player instance
static Player player;
static vec2 playerStartPos =
    vec2((MAP_WIDTH - 1) / 2.0f, (MAP_HEIGHT - 1) / 2.0f);

class Scene
{
public:
  Scene() = default;

  virtual void render() = 0;
  virtual GameState processInput() = 0;

protected:
  void clearScreen()
  {
    // call to clear pixel buffer with black
    tft.fillScreen(COL_BLACK);
  }
};

class Loading : public Scene
{
public:
  Loading()
  {
    // calls to load the image?
    // set text pos
  }

  virtual GameState processInput() override { return GameState::LOADING; }

  virtual void render() override
  {
    clearScreen();
    // call to render the image
    // call to render the text "Loading..."
    tft.setCursor(0, 0);
    tft.setTextColor(COL_BLUE);
    tft.setTextSize(5);
    tft.print("Loading");
  }

private:
  // imageData Data; ???
  vec2 textPos;
  const char *loadingText{
    "Loading..."
  }; // what? need to review string init in c LOL
};

class MainMenu : public Scene
{
public:
  MainMenu()
  {
    // call to load image?
    // set text_pos
  }

  virtual void render() override
  {
    clearScreen();
    // call to render image
    // call to render text "Press a button to start"
    tft.setCursor(0, 0);
    tft.setTextColor(COL_BLUE);
    tft.setTextSize(5);
    tft.print("Press\na button\nto start!");
  }

  virtual GameState processInput()
  {
    bool input = false;

#if IS_USING_SDL
    Button button = getButton();
    if (button)
    {
      input = true;
    }
#else
    while (!input)
    {
      // read input
      Button button = getButton();
      if (button)
      {
        input = true;
      }

      // sleep??
    }
#endif

    return GameState::GAME_VIEW;
  }

private:
  vec2 m_TextPos;
};

class GameOver : public Scene
{
public:
  GameOver()
  {
    // set text pos
  }

  virtual void render() override
  {
    // render "GAME OVER" text

    resetMiniMap();
    player.pos = playerStartPos;
    setMiniMap((int)player.pos.x, (int)player.pos.y);

    // render "Press a button to try again..."
  }

  virtual GameState processInput() override
  {
    GameState newGamestate = GameState::GAME_OVER;

    bool input = false;

    while (!input)
    {
      // read input
      Button button = getButton();
      if (button)
      {
        input = true;
        newGamestate = GameState::MAIN_MENU;
      }

      // sleep??
    }

    return newGamestate;
  }

private:
  vec2 m_gameOverTextPos;
  vec2 m_ButtonPromptTextPos;
};

class MiniMap : public Scene
{
public:
  MiniMap() { resetMiniMap(); }

  virtual void render() override
  {
    renderMiniMap();
    renderPlayer();
  }

  virtual GameState processInput() override
  {
    GameState newGamestate = GameState::MAP_VIEW;

    bool input = false;

    while (!input)
    {
      // read input
      Button button = getButton();
      if (button)
      {
        input = true;
        newGamestate = GameState::GAME_VIEW;
      }

      // sleep??
    }

    return newGamestate;
  }

private:
  int playerSizeMiniMap = 4; // still not sure about this, i wanted to use an
                             // odd lenght square, but cell size is even FML

  void renderMiniMap()
  {
    int color = 0;
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
      for (int x = 0; x < MAP_WIDTH; x++)
      {
        if (!miniMap[x][y])
          continue;

        switch (map[y][x])
        {
        case Tile::EMPTY:
          color = COL_GREY;
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

  void drawCell(int x, int y, int color)
  {
    int xPos = x * CELL_SIZE + 1;
    int yPos = y * CELL_SIZE + 1;

    int sideLenght = CELL_SIZE - 2;

    // drawcall for rect drawRect(xPos, yPos, sideLenght, sideLenght, color);
  }

  void renderPlayer()
  {
    // CARE: NOT SURE IF IT'S RIGHT, need to test it
    float posX = player.pos.x * CELL_SIZE;
    float posY = player.pos.y * CELL_SIZE;

    // drawcall:
    // drawRect((int)posX - 1, (int)posX - 1, playerSizeMiniMap,
    // playerSizeMiniMap, COL_GREEN);
    renderPlayerDir((int)posX, (int)posY);
  }

  void renderPlayerDir(int x, int y)
  {

    // TODO: TO REVIEW (even cellsize cant center player properly, i've to
    // figure out a way to show direction of view) this system was thought for 1
    // pixel next to the player in the direction he's looking not working if the
    // player size in minimap is even, need odd to work
    int posX = x + player.dir.x * 3;
    int posY = y + player.dir.y * 3;
  }
};

class MazeGame : public Scene
{
public:
  MazeGame()
  {
    // set all minimap values to 0?
    player.pos = playerStartPos;
    setMiniMap(player.pos.x, player.pos.y);
  }

  virtual void render() override
  {
    clearScreen();
    drawFloor();
    rayCasting();
  }

  virtual GameState processInput() override
  {
    bool input = false;
    bool gameOver = false;
    GameState newState = GameState::GAME_VIEW;
    Button keyPressed = Button::NONE;

#if !IS_USING_SDL
    while (!input)
    {
#endif
      keyPressed = getButton();

      switch (keyPressed)
      {
      case NONE:
        break;
      case KEY_UP:
      {
        input = true;
        vec2 predicetdPos = player.pos + player.dir;

        if (predicetdPos.x >= MAP_WIDTH || predicetdPos.y >= MAP_HEIGHT)
          break;
        if (map[(int)predicetdPos.y][(int)predicetdPos.x] == Tile::WALL ||
            map[(int)predicetdPos.y][(int)predicetdPos.x] == Tile::WALL_BLUE)
          break;

        player.movePlayer(1.0f);
        if (map[(int)player.pos.y][(int)player.pos.x] == END)
        {
          newState = GameState::GAME_OVER;
          break;
        }

        unlockMiniMapArea((int)player.pos.x, (int)player.pos.y);
        break;
      }
      case KEY_LEFT:
      {
        input = true;
        player.rotate(-90);
        break;
      }
      case KEY_RIGHT:
      {
        input = true;
        player.rotate(90);
        break;
      }
      case KEY_OPTION:
      {
        input = true;
        newState = GameState::MAP_VIEW;
        break;
      }
      }
#if !IS_USING_SDL
    }
#endif

    return newState;
  }

private:
  void rayCasting()
  {
    vec2 rayDir;

    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
      float cameraX = 2.0f * x / (float)SCREEN_WIDTH - 1;
      rayDir.x = player.dir.x + player.cameraPlane.x * cameraX;
      rayDir.y = player.dir.y + player.cameraPlane.y * cameraX;

      int mapX = (int)player.pos.x;
      int mapY = (int)player.pos.y;

      vec2 sideDist;
      vec2 deltaDist;
      float perpDist;

      deltaDist.x = (rayDir.x == 0) ? 1e30 : std::abs(1 / rayDir.x);
      deltaDist.y = (rayDir.y == 0) ? 1e30 : std::abs(1 / rayDir.y);

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

        if (map[mapY][mapX] != Tile::EMPTY && map[mapY][mapX] != Tile::END)
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

      drawVertLine(x, lineHeight, color);
    }
  }

  void drawFloor()
  {
    // drawcall grey rect bottom half
    tft.drawRect(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2,
                 COL_GREY);
  }

  void drawVertLine(int x, int lenght, int color)
  {
    int lineStartY = (SCREEN_HEIGHT - lenght) / 2;
    // drawcall line draw
    tft.drawFastVLine(x, lineStartY, lenght, color);
  }
};

#endif