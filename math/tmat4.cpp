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

#include "tmat4.h"

//----------------------------------------------------------------
// ctr
// creates matrix identity
//----------------------------------------------------------------

TMat4::TMat4() :
    a00(1.0f), a01(0.0f), a02(0.0f), a03(0.0f),
    a10(0.0f), a11(1.0f), a12(0.0f), a13(0.0f),
    a20(0.0f), a21(0.0f), a22(1.0f), a23(0.0f),
    a30(0.0f), a31(0.0f), a32(0.0f), a33(1.0f)
{
}

//----------------------------------------------------------------
// ctr matrix from array arr
//----------------------------------------------------------------

TMat4::TMat4(const float *arr) :
    a00(arr[ 0]), a01(arr[ 1]), a02(arr[ 2]), a03(arr[ 3]),
    a10(arr[ 4]), a11(arr[ 5]), a12(arr[ 6]), a13(arr[ 7]),
    a20(arr[ 8]), a21(arr[ 9]), a22(arr[10]), a23(arr[11]),
    a30(arr[12]), a31(arr[13]), a32(arr[14]), a33(arr[15])
{
}

//---------------------------------------------------------------
// ctr matrix from given values
//---------------------------------------------------------------

TMat4::TMat4(const float f0, const float f1, const float f2, const float f3,
             const float f4, const float f5, const float f6, const float f7,
             const float f8, const float f9, const float f10, const float f11,
             const float f12, const float f13, const float f14, const float f15) :
    a00(f0), a01(f1), a02(f2), a03(f3),
    a10(f4), a11(f5), a12(f6), a13(f7),
    a20(f8), a21(f9), a22(f10), a23(f11),
    a30(f12), a31(f13), a32(f14), a33(f15)
{
}

//---------------------------------------------------------------
// returns "i" column
//---------------------------------------------------------------

const TVec4 TMat4::col(const int i) const
{
    return TVec4(mat_array[i], mat_array[i+4], mat_array[i+8], mat_array[i+12]);
}

//---------------------------------------------------------------
// returns "i" row
//---------------------------------------------------------------

const TVec4 TMat4::row(const int i) const
{
    return TVec4(&mat_array[4*i]);
}

//---------------------------------------------------------------
// returns (i, j) element
//---------------------------------------------------------------

float TMat4::operator ()(const int i, const int j) const
{
    return mat_array[4*i+j];
}

//---------------------------------------------------------------
// returns reference to (i, j) element
//---------------------------------------------------------------

float& TMat4::operator ()(const int i, const int j)
{
    return mat_array[4*i+j];
}

//---------------------------------------------------------------
// sets "i" column
//---------------------------------------------------------------

void TMat4::set_col(int i, const TVec4 &v)
{
    mat_array[i] = v.x;
    mat_array[i+4] = v.y;
    mat_array[i+8] = v.z;
    mat_array[i+12] = v.w;
}

//---------------------------------------------------------------
// sets "i" row
//---------------------------------------------------------------

void TMat4::set_row(int i, const TVec4 &v)
{
    mat_array[4*i] = v.x;
    mat_array[4*i+1] = v.y;
    mat_array[4*i+2] = v.z;
    mat_array[4*i+3] = v.w;
}

//----------------------------------------------------
// transposes the matrix
//----------------------------------------------------

void TMat4::transpose()
{
    float tmp;

    tmp = a01;
    a01 = a10;
    a10 = tmp;

    tmp = a02;
    a02 = a20;
    a20 = tmp;

    tmp = a03;
    a03 = a30;
    a30 = tmp;

    tmp = a12;
    a12 = a21;
    a21 = tmp;

    tmp = a13;
    a13 = a31;
    a31 = tmp;

    tmp = a23;
    a23 = a32;
    a32 = tmp;
}

//----------------------------------------------------
// get rotation part to matrix M
//----------------------------------------------------

TMat3& TMat4::get_rot(TMat3 &M) const
{
    M.a00 = a00; M.a01 = a01; M.a02 = a02;
    M.a10 = a10; M.a11 = a11; M.a12 = a12;
    M.a20 = a20; M.a21 = a21; M.a22 = a22;
    return M;
}

