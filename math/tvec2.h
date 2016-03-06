/*
* Copyright (c) 2008 Antonie Jovanoski <minimoog77_at_gmail.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#ifndef TVEC2_H
#define TVEC2_H

#include <math.h>

struct TVec2
{
    TVec2() : x(0.0f), y(0.0f) { }
    TVec2(float x, float y) : x(x), y(y) { }
    TVec2(const float* xy) : x(xy[0]), y(xy[1]) { }


    TVec2& operator *= (const float& lambda)
    {
        x *= lambda;
        y *= lambda;
        return *this;
    }

    TVec2& operator -= (const TVec2& u)
    {
        x -= u.x;
        y -= u.y;
        return *this;
    }

    TVec2& operator += (const TVec2& u)
    {
        x += u.x;
        y += u.y;
        return *this;
    }

    float operator[] (int i) const
    {
        return vec_array[i];
    }

    float length() const
    {
        return sqrtf(x * x + y * y);
    }

    union {
        struct {
            float x, y;
        };
        struct {
            float s, t;
        };
        float vec_array[2];
    };
};

inline const TVec2 operator + (const TVec2& u, const TVec2& v)
{
    return TVec2(u.x + v.x, u.y + v.y);
}

inline const TVec2 operator - (const TVec2& u, const TVec2& v)
{
    return TVec2(u.x - v.x, u.y - v.y);
}

inline const TVec2 operator * (const float s, const TVec2& v)
{
    return TVec2(s * v.x, s * v.y);
}

inline const TVec2 operator / (const TVec2& v, const float s)
{
    return TVec2(v.x / s, v.y / s);
}

inline const TVec2 operator * (const TVec2& u, const TVec2& v)
{
    return TVec2(u.x * v.x, u.y * v.y);
}

inline TVec2& scale(TVec2& u, float s)
{
    u.x *= s;
    u.y *= s;
    return u;
}

inline TVec2& normalize(TVec2& u)
{
    float norm = sqrtf(u.x * u.x + u.y * u.y);
    return scale(u, 1.0f / norm);
}

#endif //TVEC2_H
