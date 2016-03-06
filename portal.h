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

#ifndef PORTAL_H
#define PORTAL_H

#include <vector>
#include <fstream>
#include <string>
#include "math/tvec3.h"
#include "math/tplane.h"

typedef std::vector<TVec3> TVec3Array;

class Portal
{
public:
    Portal();
    ~Portal();

    void addPoint(const TVec3& p);
    void clipPortal(TPlane &plane);
    void reset();
    bool isEmpty() const;
    void reverse();

    const TVec3Array& getClippedPoints();

    void read(std::wifstream& file);
    int getAreaPos() const;
    int getAreaNeg() const;

private:
    TVec3Array m_points;
    TVec3Array m_clippedPoints;
    int m_areaPos;
    int m_areaNeg;
};

#endif // PORTAL_H
