#include "portal.h"
#include "procutil.h"

Portal::Portal()
{
}

Portal::~Portal()
{
}

void Portal::addPoint(const TVec3 &p)
{
    m_points.push_back(p);
}

// TODO: Floating point errors

void Portal::clipPortal(TPlane &plane)
{
    if (m_clippedPoints.empty())
        return;

    TVec3Array newClippedPoints;

    for (size_t i = 0; i < m_clippedPoints.size() - 1; ++i) {
        TVec3 vp = m_clippedPoints[i];
        TVec3 vn = m_clippedPoints[i + 1];
        TVec4 pl = plane.getPlaneVector();

        float lDotVp = vp.x * pl.x + vp.y * pl.y + vp.z * pl.z + pl.w;
        float lDotVn = vn.x * pl.x + vn.y * pl.y + vn.z * pl.z + pl.w;

        if (lDotVp > 0.0f) { //Front
            newClippedPoints.push_back(vp);

            if (lDotVn < 0.0f) {    //next vertex back, new clip vertex
                float den = pl.x * (vp.x - vn.x) + pl.y * (vp.y  - vn.y) + pl.z * (vp.z - vn.z);
                float t = lDotVp / den;
                float x = vp.x + t * (vn.x - vp.x);
                float y = vp.y + t * (vn.y - vp.y);
                float z = vp.z + t * (vn.z - vp.z);

                TVec3 vnew(x, y, z);

                newClippedPoints.push_back(vnew);
            }
        } else {    //Back
            if (lDotVn > 0.0f) {    //new vertex
                float den = pl.x * (vp.x - vn.x) + pl.y * (vp.y  - vn.y) + pl.z * (vp.z - vn.z);
                float t = lDotVp / den;
                float x = vp.x + t * (vn.x - vp.x);
                float y = vp.y + t * (vn.y - vp.y);
                float z = vp.z + t * (vn.z - vp.z);

                TVec3 vnew(x, y, z);

                newClippedPoints.push_back(vnew);
            }
        }
    }

    if (!newClippedPoints.empty())
        newClippedPoints.push_back(newClippedPoints[0]);

    m_clippedPoints.assign(newClippedPoints.begin(), newClippedPoints.end());
}

bool Portal::isEmpty() const
{
    return m_clippedPoints.empty();
}

void Portal::reverse()
{
    std::reverse(m_points.begin(), m_points.end());
    std::reverse(m_clippedPoints.begin(), m_clippedPoints.end());

    //swap areas
    int tmp = m_areaNeg;
    m_areaNeg = m_areaPos;
    m_areaPos = tmp;
}

void Portal::reset()
{
    m_clippedPoints.assign(m_points.begin(), m_points.end());
    m_clippedPoints.push_back(m_clippedPoints[0]);
}

void Portal::read(std::wifstream& file)
{
    int numPoints = ProcUtil::ProcGetNextInt(file);
    m_areaPos = ProcUtil::ProcGetNextInt(file);
    m_areaNeg = ProcUtil::ProcGetNextInt(file);

    for (int i = 0; i < numPoints; ++i){
        float px = ProcUtil::ProcGetNextFloat(file);
        float py = ProcUtil::ProcGetNextFloat(file);
        float pz = ProcUtil::ProcGetNextFloat(file);

        TVec3 point(px, py, pz);

        m_points.push_back(point);
        m_clippedPoints.push_back(point);
    }

    m_clippedPoints.push_back(m_points[0]);	//first -> last
}

int Portal::getAreaPos() const
{
    return m_areaPos;
}

int Portal::getAreaNeg() const
{
    return m_areaNeg;
}

const TVec3Array& Portal::getClippedPoints()
{
    return m_clippedPoints;
}
