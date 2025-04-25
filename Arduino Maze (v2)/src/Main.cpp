/* Headers */
#include "ArduinoApp.hpp"
#include "libs/SDL.hpp"

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
