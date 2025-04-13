// SDL Related Includes
#include "libs/SDL.hpp"
// Arduino Related Includes
#include "engine/Input.hpp"
#include "engine/Player.hpp"
#include "App.hpp"
#include "scenes/GameOverScene.hpp"
#include "scenes/GameScene.hpp"
#include "scenes/LoadingScene.hpp"
#include "scenes/MainMenuScene.hpp"
#include "scenes/MiniMapScene.hpp"
#include <SDL3\SDL_timer.h>

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft(TFT_CS, TFT_DC);

float cosLT[360];
float sinLT[360];

Player player;
Vec2 playerStartPos(2, 2);

GameState state;
Scene *scenes[static_cast<int>(GameState::GAME_OVER) + 1];

LoadingScene g_loading;
MainMenuScene g_mainMenu;
MiniMapScene g_miniMap;
GameScene g_game;
GameOverScene g_gameOver;

void setup()
{
  tft.begin();
  tft.setRotation(1);

  scenes[static_cast<int>(GameState::LOADING)] = &g_loading;
  state = GameState::LOADING;
  scenes[static_cast<int>(state)]->render();
  SDL_RenderPresent(gRenderer);
  SDL_Delay(1000);

  initTables();
  setupButtons();
  scenes[static_cast<int>(GameState::MAIN_MENU)] = &g_mainMenu;
  scenes[static_cast<int>(GameState::MAP_VIEW)] = &g_miniMap;
  scenes[static_cast<int>(GameState::GAME_VIEW)] = &g_game;
  scenes[static_cast<int>(GameState::GAME_OVER)] = &g_gameOver;

  state = GameState::MAIN_MENU;
}

void loop()
{
  static bool prevButtonsState[5] = { false, false, false, false, false };

  // Render scene
  scenes[static_cast<int>(state)]->render();

  // Determine which buttons were just pressed (rising edge)
  const bool *currentButtonsState = getButtonsState();
  bool buttonsJustPressed[5] = { false };
  for (int i = 0; i < 5; ++i)
  {
    buttonsJustPressed[i] = currentButtonsState[i] && !prevButtonsState[i];
  }

  // Handle inputs
  float deltaTime = getDeltaTime();
  state = scenes[static_cast<int>(state)]->processInput(currentButtonsState, buttonsJustPressed, deltaTime);

  // Update previous button states
  memcpy(prevButtonsState, currentButtonsState, sizeof(prevButtonsState));
}
