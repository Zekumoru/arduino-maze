#include "Adafruit_ILI9341.hpp"
#include "Adafruit_GFX.hpp"
#include <SDL3\SDL_render.h>
#include <SDL3\SDL_video.h>
#include <cstdint>

extern const int16_t kScreenWidth;
extern const int16_t kScreenHeight;

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

Adafruit_ILI9341::Adafruit_ILI9341(int8_t _CS, int8_t _DC, int8_t _RST)
    : Adafruit_GFX(gWindow, gRenderer, kScreenWidth, kScreenHeight)
{
}

void Adafruit_ILI9341::begin(uint32_t freq) {}

void Adafruit_ILI9341::setRotation(uint8_t r) {}