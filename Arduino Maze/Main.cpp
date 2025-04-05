/* Headers */
#include "App.h"
#include "SDL.h"
#include <SDL3\SDL_events.h>
#include <SDL3\SDL_render.h>
#include <SDL3\SDL_stdinc.h>
#include <memory>

extern SDL_Renderer *gRenderer;
extern SDL_Event gEvent;

int main(int argc, char *args[])
{
  init();

  bool quit{ false };
  SDL_Event e;
  SDL_zero(e);

  setup();

  while (quit == false)
  {
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_EVENT_QUIT)
      {
        quit = true;
      }
      else
      {
        gEvent = e;
      }
    }

    loop();

    SDL_RenderPresent(gRenderer);
  }

  close();

  return 0;
}
