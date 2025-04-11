// SDL Related Includes
#include "App.h"
#include "SDL.h"
// Arduino Related Includes
#include "Adafruit_ILI9341.h"
#include "src/defines.hpp"
#include "src/scenes.hpp"
#include <SDL3\SDL_log.h>
#include <SDL3\SDL_render.h>
#include <SDL3\SDL_timer.h>
#include <cmath>
#include <cstdint>

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft(TFT_CS, TFT_DC);

GameState state;
Scene *scenes[static_cast<int>(GameState::GAME_OVER) + 1];

void setupButtons() { /* stub! */ }

MainMenu g_mainMenu;
MazeGame g_mazeGame;
MiniMap g_miniMap;
GameOver g_gameOver;

void setup()
{
  tft.begin();
  tft.setRotation(1);

  scenes[static_cast<int>(GameState::LOADING)] = new Loading();
  state = GameState::LOADING;
  scenes[static_cast<int>(state)]->render();
  SDL_RenderPresent(gRenderer);
  SDL_Delay(1000);

  initTables();
  setupButtons();
  scenes[static_cast<int>(GameState::MAIN_MENU)] = &g_mainMenu;
  scenes[static_cast<int>(GameState::GAME_VIEW)] = &g_mazeGame;
  scenes[static_cast<int>(GameState::MAP_VIEW)] = &g_miniMap;
  scenes[static_cast<int>(GameState::GAME_OVER)] = &g_gameOver;

  state = GameState::MAIN_MENU;
}

void loop()
{
  float deltaTime = getDeltaTime();
  scenes[static_cast<int>(state)]->render();
  state = scenes[static_cast<int>(state)]->processInput(deltaTime);
}
