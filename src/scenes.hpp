#ifndef SCENES_HPP
#define SCENES_HPP


#include "scenes.hpp"
#include "vec2.hpp"
#include "player.hpp"
#include "defines.hpp"

#define TITLE_SCREEN "../path/file.bmp"

#include "defines.hpp"



class Scene
{
public:
    Scene() = default;

    virtual void render() = 0;
    virtual GameState processInput() = 0;

protected:
    void clearScreen()
    {
        //TODO : call to clear pixel buffer with black
    }
};

//if the image has a pointer to data should be declared here globally to be used by mainmenu aswell

static Player player(vec2((MAP_WIDTH - 1) / 2.0f, (MAP_HEIGHT - 1) / 2.0f));

int map[MAP_HEIGHT][MAP_WIDTH] = 
{
    { }
};

int unconveredMap [MAP_HEIGHT][MAP_WIDTH];

class Loading : public Scene
{
public:

    Loading()
    {
        //calls to load the image
        //set text pos
    }

    virtual GameState processInput() override
    {
        return GameState::LOADING;
    }

    virtual void render() override
    {
        clearScreen();
        //call to render the image
        //call to render the text "Loading..."
    }

private:
    //imageData Data; ???
    vec2 textPos;

};

class MainMenu : public Scene
{
public:
    MainMenu()
    {
        //call to load image
    }

    virtual void render() override
    {
        clearScreen();
        //call to render image
        //call to render text "Press a button to start"
    }

    virtual GameState processInput()
    {
        bool input = false;
        //handle input

        while(!input)
        {
            //read input
            Buttons button; // = call to func that return a button pressed
            if (button)
            {
                input = true;
            }

            //sleep??
        }
        
        return GameState::GAME_VIEW;
    }
};

class MazeGame : public Scene
{
public:
    MazeGame()
    {
        //set all values to 0
    }

    virtual void render() override
    {
        clearScreen();
        //ray casting
    }

    virtual GameState processInput() override
    {
        bool input = false;
        bool gameOver = false;
        GameState newState = GameState::GAME_VIEW;
        Buttons keyPressed = Buttons::NONE;

        while (!input)
        {
            //TODO: get input
            switch (keyPressed)
            {
            case NONE:
                break;
            case KEY_UP:
                player.movePlayer(1.0f);
                input = true;
                if (map[(int)player.pos.y][(int)player.pos.x] == END)
                    newState = GameState::GAME_OVER;

                break;
                
            case KEY_LEFT:
                player.rotate(-90);
                input = true;
                break;

            case KEY_RIGHT:
                player.rotate(90);
                input = true;
                break;

            case KEY_OPTION:
                newState = GameState::MAP_VIEW;
                input = true;
                break;
            }
            
            //maybe this should be done in the gameover class
            if (newState == GameState::GAME_OVER)
            {
                //reset discovered map
                //reset player pos
                //reset player dir
            }
        }

        return newState;
    }

};

#endif