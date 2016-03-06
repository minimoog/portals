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
