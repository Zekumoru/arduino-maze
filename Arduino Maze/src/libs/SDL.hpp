#pragma once

#include "../definitions.hpp"
#include <SDL3\SDL_render.h>
#include <SDL3\SDL_video.h>
#include <cstdint>
#include <exception>
#include <string>

extern const int16_t kScreenWidth;
extern const int16_t kScreenHeight;

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

class ArduinoSDLError : public std::exception
{
  std::string message;

public:
  ArduinoSDLError(const std::string &msg);
  const char *what() const noexcept override;
};

void init();

void close();

bool *getButtonsStateSDL();

float getDeltaTime();
