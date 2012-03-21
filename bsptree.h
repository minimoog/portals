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
