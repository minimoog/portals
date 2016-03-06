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

#ifndef TPLANE_H
#define TPLANE_H

#include "tvec4.h"
#include "tvec3.h"

//remark
//plane equation is A * x + B * y + C * z + D = 0

class TPlane
{
public:

    TPlane() : m_planeVector(0.0f, 0.0f, 1.0f, 0.0f) { }
    TPlane(float a, float b, float c, float d) : m_planeVector(a, b, c, d) { }
    TPlane(const TVec4& abcd) : m_planeVector(abcd) { }
    TPlane(const TVec3& normal, float d) : m_planeVector(normal) { m_planeVector.w = d; }

    TPlane(const TVec3& p1, const TVec3& p2, const TVec3& p3);
    //Tplane(const Tvec3& p1, const Tvec3& p2);
    TPlane(const TVec3& n, const TVec3&p);

    void normalize();
    int isFrontBack(const TVec3& p) const;
    float pointDistance(const TVec3& p) const;

    TVec4& getPlaneVector() { return m_planeVector; }

private:
    TVec4 m_planeVector;	//normal, plus D
};

#endif // TPLANE_H