//----------------------------------------------------
// get rotation part to quat q
//----------------------------------------------------

TQuat& TMat4::get_rot(TQuat &q) const
{
    TMat3 m;
    get_rot(m);
    q.fromMatrix(m);
    return q;
}

//-----------------------------------------------------
// set rotation part from quat q
//-----------------------------------------------------

void TMat4::set_rot(const TQuat &q)
{
    TMat3 m;
    q.toMatrix(m);
    set_rot(m);
}

//-----------------------------------------------------
// set rotation part from rotation matrix M
//-----------------------------------------------------

void TMat4::set_rot(const TMat3 &M)
{
    a00 = M.a00; a01 = M.a01; a02 = M.a02;
    a10 = M.a10; a11 = M.a11; a12 = M.a12;
    a20 = M.a20; a21 = M.a21; a22 = M.a22;
}

//-----------------------------------------------------
// set rotation around vector v with angle of rot. theta
//-----------------------------------------------------

void TMat4::set_rot(const float theta, const TVec3 &v)
{
    float ct = cosf(theta);
    float st = sinf(theta);

    float xx = v.x * v.x;
    float yy = v.y * v.y;
    float zz = v.z * v.z;
    float xy = v.x * v.y;
    float xz = v.x * v.z;
    float yz = v.y * v.z;

    a00 = xx + ct * (1.0f - xx);
    a01 = xy - ct * xy + st * v.z;
    a02 = xz - ct * xz - st * v.y;

    a10 = xy - ct * xy - st * v.z;
    a11 = yy + ct * (1.0f - yy);
    a12 = yz - ct * yz + st * v.x;

    a20 = xz - ct * xz + st * v.y;
    a21 = yz - ct * yz + st * v.x;
    a22 = zz + ct * (1.0f - zz);
}

//-----------------------------------------------------
// set translation
//-----------------------------------------------------

void TMat4::set_translation(const TVec3 &t)
{
    a30 = t.x;
    a31 = t.y;
    a32 = t.z;
}

//-----------------------------------------------------
// get translation
//-----------------------------------------------------

TVec3& TMat4::get_translation(TVec3 &t) const
{
    t.x = a30;
    t.y = a31;
    t.z = a32;
    return t;
}

//---------------------------------------------------------------
// inverts the matrix which consist of translations and rotations
//---------------------------------------------------------------

void TMat4::invert_rot_trans()
{
    TMat4 A(*this);	//copy to tmp matrix

    a00 = A.a00;
    a01 = A.a10;
    a02 = A.a20;
    a03 = 0.0f;

    a10 = A.a01;
    a11 = A.a11;
    a12 = A.a21;
    a13 = 0.0f;

    a20 = A.a02;
    a21 = A.a12;
    a22 = A.a22;
    a23 = 0.0f;

    a30 = -(A.a00 * A.a30 + A.a01 * A.a31 + A.a02 * A.a32);
    a31 = -(A.a10 * A.a30 + A.a11 * A.a31 + A.a12 * A.a32);
    a32 = -(A.a20 * A.a30 + A.a21 * A.a31 + A.a22 * A.a32);

    a33 = 1.0f;
}

//--------------------------------------------------------------
// multiply matrix with matrix B
//--------------------------------------------------------------

