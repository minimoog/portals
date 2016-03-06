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

#ifndef TMAT3_H
#define TMAT3_H

#include "tvec3.h"

struct TMat3
{
    TMat3() : a00(1.0f), a01(0.0f), a02(0.0f),
        a10(0.0f), a11(1.0f), a12(0.0f),
        a20(0.0f), a21(0.0f), a22(1.0f) {}

    TMat3(const float* ma) : a00(ma[0]), a01(ma[1]), a02(ma[2]),
        a10(ma[3]), a11(ma[4]), a12(ma[5]),
        a20(ma[6]), a21(ma[7]), a22(ma[8]) {}

    TMat3(const float f0, const float f1, const float f2,
          const float f3, const float f4, const float f5,
          const float f6, const float f7, const float f8)
        : a00(f0), a01(f1), a02(f2),
          a10(f3), a11(f4), a12(f5),
          a20(f6), a21(f7), a22(f8) {}

    //returns column
    const TVec3 column(const int i) const
    {
        return TVec3(mat_array[i], mat_array[i+3], mat_array[i+6]);
    }

    //returns row
    const TVec3 row(int i) const
    {
        return TVec3(&mat_array[3*i]);
    }

    //returns i, j element
    const float& operator() (const int& i, const int& j) const
    {
        return mat_array[i * 3 + j];
    }

    float& operator() (const int& i, const int& j)
    {
        return mat_array[i*3+j];
    }

    TMat3& operator*= (const float& lambda)
    {
        for(int i = 0; i < 9; ++i)
            mat_array[i] *= lambda;

        return *this;
    }

    void set_row(int i, const TVec3& v)
    {
        mat_array[3*i] = v.x;
        mat_array[3*i+1] = v.y;
        mat_array[3*i+2] = v.z;
    }

    void set_col(int i, const TVec3& v)
    {
        mat_array[i] = v.x;
        mat_array[i+3] = v.y;
        mat_array[i+6] = v.z;
    }

    union {
        struct {
            float a00, a01, a02;
            float a10, a11, a12;
            float a20, a21, a22;
        };
        float mat_array[9];
    };

};

const TVec3 operator*(const TMat3& M, const TVec3& v);
const TVec3 operator*(const TVec3& v, const TMat3& M);
TVec3& mult(TVec3& u, const TMat3& M, const TVec3& v);
TVec3& mult(TVec3& u, const TVec3& v, const TMat3& M);
TMat3& add(TMat3& A, const TMat3& B);
TMat3& add(TMat3& C, const TMat3& A, const TMat3& B);
TMat3& mult(TMat3& C, const TMat3& A, const TMat3& B);
TMat3& transpose(TMat3& B, const TMat3& A);
TMat3& transpose(TMat3& B);
TMat3& invert(TMat3& B, const TMat3& A);

#endif
