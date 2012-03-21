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