TMat4 TMat4::operator *(const TMat4 &B) const
{
    TMat4 C;

    C.a00 = a00 * B.a00 + a01 * B.a10 + a02 * B.a20 + a03 * B.a30;
    C.a01 = a00 * B.a01 + a01 * B.a11 + a02 * B.a21 + a03 * B.a31;
    C.a02 = a00 * B.a02 + a01 * B.a12 + a02 * B.a22 + a03 * B.a32;
    C.a03 = a00 * B.a03 + a01 * B.a13 + a02 * B.a23 + a03 * B.a33;

    C.a10 = a10 * B.a00 + a11 * B.a10 + a12 * B.a20 + a13 * B.a30;
    C.a11 = a10 * B.a01 + a11 * B.a11 + a12 * B.a21 + a13 * B.a31;
    C.a12 = a10 * B.a02 + a11 * B.a12 + a12 * B.a22 + a13 * B.a32;
    C.a13 = a10 * B.a03 + a11 * B.a13 + a12 * B.a23 + a13 * B.a33;

    C.a20 = a20 * B.a00 + a21 * B.a10 + a22 * B.a20 + a23 * B.a30;
    C.a21 = a20 * B.a01 + a21 * B.a11 + a22 * B.a21 + a23 * B.a31;
    C.a22 = a20 * B.a02 + a21 * B.a12 + a22 * B.a22 + a23 * B.a32;
    C.a23 = a20 * B.a03 + a21 * B.a13 + a22 * B.a23 + a23 * B.a33;

    C.a30 = a30 * B.a00 + a31 * B.a10 + a32 * B.a20 + a33 * B.a30;
    C.a31 = a30 * B.a01 + a31 * B.a11 + a32 * B.a21 + a33 * B.a31;
    C.a32 = a30 * B.a02 + a31 * B.a12 + a32 * B.a22 + a33 * B.a32;
    C.a33 = a30 * B.a03 + a31 * B.a13 + a32 * B.a23 + a33 * B.a33;

    return C;
}

//-------------------------------------------------------------------
// M * v
//-------------------------------------------------------------------

const TVec4 operator*(const TMat4& M, const TVec4& v)
{
    TVec4 u;
    u.x = M.a00 * v.x + M.a10 * v.y + M.a20 * v.z + M.a30 * v.w;
    u.y = M.a01 * v.x + M.a11 * v.y + M.a21 * v.z + M.a31 * v.w;
    u.z = M.a02 * v.x + M.a12 * v.y + M.a22 * v.z + M.a32 * v.w;
    u.w = M.a03 * v.x + M.a13 * v.y + M.a23 * v.z + M.a33 * v.w;
    return u;
}

//-------------------------------------------------------------------
// v * M
//-------------------------------------------------------------------

const TVec4 operator*(const TVec4& v, const TMat4& M)
{
    TVec4 u;
    u.x = M.a00 * v.x + M.a10 * v.y + M.a20 * v.z + M.a30 * v.w;
    u.y = M.a01 * v.x + M.a11 * v.y + M.a21 * v.z + M.a31 * v.w;
    u.z = M.a02 * v.x + M.a12 * v.y + M.a22 * v.z + M.a32 * v.w;
    u.w = M.a03 * v.x + M.a13 * v.y + M.a23 * v.z + M.a33 * v.w;
    return u;
}

//-------------------------------------------------------------------
//  u = M * v
//-------------------------------------------------------------------

TVec4& mult(TVec4& u, const TMat4& M, const TVec4& v)
{
    u.x = M.a00 * v.x + M.a10 * v.y + M.a20 * v.z + M.a30 * v.w;
    u.y = M.a01 * v.x + M.a11 * v.y + M.a21 * v.z + M.a31 * v.w;
    u.z = M.a02 * v.x + M.a12 * v.y + M.a22 * v.z + M.a32 * v.w;
    u.w = M.a03 * v.x + M.a13 * v.y + M.a23 * v.z + M.a33 * v.w;
    return u;
}

//-------------------------------------------------------------------
// u = v * M
//-------------------------------------------------------------------

TVec4& mult(TVec4& u, const TVec4& v, const TMat4& M)
{
    //FIX IT
    u.x = M.a00 * v.x + M.a10 * v.y + M.a20 * v.z + M.a30 * v.w;
    u.y = M.a01 * v.x + M.a11 * v.y + M.a21 * v.z + M.a31 * v.w;
    u.z = M.a02 * v.x + M.a12 * v.y + M.a22 * v.z + M.a32 * v.w;
    u.w = M.a03 * v.x + M.a13 * v.y + M.a23 * v.z + M.a33 * v.w;
    return u;
}

//--------------------------------------------------------------------
// C = A * B
//--------------------------------------------------------------------

