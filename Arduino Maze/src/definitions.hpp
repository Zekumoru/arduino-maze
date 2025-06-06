#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <cmath>

// tft screen res
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_LINE_LEN SCREEN_HEIGHT

// the size of the map should be related to the screen res so we can fill the
// map_view and have easier time rendering it. ig: yRes = 200, we can have
// 20 or 10 or any n*m = 20
#define MAP_WIDTH 32
#define MAP_HEIGHT 24

// it's in pixels. one side needed since it's gonna
// be a square, used to render the minimap
#define CELL_SIZE 10

#define COL_BLACK 0x0000
#define COL_GREY 0x7BEF
#define COL_WHITE 0xFFFF
#define COL_RED 0xF800
#define COL_GREEN 0x07E0
#define COL_BLUE 0x001F
#define COL_YELLOW 0xFFE0
#define COL_ORANGE 0xFD20
#define COL_MAGENTA 0xF81F
#define COL_CYAN 0x07FF
#define COL_DARKGREY 0x3186

#define PI 3.14159265359

enum Button
{
  NONE = 0,
  KEY_UP,
  KEY_LEFT,
  KEY_RIGHT,
  KEY_OPTION
};

enum Tile
{
  EMPTY = 0,
  WALL = 1,
  WALL_BLUE = 2,
  END = 3
};

enum class GameState
{
  LOADING = 0,
  MAIN_MENU,
  GAME_VIEW,
  MAP_VIEW,
  GAME_OVER
};

extern float cosLT[360];
extern float sinLT[360];

inline void initTables()
{
  for (int angle = 0; angle < 360; angle++)
  {
    float rad = (float)angle * (float)PI / 180.0f;
    cosLT[angle] = cos(rad);
    sinLT[angle] = sin(rad);
  }
}

#endif // !DEFINITIONS_HPP