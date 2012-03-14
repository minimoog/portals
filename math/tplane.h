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