TMat4& mult(TMat4& C, const TMat4& A, const TMat4& B)
{
    C.a00 = A.a00 * B.a00 + A.a01 * B.a10 + A.a02 * B.a20 + A.a03 * B.a30;
    C.a01 = A.a00 * B.a01 + A.a01 * B.a11 + A.a02 * B.a21 + A.a03 * B.a31;
    C.a02 = A.a00 * B.a02 + A.a01 * B.a12 + A.a02 * B.a22 + A.a03 * B.a32;
    C.a03 = A.a00 * B.a03 + A.a01 * B.a13 + A.a02 * B.a23 + A.a03 * B.a33;

    C.a10 = A.a10 * B.a00 + A.a11 * B.a10 + A.a12 * B.a20 + A.a13 * B.a30;
    C.a11 = A.a10 * B.a01 + A.a11 * B.a11 + A.a12 * B.a21 + A.a13 * B.a31;
    C.a12 = A.a10 * B.a02 + A.a11 * B.a12 + A.a12 * B.a22 + A.a13 * B.a32;
    C.a13 = A.a10 * B.a03 + A.a11 * B.a13 + A.a12 * B.a23 + A.a13 * B.a33;

    C.a20 = A.a20 * B.a00 + A.a21 * B.a10 + A.a22 * B.a20 + A.a23 * B.a30;
    C.a21 = A.a20 * B.a01 + A.a21 * B.a11 + A.a22 * B.a21 + A.a23 * B.a31;
    C.a22 = A.a20 * B.a02 + A.a21 * B.a12 + A.a22 * B.a22 + A.a23 * B.a32;
    C.a23 = A.a20 * B.a03 + A.a21 * B.a13 + A.a22 * B.a23 + A.a23 * B.a33;

    C.a30 = A.a30 * B.a00 + A.a31 * B.a10 + A.a32 * B.a20 + A.a33 * B.a30;
    C.a31 = A.a30 * B.a01 + A.a31 * B.a11 + A.a32 * B.a21 + A.a33 * B.a31;
    C.a32 = A.a30 * B.a02 + A.a31 * B.a12 + A.a32 * B.a22 + A.a33 * B.a32;
    C.a33 = A.a30 * B.a03 + A.a31 * B.a13 + A.a32 * B.a23 + A.a33 * B.a33;

    return C;
}

//---------------------------------------------------------------------
// B is transpose of A
//---------------------------------------------------------------------

TMat4& transpose(TMat4& B, const TMat4& A)
{
    B.a00 = A.a00;
    B.a01 = A.a10;
    B.a02 = A.a20;
    B.a03 = A.a30;
    B.a10 = A.a01;
    B.a11 = A.a11;
    B.a12 = A.a21;
    B.a13 = A.a31;
    B.a20 = A.a02;
    B.a21 = A.a12;
    B.a22 = A.a22;
    B.a23 = A.a32;
    B.a30 = A.a03;
    B.a31 = A.a13;
    B.a32 = A.a23;
    B.a33 = A.a33;
    return B;
}

TMat4& invert(TMat4& B, const TMat4& /* A */)
{
    //sometime, some day will be coded
    return B;
}

//----------------------------------------------------------------
// B is invert of A (only translations and rotations)
//----------------------------------------------------------------

TMat4& invert_rot_trans(TMat4& B, const TMat4& A)
{
    //assumption, A consist only from translation and rotation
    B.a00 = A.a00;
    B.a01 = A.a10;
    B.a02 = A.a20;
    B.a03 = 0.0f;

    B.a10 = A.a01;
    B.a11 = A.a11;
    B.a12 = A.a21;
    B.a13 = 0.0f;

    B.a20 = A.a02;
    B.a21 = A.a12;
    B.a22 = A.a22;
    B.a23 = 0.0f;

    B.a30 = -(A.a00 * A.a30 + A.a01 * A.a31 + A.a02 * A.a32);
    B.a31 = -(A.a10 * A.a30 + A.a11 * A.a31 + A.a12 * A.a32);
    B.a32 = -(A.a20 * A.a30 + A.a21 * A.a31 + A.a22 * A.a32);

    B.a33 = 1.0f;

    return B;
}

