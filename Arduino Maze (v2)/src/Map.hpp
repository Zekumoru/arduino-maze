#ifndef MAP_HPP
#define MAP_HPP

#include "definitions.hpp"

// mapdata
//!!! Will probably opt for a one dim array (map[HEIGHT*WIDTH] for better access(?) to memory)
extern int mazeMap[MAP_HEIGHT][MAP_WIDTH];

extern int miniMap[MAP_HEIGHT][MAP_WIDTH];

// minimap utils
void resetMiniMap();

void unlockMiniMapArea(int xPos, int yPos);

void setMiniMap(int xPos, int yPos);

#endif // MAP_HPP
