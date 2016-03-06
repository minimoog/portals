/*
* Copyright (c) 2010 Antonie Jovanoski <minimoog77_at_gmail.com>
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

