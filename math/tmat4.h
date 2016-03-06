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

#ifndef TMAT4_H
#define TMAT4_H

#include "tvec3.h"
#include "tvec4.h"
#include "tquat.h"
#include "tmat3.h"

struct TMat4
{
    //ctr
    TMat4();
    TMat4(const float* arr);
    TMat4(const float f0,  const float f1,  const float f2,  const float f3,
          const float f4,  const float f5,  const float f6,  const float f7,
          const float f8,  const float f9,  const float f10, const float f11,
          const float f12, const float f13, const float f14, const float f15);

    const TVec4 col(const int i) const;
    const TVec4 row(const int i) const;
    float operator() (const int i, const int j) const;
    float& operator() (const int i, const int j);
    void set_col(int i, const TVec4& v);
    void set_row(int i, const TVec4& v);

    void transpose();

    TMat3& get_rot(TMat3& M) const;
    TQuat& get_rot(TQuat& q) const;
    void set_rot(const TQuat& q);
    void set_rot(const TMat3& M);
    void set_rot(const float theta, const TVec3& v);

    void set_translation(const TVec3& t);
    TVec3& get_translation(TVec3& t) const;

    void invert_rot_trans();

    TMat4 operator*(const TMat4& B) const;

    union{
        struct{
            float a00, a01, a02, a03;
            float a10, a11, a12, a13;
            float a20, a21, a22, a23;
            float a30, a31, a32, a33;
        };
        struct{
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };
        float mat_array[16];
    };
};

const TVec4 operator*(const TMat4& M, const TVec4& v);
const TVec4 operator*(const TVec4& v, const TMat4& M);

TVec4& mult(TVec4& u, const TMat4& M, const TVec4& v);
TVec4& mult(TVec4& u, const TVec4& v, const TMat4& M);
TMat4& mult(TMat4& C, const TMat4& A, const TMat4& B);
TMat4& transpose(TMat4& B, const TMat4& A);
TMat4& invert(TMat4& B, const TMat4& A);
TMat4& invert_rot_trans(TMat4& B, const TMat4& A);

#endif
