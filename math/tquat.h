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

#ifndef TQUAT_H
#define TQUAT_H

#include "tvec3.h"
#include "tmat3.h"

struct TQuat
{
    //ctr
    TQuat();
    TQuat(float x, float y, float z, float w);
    TQuat(const TQuat& quat); //cp ctr
    TQuat(const TVec3& axis, float angle);
    TQuat(const TMat3& rot);

    TQuat& operator=(const TQuat& quat);
    TQuat operator-();
    TQuat& operator*=(const TQuat& q);

    void inverse();
    void normalize();
    void multQuat(const TQuat& q);
    void fromMatrix(const TMat3& mat);
    void toMatrix(TMat3& mat) const;

    union {
        struct {
            float x, y, z, w;
        };
        float comp[4];
    };
};

const TQuat operator*(const TQuat& p, const TQuat& q);
TQuat& mult_quats(TQuat& p, const TQuat& q1, const TQuat& q2);

#endif
