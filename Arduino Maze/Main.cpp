/* Headers */
#include "App.h"
#include "SDL.h"
#include <SDL3\SDL_events.h>
#include <SDL3\SDL_keycode.h>
#include <SDL3\SDL_render.h>
#include <SDL3\SDL_stdinc.h>

extern SDL_Renderer *gRenderer;

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
      else if (e.type == SDL_EVENT_KEY_DOWN)
      {
        if (e.key.key == SDLK_UP)
        {
        }
        else if (e.key.key == SDLK_DOWN)
        {
        }
        else if (e.key.key == SDLK_LEFT)
        {
        }
        else if (e.key.key == SDLK_RIGHT)
        {
        }
      }
    }

    loop();

    SDL_RenderPresent(gRenderer);
  }

  close();

  return 0;
}
