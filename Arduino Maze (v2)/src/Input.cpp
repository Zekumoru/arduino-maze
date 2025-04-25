#include "Input.hpp"
#include "definitions.hpp"

#ifdef IS_USING_SDL
#include "libs/SDL.hpp"
#endif

void setupButtons()
{
  // stub!
}

bool *getButtonsState()
{
#ifndef IS_USING_SDL
  static bool dummy[5]={false,false,false,false,false};
  return dummy;
#else
  return getButtonsStateSDL();
#endif
}
