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
