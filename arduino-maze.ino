/*  ──────────────────────────────────────
    Minimal-RAM Arduino “3-D Maze” demo
    (all modules flattened into one .ino)
    - tested with UNO/Nano (ATmega328P)
    ────────────────────────────────────── */

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <avr/pgmspace.h>

/* ---------- Hardware ---------- */
#define TFT_RST   8
#define TFT_DC    9
#define TFT_CS   10
#define TFT_FREQ 3999999
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

/* ---------- Compile-time constants ---------- */
#define SCREEN_WIDTH   320
#define SCREEN_HEIGHT  240
#define MAX_LINE_LEN   SCREEN_HEIGHT

#define MAP_WIDTH   32
#define MAP_HEIGHT  24
#define CELL_SIZE   10     // pixel side of a minimap cell

#define PI_F 3.1415926536f   // float PI

/* 16-bit 565 colours */
#define COL_BLACK     0x0000
#define COL_GREY      0x7BEF
#define COL_WHITE     0xFFFF
#define COL_RED       0xF800
#define COL_GREEN     0x07E0
#define COL_BLUE      0x001F
#define COL_YELLOW    0xFFE0
#define COL_ORANGE    0xFD20
#define COL_MAGENTA   0xF81F
#define COL_CYAN      0x07FF
#define COL_DARKGREY  0x3186

/* ---------- Small enums ---------- */
enum Button : uint8_t { NONE=0, KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_OPTION };
enum Tile   : uint8_t { EMPTY=0, WALL, WALL_BLUE, END };

enum class GameState : uint8_t {
  LOADING=0, MAIN_MENU, GAME_VIEW, MAP_VIEW, GAME_OVER
};

/* ---------- Utility ---------- */
static inline float degToRad(float d) { return d * PI_F / 180.0f; }

