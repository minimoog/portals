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

#include "tvec3.h"

TVec3& scale(TVec3& u, const float s)
{
	u.x *= s;
	u.y *= s;
	u.z *= s;
	return u;
}

TVec3& normalize(TVec3& u)
{
	float norm = sqrtf(u.x * u.x + u.y * u.y + u.z * u.z);
	return scale(u, 1.0f / norm);
}

TVec3& cross(TVec3& u, const TVec3& v, const TVec3& w)
{
	u.x = v.y * w.z - v.z * w.y;
	u.y = v.z * w.x - v.x * w.z;
	u.z = v.x * w.y - v.y * w.x;
	return u;
}

float dot(const TVec3& v, const TVec3& w)
{
	return v.x * w.x + v.y * w.y + v.z * w.z;
}

TVec3& sub(TVec3& u, const TVec3& v, const TVec3& w)
{
	u.x = v.x - w.x;
	u.y = v.y - w.y;
	u.z = v.z - w.z;
	return u;
}

TVec3& add(TVec3& u, const TVec3& v, const TVec3& w)
{
	u.x = v.x + w.x;
	u.y = v.y + w.y;
	u.z = v.z + w.z;
	return u;
}

