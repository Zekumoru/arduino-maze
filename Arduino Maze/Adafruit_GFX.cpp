#include "Adafruit_GFX.h"

#include "SDL.h"
#include "font.h"
#include <SDL3\SDL_rect.h>
#include <SDL3\SDL_render.h>
#include <SDL3\SDL_video.h>
#include <cstdint>
#include <utility>

Adafruit_GFX::Adafruit_GFX(SDL_Window *window, SDL_Renderer *renderer,
                           int16_t width, int16_t height)
    : window(window), renderer(renderer), width(width), height(height)
{
  if (window == nullptr || renderer == nullptr)
  {
    init();
    this->window = gWindow;
    this->renderer = gRenderer;
  }
}

void Adafruit_GFX::drawRect(int16_t x, int16_t y, int16_t w, int16_t h,
                            uint16_t color)
{
  SDL_FRect rect = { static_cast<float>(x), static_cast<float>(y),
                     static_cast<float>(w), static_cast<float>(h) };
  setColor(color);
  SDL_RenderRect(renderer, &rect);
}

void Adafruit_GFX::drawChar(int16_t x, int16_t y, unsigned char c,
                            uint16_t color, uint16_t bg, uint8_t size)
{
  // Calculate actual dimensions
  const int16_t charW = 5 * size;
  const int16_t charH = 7 * size;

  // Clip if character is completely offscreen
  if (x >= width || y >= height || x + charW < 0 || y + charH < 0)
    return;

  // Draw background (if different from text color)
  if (color != bg)
  {
    // Include vertical and horizontal spaces with bg color
    const int16_t charBgW = CHAR_WIDTH * size;
    const int16_t charBgH = CHAR_HEIGHT * size;

    // Clip background rect to screen bounds
    int16_t zero = 0;
    int16_t bgX = std::max(x, zero);
    int16_t bgY = std::max(y, zero);

    int16_t bX = width - bgX;
    int16_t bgW = std::min(charBgW, bX);

    int16_t bY = height - bgY;
    int16_t bgH = std::min(charBgH, bY);

    if (bgW > 0 && bgH > 0)
    {
      fillRect(bgX, bgY, bgW, bgH, bg);
    }
  }

  // Draw character glyph
  int index = (c - 0x20) * 5;
  if (index < 0 || index + 4 >= sizeof(font))
    return;

  setColor(color);

  for (uint8_t col = 0; col < 5; col++)
  {
    uint8_t column = font[index + col];
    for (uint8_t row = 0; row < 7; row++)
    {
      if (column & (1 << row))
      {
        // Calculate base position
        const int16_t baseX = x + col * size;
        const int16_t baseY = y + row * size;

        // Draw scaled pixels
        for (uint8_t i = 0; i < size; i++)
        {
          for (uint8_t j = 0; j < size; j++)
          {
            const int16_t px = baseX + i;
            const int16_t py = baseY + j;

            // Only draw if within screen bounds
            if (px >= 0 && px < width && py >= 0 && py < height)
            {
              SDL_RenderPoint(renderer, px, py);
            }
          }
        }
      }
    }
  }
}

void Adafruit_GFX::setTextColor(uint16_t c) { textColor = textBgColor = c; }

void Adafruit_GFX::print(const char *str)
{
  textBgColor = textColor; // Set bg transparent

  while (*str)
  {
    if (*str == '\n')
    {
      cursorY += CHAR_HEIGHT * textSize;
      cursorX = defaultCursorX;
    }
    else
    {
      // Check if we need to wrap
      if (cursorX + (CHAR_WIDTH * textSize) > width)
      {
        cursorY += CHAR_HEIGHT * textSize;
        cursorX = defaultCursorX;
      }

      // Only draw if vertically within bounds
      if (cursorY < height)
      {
        drawChar(cursorX, cursorY, *str, textColor, textBgColor, textSize);
      }

      cursorX += CHAR_WIDTH * textSize;
    }
    str++;
  }
}

void Adafruit_GFX::println(const char *str)
{
  print(str);

  // Only advance if we're still within vertical bounds
  if (cursorY < height)
  {
    cursorY += CHAR_HEIGHT * textSize;
  }
}

void Adafruit_GFX::setTextSize(uint8_t s) { textSize = (s < 1) ? 1 : s; }

void Adafruit_GFX::drawFastVLine(int16_t x, int16_t y, int16_t h,
                                 uint16_t color)
{
  setColor(color);
  SDL_RenderLine(renderer, static_cast<float>(x), static_cast<float>(y),
                 static_cast<float>(x), static_cast<float>(y + h));
}

void Adafruit_GFX::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                            uint16_t color)
{
  SDL_FRect rect = { static_cast<float>(x), static_cast<float>(y),
                     static_cast<float>(w), static_cast<float>(h) };
  setColor(color);
  SDL_RenderFillRect(renderer, &rect);
}

void Adafruit_GFX::fillScreen(uint16_t color)
{
  fillRect(0, 0, width, height, color);
}

void Adafruit_GFX::setCursor(int16_t x, int16_t y)
{
  defaultCursorX = cursorX = x;
  defaultCursorY = cursorY = y;
}

int16_t Adafruit_GFX::getCursorX() const { return cursorX; }

int16_t Adafruit_GFX::getCursorY() const { return cursorY; }

void Adafruit_GFX::setColor(uint16_t color)
{
  // Convert RGB565 to RGB888
  uint8_t r = ((color >> 11) & 0x1F) * 255 / 31;
  uint8_t g = ((color >> 5) & 0x3F) * 255 / 63;
  uint8_t b = (color & 0x1F) * 255 / 31;
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}
