/* Headers */
#include "App.hpp"
#include "libs/SDL.hpp"
#include <SDL3\SDL_events.h>
#include <SDL3\SDL_render.h>

extern SDL_Renderer *gRenderer;
extern SDL_Event gEvent;

bool gQuit{ false };

int main(int argc, char *args[])
{
  init();

  setup();

  while (!gQuit)
  {
    loop();

    SDL_RenderPresent(gRenderer);
  }

  close();

  return 0;
}
