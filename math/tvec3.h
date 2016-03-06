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

#ifndef TVEC3_H
#define TVEC3_H

#include "tvec2.h"

struct TVec3
{
    TVec3() : x(0.0f), y(0.0f), z(0.0f) { }
    TVec3(float x, float y, float z) : x(x), y(y), z(z) { }
    TVec3(const float* xyz) : x(xyz[0]), y(xyz[1]), z(xyz[2]) { }
    TVec3(const TVec2& u) : x(u.x), y(u.y), z(1.0f) { }

    TVec3& operator * (const float& s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    TVec3 operator - () const
    {
        return TVec3(-x, -y, -z);
    }

    TVec3& operator -= (const TVec3& u)
    {
        x -= u.x;
        y -= u.y;
        z -= u.z;
        return *this;
    }

    TVec3& operator += (const TVec3& u)
    {
        x += u.x;
        y += u.y;
        z += u.z;
        return *this;
    }

    float normalize()
    {
        float norm = 1 / sqrtf(x * x + y * y + z * z);
        x *= norm;
        y *= norm;
        z *= norm;
        return norm;
    }

    float norm() const
    {
        return sqrtf(x * x + y * y + z * z);
    }

    float& operator[] (int i)
    {
        return vec_array[i];
    }

    float operator[] (int i) const
    {
        return vec_array[i];
    }

    union {
        struct {
            float x, y, z;
        };
        struct {
            float s, t, r;
        };
        float vec_array[3];
    };
};

inline const TVec3 operator + (const TVec3& u, const TVec3& v)
{
    return TVec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline const TVec3 operator - (const TVec3& u, const TVec3& v)
{
    return TVec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

/* cross product */
inline const TVec3 operator ^ (const TVec3& u, const TVec3& v)
{
    return TVec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

inline const TVec3 operator * (const float s, const TVec3& u)
{
    return TVec3(s * u.x, s * u.y, s * u.z);
}

inline const TVec3 operator / (const TVec3& u, const float s)
{
    return TVec3(u.x / s, u.y / s, u.z / s);
}

inline const TVec3 operator * (const TVec3& u, const TVec3& v)
{
    return TVec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

TVec3& scale(TVec3& u, const float s);
TVec3& normalize(TVec3& u);
TVec3& cross(TVec3& u, const TVec3& v, const TVec3& w);
float dot(const TVec3& v, const TVec3& w);
TVec3& sub(TVec3& u, const TVec3& v, const TVec3& w);
TVec3& add(TVec3& u, const TVec3& v, const TVec3& w);

#endif //TVEC3_H
