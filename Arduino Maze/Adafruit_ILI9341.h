#pragma once

#include "Adafruit_GFX.h"
#include <cstdint>

// Color definitions
#define ILI9341_BLACK 0x0000       ///<   0,   0,   0
#define ILI9341_NAVY 0x000F        ///<   0,   0, 123
#define ILI9341_DARKGREEN 0x03E0   ///<   0, 125,   0
#define ILI9341_DARKCYAN 0x03EF    ///<   0, 125, 123
#define ILI9341_MAROON 0x7800      ///< 123,   0,   0
#define ILI9341_PURPLE 0x780F      ///< 123,   0, 123
#define ILI9341_OLIVE 0x7BE0       ///< 123, 125,   0
#define ILI9341_LIGHTGREY 0xC618   ///< 198, 195, 198
#define ILI9341_DARKGREY 0x7BEF    ///< 123, 125, 123
#define ILI9341_BLUE 0x001F        ///<   0,   0, 255
#define ILI9341_GREEN 0x07E0       ///<   0, 255,   0
#define ILI9341_CYAN 0x07FF        ///<   0, 255, 255
#define ILI9341_RED 0xF800         ///< 255,   0,   0
#define ILI9341_MAGENTA 0xF81F     ///< 255,   0, 255
#define ILI9341_YELLOW 0xFFE0      ///< 255, 255,   0
#define ILI9341_WHITE 0xFFFF       ///< 255, 255, 255
#define ILI9341_ORANGE 0xFD20      ///< 255, 165,   0
#define ILI9341_GREENYELLOW 0xAFE5 ///< 173, 255,  41
#define ILI9341_PINK 0xFC18        ///< 255, 130, 198

class Adafruit_ILI9341 : public Adafruit_GFX
{
public:
  /**
   * @note All parameters don't do anything. They just imitate
   *       the real Adafruit_ILI9341.
   */
  Adafruit_ILI9341(int8_t _CS, int8_t _DC, int8_t _RST = -1);

  /**
   * @note freq doesn't do anything. Just to imitate the
   *       original method.
   */
  void begin(uint32_t freq = 0);

  /**
   * @note Doesn't do anything, this is just a stub.
   *       Since the screen is already in landscape mode,
   *       there's no need to setRotation but just to
   *       imitate the "real thing" then I add this here.
   */
  void setRotation(uint8_t r);
};
