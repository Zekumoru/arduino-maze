#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <cmath>

// tft screen res
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_LINE_LEN (SCREEN_HEIGHT - 8)

// the size of the map should be related to the screen res so we can fill the
// map_view and have easier time rendering it. ig: yRes = 200, we can have
// 20 or 10 or any n*m = 20
#define MAP_WIDTH 32
#define MAP_HEIGHT 24
#define CELL_SIZE 10 // it's in pixels. one side needed since it's gonna
                     // be a square, used to render the minimap

#define COL_BLACK 0x000F
#define COL_GREY 0x888F
#define COL_WHITE 0xFFFF
#define COL_RED 0xF00F
#define COL_GREEN 0x0F0F
#define COL_BLUE 0x00FF
#define COL_YELLOW 0xFF0F
#define COL_MAGENTA 0xF0FF
#define COL_CYAN 0x0FFF

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

inline static float cosLT[360];
inline static float sinLT[360];

float radians(int angle)
{
    return (float)angle * PI / 180;
}

inline void initTables()
{
    for (int i = 0; i < 360; i++)
    {
        float rad = radians(i);
        cosLT[i] = cos(rad);
        sinLT[i] = sin(rad);
    }
}

#endif // !DEFINES_HPP