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

#include "tmat3.h"

//---------------------------------------------------
// multiply matrix with vector
//---------------------------------------------------

const TVec3 operator*(const TMat3& M, const TVec3& v)
{
    TVec3 u;
    u.x = M.a00 * v.x + M.a01 * v.y + M.a02 * v.z;
    u.y = M.a10 * v.x + M.a11 * v.y + M.a12 * v.z;
    u.z = M.a20 * v.x + M.a21 * v.y + M.a22 * v.z;
    return u;
}

//---------------------------------------------------
// multiply vector with matrix
//---------------------------------------------------

const TVec3 operator*(const TVec3& v, const TMat3& M)
{
    TVec3 u;
    u.x = M.a00 * v.x + M.a10 * v.y + M.a20 * v.z;
    u.y = M.a01 * v.x + M.a11 * v.y + M.a21 * v.z;
    u.z = M.a02 * v.x + M.a21 * v.y + M.a22 * v.z;
    return u;
}

//---------------------------------------------------
// multiply matrix with vector
// result in vector u, and returns the result
//----------------------------------------------------

TVec3& mult(TVec3& u, const TMat3& M, const TVec3& v)
{	
    u.x = M.a00 * v.x + M.a01 * v.y + M.a02 * v.z;
    u.y = M.a10 * v.x + M.a11 * v.y + M.a12 * v.z;
    u.z = M.a20 * v.x + M.a21 * v.y + M.a22 * v.z;
    return u;
}

//--------------------------------------------------
// multiply vector with matrix
// result in vector u, returns the result
//--------------------------------------------------

TVec3& mult(TVec3& u, const TVec3& v, const TMat3& M)
{
    u.x = M.a00 * v.x + M.a10 * v.y + M.a20 * v.z;
    u.y = M.a01 * v.x + M.a11 * v.y + M.a21 * v.z;
    u.z = M.a02 * v.x + M.a12 * v.y + M.a22 * v.z;
    return u;
}

//--------------------------------------------------
// Add matrix B to A
// result in A, return the result
//--------------------------------------------------

TMat3& add(TMat3& A, const TMat3& B)
{
    A.a00 += B.a00;
    A.a01 += B.a01;
    A.a02 += B.a02;
    A.a10 += B.a10;
    A.a11 += B.a11;
    A.a12 += B.a12;
    A.a20 += B.a20;
    A.a21 += B.a21;
    A.a22 += B.a22;
    return A;
}

//--------------------------------------------------
// C = A + B
// result in C, returns the result
//--------------------------------------------------

TMat3& add(TMat3& C, const TMat3& A, const TMat3& B)
{
    C.a00 = A.a00 + B.a00;
    C.a01 = A.a01 + B.a01;
    C.a02 = A.a02 + B.a02;
    C.a10 = A.a10 + B.a10;
    C.a11 = A.a11 + B.a11;
    C.a12 = A.a12 + B.a12;
    C.a20 = A.a20 + B.a20;
    C.a21 = A.a21 + B.a21;
    C.a22 = A.a22 + B.a22;
    return C;
}

//-------------------------------------------------------
// Matrix Multiplication
// returns C = A * B
//-------------------------------------------------------

TMat3& mult(TMat3& C, const TMat3& A, const TMat3& B)
{
    C.a00 = A.a00 * B.a00 + A.a01 * B.a10 + A.a02 * B.a20;
    C.a01 = A.a00 * B.a01 + A.a01 * B.a11 + A.a02 * B.a21;
    C.a02 = A.a00 * B.a02 + A.a01 * B.a12 + A.a02 * B.a22;
    C.a10 = A.a10 * B.a00 + A.a11 * B.a10 + A.a12 * B.a20;
    C.a11 = A.a10 * B.a01 + A.a11 * B.a11 + A.a12 * B.a21;
    C.a12 = A.a10 * B.a02 + A.a11 * B.a12 + A.a12 * B.a22;
    C.a20 = A.a20 * B.a00 + A.a21 * B.a10 + A.a22 * B.a20;
    C.a21 = A.a20 * B.a01 + A.a21 * B.a11 + A.a22 * B.a21;
    C.a22 = A.a20 * B.a02 + A.a21 * B.a12 + A.a22 * B.a22;
    return C;
}

//--------------------------------------------------------
// Transpose the matrix
// result in B, returns the result
//--------------------------------------------------------

TMat3& transpose(TMat3& B, const TMat3& A)
{
    B.a00 = A.a00;
    B.a01 = A.a10;
    B.a02 = A.a20;
    B.a10 = A.a01;
    B.a11 = A.a11;
    B.a12 = A.a21;
    B.a20 = A.a02;
    B.a21 = A.a12;
    B.a22 = A.a22;
    return B;
}

//--------------------------------------------------------
// Transposes the matrix B
//--------------------------------------------------------

TMat3& transpose(TMat3& B)
{
    float tmp;

    tmp = B.a01;
    B.a01 = B.a10;
    B.a10 = tmp;

    tmp = B.a02;
    B.a02 = B.a20;
    B.a20 = tmp;

    tmp = B.a12;
    B.a12 = B.a21;
    B.a21 = tmp;

    return B;
}

static inline float det2x2(float a1, float a2, float b1, float b2)
{
    return a1 * b2 - b1 * a2;
}

//a1 a2 a3
//b1 b2 b3
//c1 c2 c3

static inline float det3x3(float a1, float a2, float a3,
                           float b1, float b2, float b3,
                           float c1, float c2, float c3)
{
    return a1 * det2x2(b2, b3, c2, c3) - b1 * det2x2(a2, a3, c2, c3) + c1 * det2x2(a2, a3, b2, b3);
}

//a00, a01, a02
//a10, a11, a12
//a20, a21, a22

//*************************************************
// TO BE DONE
//*************************************************

TMat3& invert(TMat3& B, const TMat3& /* A */)
{
    //TO BE DONE

    return B;
}
