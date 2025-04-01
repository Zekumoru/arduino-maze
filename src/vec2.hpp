#ifndef VEC2_H
#define VEC2_H

struct vec2
{
    float x,y;
    
    vec2();
    vec2(float _x, float _y);
    vec2(float value);
    vec2(const vec2& vec);
    vec2(const vec2&& vec);
    vec2(int _x, int _y);
    
    void operator=(const vec2& vec);
    void operator=(const vec2&& vec);
    void operator=(const int value) = delete;
    void operator=(const float valule) = delete;
    
    
    vec2 operator+(const vec2& vec);
    vec2 operator+(const int value);
    vec2 operator+(const float value);
    
    vec2 operator-(const vec2& vec);
    vec2 operator-(const int value);
    vec2 operator-(const float value);
    
    vec2 operator*(const vec2& vec) = delete;
    vec2 operator*(const int value);
    vec2 operator*(const float value);
    
    vec2 operator/(const vec2& vec) = delete;
    vec2 operator/(float value);
    vec2 operator/(const int value);
    friend vec2 operator/(const vec2& vec, float value);
    
    static float dot(const vec2& left, const vec2& right);
};



#endif // !VEC2_H