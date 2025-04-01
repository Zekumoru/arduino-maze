#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "vec2.hpp"

class Player
{
public:
    Player(vec2&& _pos)
    {
        pos = _pos;
    }
    
    void movePlayer(float distance)
    {
        pos.x += distance * m_Dir.x;
        pos.y += distance * m_Dir.y;
    };
    
    void rotate(int angle)
    {
        extern float cosLT[];
        extern float sinLT[];

        m_angle += angle;
        m_angle %= 360;

        m_Dir.x = cosLT[m_angle];
        m_Dir.y = sinLT[m_angle]; 
    }

    vec2 pos;
private:
    vec2 m_Dir;
    int m_angle;

    vec2 cameraPlane; float fov; //need to choose witch one to use
};


#endif // !PLAYER_HPP
