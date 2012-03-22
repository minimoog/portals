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
