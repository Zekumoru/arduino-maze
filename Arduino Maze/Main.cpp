/* Headers */
#include <SDL3\SDL_error.h>
#include <SDL3\SDL_events.h>
#include <SDL3\SDL_init.h>
#include <SDL3\SDL_log.h>
#include <SDL3\SDL_pixels.h>
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

  // The quit flag
  bool quit{ false };

  // The event data
  SDL_Event e;
  SDL_zero(e);

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
    }

    // Fill the background with color white
    SDL_Color bgColor = { 0xFF, 0xFF, 0xFF, 0xFF };
    SDL_SetRenderDrawColor(gRenderer, bgColor.r, bgColor.g, bgColor.b, 0xFF);
    SDL_RenderClear(gRenderer);

    // Update screen
    SDL_RenderPresent(gRenderer);
  }

  // Clean up
  close();

  return 0;
}
