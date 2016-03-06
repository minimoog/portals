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

#include "bsptree.h"
#include "procutil.h"

BspTree::BspTree()
{
}

BspTree::~BspTree()
{
}

/*
 * reads BSP tree from .PROC file
 * file.filepos must point to nodes section of .PROC file
 */

void BspTree::read(std::wifstream &file)
{
    int numNodes = ProcUtil::ProcGetNextInt(file);

    for (int i = 0; i < numNodes; ++i) {
        BspNode node;
        TVec4 plane;

        plane.x = ProcUtil::ProcGetNextFloat(file);
        plane.y = ProcUtil::ProcGetNextFloat(file);
        plane.z = ProcUtil::ProcGetNextFloat(file);
        plane.w = ProcUtil::ProcGetNextFloat(file);

        node.plane = plane;

        node.posChild = ProcUtil::ProcGetNextInt(file);
        node.negChild = ProcUtil::ProcGetNextInt(file);

        m_nodes.push_back(node);
    }
}

/*
 * Returns on which area is position
 * if it's negative aren = - 1 - return_value
 * if it's zero or positive position is outside of map
 */

int BspTree::getArea(const TVec3 &position) const
{
    BspNode node = m_nodes[0];

    while (true) {
        if (node.plane.isFrontBack(position) == 1) {  //front
            if (node.posChild > 0) {    //if there is a next child
                node = m_nodes[node.posChild];
            } else {
                return node.posChild;
            }
        } else { //back
            if (node.negChild > 0) { //next child
                node = m_nodes[node.negChild];
            } else {
                return node.negChild;
            }
        }
    }
}