/* ---------- Map data (flash only!) ---------- */
const uint8_t mazeMap[MAP_HEIGHT][MAP_WIDTH] PROGMEM = {
  { 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1 },
  { 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
  { 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1 },
  { 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1 },
  { 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1 },
  { 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1 },
  { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1 },
  { 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1 },
  { 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1 },
  { 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1 },
  { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1 },
  { 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1 },
  { 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1 },
  { 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1 },
  { 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1 },
  { 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1 },
  { 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1 },
  { 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
  { 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1 },
  { 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};
/* helper */
static inline uint8_t getMazeTile(int x,int y){
  return pgm_read_byte(&(mazeMap[y][x]));
}

/* ---------- Mini-map (runtime, modifiable) ---------- */
uint8_t miniMap[MAP_HEIGHT][MAP_WIDTH];   // 768 B

/* ---------- Vec2 ---------- */
struct Vec2 {
  float x,y;
  Vec2():x(0),y(0) {}
  Vec2(float _x,float _y):x(_x),y(_y){}
  Vec2 operator+(const Vec2& o) const { return {x+o.x,y+o.y}; }
  Vec2 operator*(float k) const       { return {x*k,  y*k }; }
};

/* ---------- Player ---------- */
struct Player {
  Vec2 pos   = {2,2};
  Vec2 dir   = {0,1};          // facing “north”
  Vec2 cam   = {0.65f,0};      // camera plane
  float moveSpeed = 1.5f;
  float rotSpeed  = 1.5f;
  float angle     = 90;        // degrees
  void rotate(float deg,float dt){
    angle += deg*rotSpeed*dt;
    if(angle>=360) angle-=360;
    if(angle<0)    angle+=360;
    float r  = degToRad(angle);
    dir.x = cosf(r); dir.y = sinf(r);
    float cp = degToRad(angle-90);
    cam.x = 0.65f*cosf(cp);
    cam.y = 0.65f*sinf(cp);
  }
};
Player player;

/* ---------- Forward decls for scenes ---------- */
struct Scene { virtual void render()=0;
               virtual GameState tick(float dt,const bool* s,const bool* j)=0; };
/* stubs for buttons */
static inline void setupButtons(){}        // TODO: wire buttons
static inline const bool* getButtons(){   // always “no button”
  static bool dummy[5]={false,false,false,false,false};
  return dummy;
}

/* ---------- Scenes ---------- */
struct LoadingScene:Scene{
  void render() override{
    tft.fillScreen(COL_BLACK);
    tft.setCursor(0,0); tft.setTextColor(COL_BLUE);
    tft.setTextSize(3); tft.print(F("Loading..."));
  }
  GameState tick(float,const bool*,const bool*) override{
    return GameState::MAIN_MENU;
  }
} g_loading;

struct MainMenuScene:Scene{
  void render() override{
    tft.fillScreen(COL_BLACK);
    tft.setCursor(0,0); tft.setTextColor(COL_BLUE);
    tft.setTextSize(3);
    tft.print(F("Press\nany btn\nto start"));
  }
  GameState tick(float,const bool*,const bool* j) override{
    return (j[KEY_UP]||j[KEY_LEFT]||j[KEY_RIGHT]||j[KEY_OPTION])
            ? GameState::GAME_VIEW : GameState::MAIN_MENU;
  }
} g_menu;

struct MiniMapScene;      // needs forward use

struct GameScene:Scene{
  void render() override{
    drawFloor();
    raycast();
  }
  GameState tick(float dt,const bool* s,const bool* j) override{
    if(s[KEY_UP]){
      Vec2 next = player.pos + player.dir*player.moveSpeed*dt;
      if(getMazeTile((int)next.x,(int)player.pos.y)!=WALL &&
         getMazeTile((int)next.x,(int)player.pos.y)!=WALL_BLUE) player.pos.x=next.x;
      if(getMazeTile((int)player.pos.y,(int)next.y)!=WALL &&
         getMazeTile((int)player.pos.y,(int)next.y)!=WALL_BLUE) player.pos.y=next.y;
    }
    if(s[KEY_LEFT])  player.rotate(-90,dt);
    if(s[KEY_RIGHT]) player.rotate( 90,dt);
    return j[KEY_OPTION]?GameState::MAP_VIEW:GameState::GAME_VIEW;
  }
private:
  void drawFloor(){ tft.fillRect(0,SCREEN_HEIGHT/2,SCREEN_WIDTH,SCREEN_HEIGHT/2,COL_GREY); }
  void drawVLine(int x,int len,uint16_t col){
    int y0=(SCREEN_HEIGHT-len)/2;
    tft.drawFastVLine(x,y0,len,col);
  }
  void raycast(){
    for(int x=0;x<SCREEN_WIDTH;x++){
      float camX = 2.0f*x/SCREEN_WIDTH - 1;
      Vec2 ray{ player.dir.x+player.cam.x*camX,
                player.dir.y+player.cam.y*camX };
      int mapX=(int)player.pos.x, mapY=(int)player.pos.y;
      Vec2 delta{ ray.x?fabs(1/ray.x):1e30f,
                  ray.y?fabs(1/ray.y):1e30f };
      Vec2 side;
      int stepX,stepY;
      if(ray.x<0){ stepX=-1; side.x=(player.pos.x-mapX)*delta.x; }
      else       { stepX= 1; side.x=(mapX+1.0f-player.pos.x)*delta.x; }
      if(ray.y<0){ stepY=-1; side.y=(player.pos.y-mapY)*delta.y; }
      else       { stepY= 1; side.y=(mapY+1.0f-player.pos.y)*delta.y; }
      uint8_t tile=EMPTY; int sideHit=0;
      while(tile==EMPTY||tile==END){
        if(side.x<side.y){ side.x+=delta.x; mapX+=stepX; sideHit=0; }
        else             { side.y+=delta.y; mapY+=stepY; sideHit=1; }
        tile=getMazeTile(mapX,mapY);
      }
      float perp = sideHit?side.y-delta.y:side.x-delta.x;
      int lineH = (int)(SCREEN_HEIGHT/perp);
      if(lineH>MAX_LINE_LEN) lineH=MAX_LINE_LEN;
      uint16_t col = (tile==WALL?COL_ORANGE:COL_BLUE);
      if(sideHit && tile==WALL) col=COL_YELLOW;
      drawVLine(SCREEN_WIDTH-1-x,lineH,col);
    }
  }
} g_game;

struct MiniMapScene:Scene{
  void render() override{
    tft.fillScreen(COL_BLACK);
    for(int y=0;y<MAP_HEIGHT;y++)
      for(int x=0;x<MAP_WIDTH;x++){
        if(!miniMap[y][x]) continue;
        uint16_t c;
        switch(getMazeTile(x,y)){
          case EMPTY: c=COL_DARKGREY; break;
          case WALL: case WALL_BLUE: c=COL_WHITE; break;
          case END:  c=COL_BLUE; break;
          default:   c=COL_MAGENTA; break;
        }
        drawCell(x,y,c);
      }
    drawPlayer();
  }
  GameState tick(float,const bool*,const bool* j) override{
    return j[KEY_OPTION]?GameState::GAME_VIEW:GameState::MAP_VIEW;
  }
private:
  void drawCell(int x,int y,uint16_t col){
    int px=x*CELL_SIZE, py=y*CELL_SIZE;
    tft.fillRect(px+1,py+1,CELL_SIZE-2,CELL_SIZE-2,col);
  }
  void drawPlayer(){
    int px=player.pos.x*CELL_SIZE, py=player.pos.y*CELL_SIZE;
    tft.fillRect(px+3,py+3,4,4,COL_GREEN);
    int dx=px+CELL_SIZE/2+3*player.dir.x;
    int dy=py+CELL_SIZE/2+3*player.dir.y;
    tft.drawPixel(dx,dy,COL_GREEN);
  }
} g_map;

struct GameOverScene:Scene{
  void render() override{
    tft.fillScreen(COL_BLACK);
    tft.setCursor(0,0); tft.setTextColor(COL_RED);
    tft.setTextSize(3); tft.print(F("GAME OVER"));
    tft.setCursor(0,60); tft.setTextColor(COL_WHITE); tft.setTextSize(2);
    tft.print(F("Press any btn"));
  }
  GameState tick(float,const bool*,const bool* j) override{
    return (j[KEY_UP]||j[KEY_LEFT]||j[KEY_RIGHT]||j[KEY_OPTION])
            ? GameState::MAIN_MENU : GameState::GAME_OVER;
  }
} g_over;

/* ---------- Globals ---------- */
Scene* scenes[] = { &g_loading,&g_menu,&g_game,&g_map,&g_over };
GameState state = GameState::LOADING;

/* ---------- Mini-map helpers ---------- */
static void resetMiniMap(){
  memset(miniMap,0,sizeof(miniMap));
}
static void unlockArea(int x,int y){
  for(int dy=-1;dy<=1;dy++)
    for(int dx=-1;dx<=1;dx++){
      int nx=x+dx, ny=y+dy;
      if(nx>=0&&nx<MAP_WIDTH&&ny>=0&&ny<MAP_HEIGHT)
        miniMap[ny][nx]=1;
    }
}
static void setMini(int x,int y){ miniMap[y][x]=1; unlockArea(x,y); }

/* ---------- Arduino setup / loop ---------- */
void setup(){
  tft.begin(TFT_FREQ); tft.setRotation(3);
  resetMiniMap(); setMini(player.pos.x,player.pos.y);
  scenes[(int)state]->render();   // LOADING splash
  delay(600);                     // brief pause
  state = GameState::MAIN_MENU;
}

static inline float getDelta(){ return 0.02f; }   // fixed dt

void loop(){
  static bool prev[5]={0};
  const bool* now = getButtons();            // replace with real input
  bool just[5];
  for(uint8_t i=0;i<5;i++){ just[i]= now[i] && !prev[i]; prev[i]=now[i]; }

  scenes[(int)state]->render();
  state = scenes[(int)state]->tick(getDelta(),now,just);
}

/* ───── END OF FILE ───── */
