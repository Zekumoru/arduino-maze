#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "vec2.hpp"

extern float cosLT[];
extern float sinLT[];

class Player
{
public:
    Player(vec2 &&_pos)
    {
        pos = _pos;
        m_fov = 75.0f;
        dir = vec2(0.0f, 1.0f);
        cameraPlane = vec2(m_fov, 0.0f);
    }

    void movePlayer(float distance)
    {
        pos.x += distance * dir.x;
        pos.y += distance * dir.y;
    };

    void rotate(int angle)
    {
        m_angle += angle;
        m_angle %= 360;

        dir.x = cosLT[m_angle];
        dir.y = sinLT[m_angle];

        rotateCamera(m_angle);
    }

    vec2 pos;
    vec2 dir;
    vec2 cameraPlane;

private:
    int m_angle;

    float m_fov; // need to choose witch one to use

    void rotateCamera(int _angle)
    {
        int angle = _angle + 90;
        angle %= 360;

        cameraPlane.x = cameraPlane.x * cosLT[_angle] - sinLT[_angle] * cameraPlane.y;
        cameraPlane.y = cameraPlane.x * sinLT[_angle] + cosLT[_angle] * cameraPlane.y;
    }
};

#endif // !PLAYER_HPP
