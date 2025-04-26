#include "Input.hpp"
#include "definitions.hpp"

#ifdef IS_USING_SDL
#include "libs/SDL.hpp"
#else
const uint8_t buttonPins[NUM_BUTTONS] = { -1, 5, 4, 3, 2 }; // NONE, KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_OPTION
static uint8_t stableState = 0;
static uint8_t lastRaw[NUM_BUTTONS];
static unsigned long lastChange[NUM_BUTTONS];
static bool states[NUM_BUTTONS];
#endif

void setupButtons()
{
#ifndef IS_USING_SDL
  unsigned long now = millis();

  for (uint8_t i = 0; i <= NUM_BUTTONS; i++)
  {
    if (buttonPins[i] == -1)
      continue; // skip NONE button

    pinMode(buttonPins[i], INPUT_PULLUP);
    lastRaw[i] = digitalRead(buttonPins[i]);
    lastChange[i] = now;
    if (lastRaw[i] == LOW)
      stableState |= (1 << i);
  }
#endif
}

bool *getButtonsState()
{
#ifndef IS_USING_SDL
  unsigned long now = millis();
  
  // Debounce & update stableState
  for (uint8_t i = 0; i < NUM_BUTTONS; i++)
  {
    uint8_t raw = digitalRead(buttonPins[i]);

    // reset timer on change
    if (raw != lastRaw[i]) {
      lastRaw[i]    = raw;
      lastChange[i] = now;
    }

    // commit if past debounce window
    if (now - lastChange[i] >= DEBOUNCE_MS) {
      bool isPressed  = (raw == LOW);
      bool wasPressed = bitRead(stableState, i);
      if (isPressed != wasPressed) {
        bitWrite(stableState, i, isPressed);
      }
    }

    // write out result
    states[i] = bitRead(stableState, i) ? 0 : 1;
  }

  return states;
#else
  return getButtonsStateSDL();
#endif
}
