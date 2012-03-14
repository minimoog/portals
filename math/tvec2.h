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

    const float operator[] (int i) const
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
