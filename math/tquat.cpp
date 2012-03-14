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

#include "tquat.h"

//------------------------------------------------
// ctr
// sets quat to identity
//------------------------------------------------

TQuat::TQuat() : x(0.0f), y(0.0f), z(0.0f), w(1.0f)
{
}

//----------------------------------------------------------------------
// ctr
//----------------------------------------------------------------------

TQuat::TQuat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

//--------------------------------------------------------------------------
// cp ctr
//--------------------------------------------------------------------------

TQuat::TQuat(const TQuat &quat) : x(quat.x), y(quat.y), z(quat.z), w(quat.w)
{
}

//--------------------------------------------------------------------------
// ctr from rotation axis and given angle of rotation
//--------------------------------------------------------------------------

TQuat::TQuat(const TVec3 &axis, float angle)
{
    float len = axis.norm();
    if(len){
        float invLen = 1.0f / len;
        float angle2 = angle / 2.0f;
        float scale = sinf(angle2) * invLen;
        x = scale * axis.x;
        y = scale * axis.y;
        z = scale * axis.z;
        w = cosf(angle2);
    }
}

//------------------------------------------------------------------------
// ctr from given rotation matrix
//------------------------------------------------------------------------

TQuat::TQuat(const TMat3 &rot)
{
    fromMatrix(rot);
}

//------------------------------------------------------------------------

TQuat& TQuat::operator=(const TQuat& quat)
{
    x = quat.x;
    y = quat.y;
    z = quat.z;
    w = quat.w;
    return *this;
}

//------------------------------------------------------------------------

TQuat TQuat::operator-()
{
    return TQuat(-x, -y, -z, w);
}

//------------------------------------------------------------------------

TQuat& TQuat::operator *=(const TQuat &q)
{
    *this = *this * q;
    return *this;
}

//------------------------------------------------------------------------
// Inverse the quaternion
//------------------------------------------------------------------------

void TQuat::inverse()
{
    x = -x;
    y = -y;
    z = -z;
}

//-----------------------------------------------------------------------
// Normalize quaternion
//-----------------------------------------------------------------------

void TQuat::normalize()
{
    float len = sqrtf(x * x + y * y + z * z + w * w);
    if(len > 0){
        float invLen = 1 / len;
        x *= invLen;
        y *= invLen;
        z *= invLen;
        w *= invLen;
    }
}

//----------------------------------------------------------------------
// multiply quaternion
//----------------------------------------------------------------------

void TQuat::multQuat(const TQuat& q)
{
    float tx = w * q.x + x * q.w + y * q.z - z * q.y;
    float ty = w * q.y + y * q.w + z * q.x - x * q.z;
    float tz = w * q.z + z * q.w + x * q.y - y * q.x;
    float tw = w * q.w - x * q.x - y * q.y - z * q.z;

    x = tx;
    y = ty;
    z = tz;
    w = tw;
}

//----------------------------------------------------------------------
// convert rotation matrix to quaternion
//----------------------------------------------------------------------

void TQuat::fromMatrix(const TMat3& mat)
{
    float w4Sqr1 = mat.a00 + mat.a11 + mat.a22;
    float x4Sqr1 = mat.a00 - mat.a22 - mat.a22;
    float y4Sqr1 = mat.a11 - mat.a00 - mat.a22;
    float z4Sqr1 = mat.a22 - mat.a00 - mat.a11;

    int biggestIndex = 0;
    float biggest = w4Sqr1;
    if(x4Sqr1 > biggest){
        biggest = x4Sqr1;
        biggestIndex = 1;
    }
    if(y4Sqr1 > biggest){
        biggest = y4Sqr1;
        biggestIndex = 2;
    }
    if(z4Sqr1 > biggest){
        biggest = z4Sqr1;
        biggestIndex = 3;
    }

    float biggestVal = sqrtf(biggest + 1.0f) * 0.5f;
    float mult = 0.25f / biggestVal;

    switch(biggestIndex){
    case 0:
        w = biggestVal;
        x = (mat.a12 - mat.a21) * mult;
        y = (mat.a20 - mat.a02) * mult;
        z = (mat.a01 - mat.a10) * mult;
        break;
    case 1:
        x = biggestVal;
        w = (mat.a12 - mat.a21) * mult;
        y = (mat.a01 + mat.a10) * mult;
        z = (mat.a20 + mat.a02) * mult;
        break;
    case 2:
        y = biggestVal;
        w = (mat.a20 - mat.a02) * mult;
        x = (mat.a01 + mat.a10) * mult;
        z = (mat.a12 + mat.a21) * mult;
        break;
    case 3:
        z = biggestVal;
        w = (mat.a01 - mat.a10) * mult;
        x = (mat.a20 + mat.a02) * mult;
        y = (mat.a12 + mat.a21) * mult;
        break;
    }
}

//---------------------------------------------------------------
// calc rot. matrix from quat
//---------------------------------------------------------------

void TQuat::ToMatrix(TMat3 &mat) const
{
    float x2 = 2.0f * x;
    float y2 = 2.0f * y;
    float z2 = 2.0f * z;
    float wx = x2 * w;
    float wy = y2 * w;
    float wz = z2 * w;
    float xx = x2 * x;
    float xy = y2 * x;
    float xz = z2 * x;
    float yy = y2 * y;
    float yz = z2 * y;
    float zz = z2 * z;

    mat.a00 = 1.0f - yy - zz;
    mat.a01 = xy + wz;
    mat.a02 = xz - wy;
    mat.a10 = xy - wz;
    mat.a11 = 1.0f - xx - zz;
    mat.a12 = yz + wx;
    mat.a20 = xz + wy;
    mat.a21 = yz - wx;
    mat.a22 = 1 - xx - yy;
}

//----------------------------------------------------------------
// multiply quaternions
//----------------------------------------------------------------

const TQuat operator*(const TQuat& p, const TQuat& q)
{
    return TQuat(p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y,
                 p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z,
                 p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x,
                 p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z);
}

//----------------------------------------------------------------
// multiply quaternions
//----------------------------------------------------------------

TQuat& mult_quats(TQuat& p, const TQuat& q1, const TQuat& q2)
{
    p.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    p.y = q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z;
    p.z = q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x;
    p.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
    return p;
}
