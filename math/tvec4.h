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

#ifndef TVEC4_H
#define TVEC4_H

#include "tvec3.h"

struct TVec4
{
    TVec4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
    TVec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    TVec4(const float* xyzw) : x(xyzw[0]), y(xyzw[1]), z(xyzw[2]), w(xyzw[3]) {}
    TVec4(const TVec3& u) : x(u.x), y(u.y), z(u.z), w(1.0f) {}

    TVec4& operator *=(const float& s)
    {
        x*= s;
        y*= s;
        z*= s;
        w*= s;
        return *this;
    }

    TVec4& operator -=(const TVec4& u)
    {
        x-= u.x;
        y-= u.y;
        z-= u.z;
        w-= u.w;
        return *this;
    }

    TVec4& operator +=(const TVec4& u)
    {
        x+= u.x;
        y+= u.y;
        z+= u.z;
        w+= u.w;
        return *this;
    }

    TVec4 operator -() const
    {
        return TVec4(-x, -y, -z, -w);
    }

    float& operator [](int i)
    {
        return vec_array[i];
    }

    float operator [](int i) const
    {
        return vec_array[i];
    }

    union {
        struct {
            float x,y,z,w;
        };
        struct {
            float s,t,r,q;
        };
        float vec_array[4];
    };
};

inline const TVec4 operator+ (const TVec4& u, const TVec4& v)
{
    return TVec4(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}

inline const TVec4 operator- (const TVec4& u, const TVec4& v)
{
    return TVec4(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w);
}

inline const TVec4 operator* (const float s, const TVec4& u)
{
    return TVec4(s * u.x, s * u.y, s * u.z, s * u.w);
}

inline const TVec4 operator/ (const TVec4& u, const float s)
{
    return TVec4(u.x / s, u.y / s, u.z / s, u.w / s);
}

inline const TVec4 operator* (const TVec4& u, const TVec4& v)
{
    return TVec4(u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w);
}

TVec4& scale(TVec4& u, const float s);
TVec4& normalize(TVec4& u);
float& dot(float& u, const TVec4& v, const TVec4& w);
float dot(const TVec4& v, const TVec4& w);

#endif //TVEC4_H
