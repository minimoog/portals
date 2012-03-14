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

#include "tplane.h"

//---------------------------------------------------------------
//construct plane who passes through points p1, p2, p3
//---------------------------------------------------------------

TPlane::TPlane(const TVec3 &p1, const TVec3 &p2, const TVec3 &p3)
{
    TVec3 e2 = p2 - p1;
    TVec3 e3 = p3 - p1;
    TVec3 n = e2 ^ e3;
    n.normalize();

    m_planeVector.x = n.x;
    m_planeVector.y = n.y;
    m_planeVector.z = n.z;
    m_planeVector.w = -dot(n, p1);
}

//construct plane who passes through p1, p2, and origin
/*
Tplane::Tplane(const Tvec3& p1, const Tvec3& p2)
{
    Tvec3 n = p1 ^ p2;
    n.normalize();

    planeVec.x = n.x;
    planeVec.y = n.y;
    planeVec.z = n.z;
    planeVec.w = 0.0;
}
*/

//------------------------------------------------------
//construct plane from normal and passing point p
//assuming n is normalized
//------------------------------------------------------

TPlane::TPlane(const TVec3 &n, const TVec3 &p)
{
    m_planeVector.x = n.x;
    m_planeVector.y = n.y;
    m_planeVector.z = n.z;
    m_planeVector.w = -dot(n, p);
}

//------------------------------------------------------
//normalize plane vector
//------------------------------------------------------

void TPlane::normalize()
{
    TVec3 n(m_planeVector.x, m_planeVector.y, m_planeVector.z);
    float s = n.normalize();

    m_planeVector.x = n.x;
    m_planeVector.y = n.y;
    m_planeVector.z = n.z;
    m_planeVector.w *= s;
}

//-----------------------------------------------------------------
//test if point is in front of the plane, or back
// 1 if Front
// -1 if back
// 0 should be on the plane //TODO
//-----------------------------------------------------------------

//TODO floating point rounding errors

int TPlane::isFrontBack(const TVec3 &p) const
{
    TVec4 pw(p);
    float dist = dot(m_planeVector, pw);

    if (dist > 0)
        return 1;

    return -1;
}

//------------------------------------------------------------------
//return distance from plane
//------------------------------------------------------------------

float TPlane::pointDistance(const TVec3 &p) const
{
    TVec4 pw(p);
    return dot(m_planeVector, p);
}

