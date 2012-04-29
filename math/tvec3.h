/* Copyright (c) 2008, Antonie Jovanoski
 *
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
