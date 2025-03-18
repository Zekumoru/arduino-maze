const int SCREEN_WIDTH;
const int SCREEN_HEIGHT;

class Scene
{
  Scene();

  virtual void render() = 0;

  virtual GameState getInput() = 0; // return type to be thought of
};

class LoadingScreen : public Scene
{
};

class MainMenu : public Scene
{
};

class MainGame : public Scene
{
};

enum Buttons = {
                   CONTROL_BUTTON, // minimap, menu selection
                   FORWARD_BUTTON,
                   LEFT_BUTTON,
                   RIGHT_BUTTON,
}

               // Game flow

               Scene *
               scene;

enum GameState
{
  LOADING_STATE,
  MENU_STATE,
  RUNNING_STATE,
  WIN_STATE,
  GAME_OVER_STATE,
  MINIMAP_STATE,
  STATE_COUNT
}

GameState state;

Scene *scenes[STATE_COUNT];

void setup()
{
  setupScreen(); // setup display physical component

  // show loading scene
  scenes[LOADING_STATE] = new LoadingScene();
  state = LOADING_STATE;
  scenes[state]->render();

  // init scenes
  scenes[MENU_STATE] = new MenuScene();
  scenes[RUNNING_STATE] = new RunningScene();
  scenes[WIN_STATE] = new WinScene();
  scenes[GAME_OVER_STATE] = new GameOverScene();
  scenes[MINIMAP_STATE] = new MinimapScene();

  // setup game
  setupButtons();

  createTrigLookUpTable(); // create sine/cosine lookup table

  scene = MENU_STATE;
}

Timer timer;

void loop()
{

  scenes[state]->render();

  /**
   * If RUNNING_STATE and input is LEFT, RIGHT, FORWARD
   * then RUNNING_STATE
   */
  state = scenes[state]->getInput();

  // timer is an over feature
  if (!timer.hasStarted() && state == RUNNING_STATE)
  {
    timer.start();
  }

  if (timer.isFinished())
  {
    state = GAME_OVER_STATE;
  }
}
