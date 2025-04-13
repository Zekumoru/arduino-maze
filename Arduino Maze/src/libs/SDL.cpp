#include "SDL.hpp"
#include "../definitions.hpp"
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

extern bool gQuit;

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

void putButtonsSDL(bool (&buttonsState)[5])
{
  SDL_Event e;
  SDL_zero(e);

  while (SDL_PollEvent(&e))
  {
    if (e.key.key == SDLK_ESCAPE)
    {
      gQuit = true;
    }
    if (e.type == SDL_EVENT_QUIT)
    {
      gQuit = true;
    }
  }

  const bool *keystate = SDL_GetKeyboardState(nullptr);

  buttonsState[NONE] = false;
  buttonsState[KEY_LEFT] = keystate[SDL_SCANCODE_LEFT];
  buttonsState[KEY_RIGHT] = keystate[SDL_SCANCODE_RIGHT];
  buttonsState[KEY_UP] = keystate[SDL_SCANCODE_UP];
  buttonsState[KEY_OPTION] = keystate[SDL_SCANCODE_SPACE];
}

Button getButtonSDL()
{
  SDL_Event e;
  SDL_zero(e);

  Button button = Button::NONE;

  while (SDL_PollEvent(&e))
  {
    if (e.key.key == SDLK_ESCAPE)
    {
      gQuit = true;
    }
    if (e.type == SDL_EVENT_QUIT)
    {
      gQuit = true;
    }
    if (e.type == SDL_EVENT_KEY_DOWN)
    {
      switch (e.key.key)
      {
      case SDLK_UP:
        button = KEY_UP;
        break;
      case SDLK_LEFT:
        button = KEY_LEFT;
        break;
      case SDLK_RIGHT:
        button = KEY_RIGHT;
        break;
      }
    }
    if (e.type == SDL_EVENT_KEY_UP && e.key.key == SDLK_SPACE)
    {
      button = KEY_OPTION;
    }
  }

  return button;
}

// static Uint64 lastTime = SDL_GetPerformanceCounter();

// float getDeltaTime()
//{
//   Uint64 now = SDL_GetPerformanceCounter();
//   float deltaTime =
//       (float)((now - lastTime) * 1000 / (double)SDL_GetPerformanceFrequency()) *
//       0.001f;
//   lastTime = now;
//   return deltaTime;
// }

float getDeltaTime()
{
  static Uint64 last_time = 0; // Time counter at the end of the previous frame
  static Uint64 frequency = 0; // Ticks per second of the performance counter

  if (frequency == 0)
  {
    frequency = SDL_GetPerformanceFrequency();
    if (frequency == 0)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                   "Could not get performance frequency: %s", SDL_GetError());
      return 0.0f;
    }
    last_time = SDL_GetPerformanceCounter();
  }

  Uint64 current_time = SDL_GetPerformanceCounter();

  Uint64 elapsed_ticks;
  if (current_time < last_time)
  {
    elapsed_ticks = (SDL_MAX_UINT64 - last_time) + current_time;
  }
  else
  {
    elapsed_ticks = current_time - last_time;
  }

  float delta_time =
      static_cast<float>(elapsed_ticks) / static_cast<float>(frequency);

  last_time = current_time;

  return delta_time;
}
