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

#include "tvec4.h"

TVec4& scale(TVec4& u, const float s)
{
    u.x *= s;
    u.y *= s;
    u.z *= s;
    u.w *= s;
    return u;
}

TVec4& normalize(TVec4& u)
{
    float norm = sqrtf(u.x * u.x + u.y * u.y + u.z * u.z + u.w * u.w);
    return scale(u, 1.0f / norm); 
}

float& dot(float& u, const TVec4& v, const TVec4& w)
{
    u = v.x * w.x + v.y * w.y + v.z * w.z + v.w * w.w;
    return u;
}

float dot(const TVec4& v, const TVec4& w)
{
    return v.x * w.x + v.y * w.y + v.z * w.z + v.w * w.w;
}
