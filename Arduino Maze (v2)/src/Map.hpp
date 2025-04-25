#ifndef MAP_HPP
#define MAP_HPP

#include "definitions.hpp"

#ifdef IS_USING_SDL
#include <cstdint>
#endif

// mapdata
//!!! Will probably opt for a one dim array (map[HEIGHT*WIDTH] for better access(?) to memory)
extern const uint8_t mazeMap[MAP_HEIGHT][MAP_WIDTH] PROGMEM;
uint8_t getMazeTile(int x, int y);

extern uint8_t miniMap[MAP_HEIGHT][MAP_WIDTH];

// minimap utils
void resetMiniMap();

void unlockMiniMapArea(int xPos, int yPos);

void setMiniMap(int xPos, int yPos);

#endif // MAP_HPP
