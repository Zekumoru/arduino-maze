#pragma once

#include <SDL3\SDL_render.h>
#include <SDL3\SDL_video.h>
#include <cstdint>

class Adafruit_GFX
{
public:
  Adafruit_GFX(SDL_Window *window, SDL_Renderer *renderer, int16_t width,
               int16_t height);

  void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

  void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
                uint16_t bg, uint8_t size);

  /*!
    @brief   Set text font color with transparent background.
    @param   c   16-bit 5-6-5 Color to draw text with
    @note    For 'transparent' background, background and foreground
             are set to same color rather than using a separate flag.
  */
  void setTextColor(uint16_t c);

  void print(const char *str);

  void println(const char *str);

  void setTextSize(uint8_t s);

  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);

  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

  void fillScreen(uint16_t color);

  void setCursor(int16_t x, int16_t y);

  int16_t getCursorX() const;
  int16_t getCursorY() const;

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  int16_t width;
  int16_t height;

  // Text rendering state
  static constexpr int16_t CHAR_WIDTH = 6;  // 5 + 1 for space
  static constexpr int16_t CHAR_HEIGHT = 8; // 7 + 1 for space
  uint8_t textSize = 1;
  int16_t cursorX = 0;
  int16_t cursorY = 0;
  int16_t defaultCursorX = 0;    // Set only when used setCursor
  int16_t defaultCursorY = 0;    // Set only when used setCursor
  uint16_t textColor = 0xFFFF;   // Default white
  uint16_t textBgColor = 0x0000; // Default black

  void setColor(uint16_t color);
};
