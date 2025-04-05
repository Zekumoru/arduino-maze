#include "SDL.h"
#include "defines.hpp"
#include <SDL3\SDL_error.h>
#include <SDL3\SDL_events.h>
#include <SDL3\SDL_init.h>
#include <SDL3\SDL_keyboard.h>
#include <SDL3\SDL_keycode.h>
#include <SDL3\SDL_log.h>
#include <SDL3\SDL_render.h>
#include <SDL3\SDL_scancode.h>
#include <SDL3\SDL_stdinc.h>
#include <SDL3\SDL_timer.h>
#include <SDL3\SDL_video.h>
#include <cstdint>

const int16_t kScreenWidth = 320;
const int16_t kScreenHeight = 240;

SDL_Window *gWindow{ nullptr };
SDL_Renderer *gRenderer{ nullptr };

ArduinoSDLError::ArduinoSDLError(const std::string &msg) : message(msg) {}

const char *ArduinoSDLError::what() const noexcept { return message.c_str(); }

void init()
{
  // Is already initialized?
  if (gWindow != nullptr || gRenderer != nullptr)
  {
    return;
  }

  // Initialize SDL
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
    throw ArduinoSDLError("SDL could not initialize!");
  }

  // Create window with renderer
  if (!SDL_CreateWindowAndRenderer("Arduino Maze Simulator", kScreenWidth,
                                   kScreenHeight, 0, &gWindow, &gRenderer))
  {
    SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
    throw ArduinoSDLError("SDL could not create window/renderer!");
  }
}

void close()
{
  // Destroy window
  SDL_DestroyRenderer(gRenderer);
  gRenderer = nullptr;
  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  // Quit SDL subsystems
  SDL_Quit();
}

Button getInput()
{
  const bool *keystate = SDL_GetKeyboardState(nullptr);

  if (keystate[SDL_SCANCODE_LEFT])
    return KEY_LEFT;
  if (keystate[SDL_SCANCODE_RIGHT])
    return KEY_RIGHT;
  if (keystate[SDL_SCANCODE_UP])
    return KEY_UP;
  if (keystate[SDL_SCANCODE_SPACE])
    return KEY_OPTION;

  return NONE;
}

Uint64 lastTime = SDL_GetPerformanceCounter();

float getDeltaTime()
{
  Uint64 now = SDL_GetPerformanceCounter();
  float deltaTime =
      (float)((now - lastTime) * 1000 / (double)SDL_GetPerformanceFrequency()) *
      0.001f;
  lastTime = now;
  return deltaTime;
}
