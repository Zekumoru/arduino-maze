/* Headers */
#include "Adafruit_GFX.h"
#include <SDL3\SDL_error.h>
#include <SDL3\SDL_events.h>
#include <SDL3\SDL_init.h>
#include <SDL3\SDL_keycode.h>
#include <SDL3\SDL_log.h>
#include <SDL3\SDL_render.h>
#include <SDL3\SDL_stdinc.h>
#include <SDL3\SDL_video.h>

const int kScreenWidth = 320;
const int kScreenHeight = 240;

SDL_Window *gWindow{ nullptr };
SDL_Renderer *gRenderer{ nullptr };

/* Function Implementations */
static bool init()
{
  // Initialize SDL
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
    return false;
  }

  // Create window with renderer
  if (!SDL_CreateWindowAndRenderer("Arduino Maze Simulator", kScreenWidth,
                                   kScreenHeight, 0, &gWindow, &gRenderer))
  {
    SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

static void close()
{
  // Destroy window
  SDL_DestroyRenderer(gRenderer);
  gRenderer = nullptr;
  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  // Quit SDL subsystems
  SDL_Quit();
}

int main(int argc, char *args[])
{
  // Initialize
  if (!init())
  {
    SDL_Log("Unable to initialize program!\n");
    return 1;
  }

  Adafruit_GFX gfx(gWindow, gRenderer, kScreenWidth, kScreenHeight);

  // The quit flag
  bool quit{ false };

  // The event data
  SDL_Event e;
  SDL_zero(e);

  int x = 0;
  int y = 0;

  // The main loop
  while (quit == false)
  {
    // Get event data//Get event data
    while (SDL_PollEvent(&e))
    {
      // If event is quit type
      if (e.type == SDL_EVENT_QUIT)
      {
        // End the main loop
        quit = true;
      }
      else if (e.type == SDL_EVENT_KEY_DOWN)
      {
        // Set texture
        if (e.key.key == SDLK_UP)
        {
          y -= 2;

          if (y < 0)
          {
            y = 0;
          }
        }
        else if (e.key.key == SDLK_DOWN)
        {
          y += 2;

          if (y > kScreenHeight)
          {
            y = kScreenHeight - 1;
          }
        }
        else if (e.key.key == SDLK_LEFT)
        {
          x -= 2;

          if (x < 0)
          {
            x = 0;
          }
        }
        else if (e.key.key == SDLK_RIGHT)
        {
          x += 2;

          if (x > kScreenWidth)
          {
            x = kScreenWidth - 1;
          }
        }
      }
    }

    gfx.fillScreen(0xFFFFFF);

    gfx.setTextColor(0xFF00FF);
    gfx.setTextSize(5);
    gfx.setCursor(x, y);
    gfx.println("Hello, lorem ipsum dolor it sum noir.");
    gfx.println("World!");
    gfx.drawChar(0, 0, 'A', 0xFFFFFF, 0x0, 5);
    gfx.drawRect(50, 50, 100, 100, 0xFF0000);
    gfx.fillRect(100, 100, 100, 100, 0x00FF00);
    gfx.drawFastVLine(x, 0, kScreenHeight, 0x0000FF);

    // Update screen
    SDL_RenderPresent(gRenderer);
  }

  // Clean up
  close();

  return 0;
}
