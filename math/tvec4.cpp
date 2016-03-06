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

#include "tvec4.h"

TVec4& scale(TVec4& u, const float s)
{
    u.x *= s;
    u.y *= s;
    u.z *= s;
    u.w *= s;
    return u;
}

TVec4& normalize(TVec4& u)
{
    float norm = sqrtf(u.x * u.x + u.y * u.y + u.z * u.z + u.w * u.w);
    return scale(u, 1.0f / norm); 
}

float& dot(float& u, const TVec4& v, const TVec4& w)
{
    u = v.x * w.x + v.y * w.y + v.z * w.z + v.w * w.w;
    return u;
}

float dot(const TVec4& v, const TVec4& w)
{
    return v.x * w.x + v.y * w.y + v.z * w.z + v.w * w.w;
}
