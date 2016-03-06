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

#ifndef BSPTREE_H
#define BSPTREE_H

#include <vector>
#include <fstream>
#include <string>
#include "math/tplane.h"
#include "math/tvec3.h"

// BSP Node struct
// negative child number means that it is area (-1 - child)
// 0 is opaque
// positive childe number is a next child

struct BspNode
{
    TPlane plane;
    int posChild;
    int negChild;
};

class BspTree
{
public:
    BspTree();
    ~BspTree();

    void read(std::wifstream& file);

    int getArea(const TVec3& position) const;

private:
    std::vector<BspNode> m_nodes;
};

#endif // BSPTREE_H
