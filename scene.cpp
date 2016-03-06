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

#include "scene.h"
#include <fstream>
#include <string>
#include "procutil.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

bool Scene::loadProc(const char * filename, QGLWidget *glwidget, TextureManager &texManager)
{
    std::wifstream file(filename);
    std::wstring s;
    std::vector<Portal> portals;

    if (!file)
        return false;

    while (file >> s) {
        if (s == L"model") {
            std::wstring nameArea = ProcUtil::ProcGetNextString(file);

            ModelArea area;
            if (!area.readFromFile(file, texManager))
                return false;

            m_areas.push_back(area);
        } else if (s == L"interAreaPortals") {
            int numAreas = ProcUtil::ProcGetNextInt(file);
            int numPortals = ProcUtil::ProcGetNextInt(file);

            for (int i = 0; i < numPortals; ++i) {
                Portal portal;
                portal.read(file);
                portals.push_back(portal);
            }
        } else if (s == L"nodes") {
            m_nodes.read(file);
        }
    }

    file.close();

    for (int i = 0; i < portals.size(); ++i) {
        int ap = portals[i].getAreaPos();
        m_areas[ap].addPortal(portals[i]);

        int an = portals[i].getAreaNeg();
        portals[i].reverse();
        m_areas[an].addPortal(portals[i]);
    }

    return true;
}

bool Scene::clipPortal(Portal &firstPortal, Portal &secondPortal, TVec3 &cameraPosition)
{
    TVec3Array points = firstPortal.getClippedPoints();

    //near plane clipping
    TPlane nearPlane(points[0], points[1], points[2]);

    secondPortal.clipPortal(nearPlane);

    if (secondPortal.isEmpty())
        return false;

    for (int i = 0; i < points.size() - 1; ++i) {
        TPlane clipPlane(cameraPosition, points[i], points[i+1]);
        secondPortal.clipPortal(clipPlane);

        if (secondPortal.isEmpty())
            return false;
    }

    return true;
}

void Scene::constructViewPortal(Portal &viewPortal, Kamera &camera)
{
    TVec3 cameraPos(camera.getEyePos());
    TVec3 cameraDir = camera.getDirection();
    TVec3 cameraUp = camera.getUp();
    TVec3 cameraRight = camera.getRight();

    float hn2 = camera.getHeightNearPlane() / 2.0f;
    float wn2 = camera.getWidthNearPlane() / 2.0f;
    float nr = camera.getZNearPlane();

    TVec3 nc = cameraPos + nr * cameraDir;

    TVec3 uphn2 = hn2 * cameraUp;
    TVec3 rightwn2 = wn2 * cameraRight;

    TVec3 ntl = nc + uphn2 - rightwn2;
    TVec3 ntr = nc + uphn2 + rightwn2;
    TVec3 nbl = nc - uphn2 - rightwn2;
    TVec3 nbr = nc - uphn2 + rightwn2;

    viewPortal.addPoint(ntl);
    viewPortal.addPoint(nbl);
    viewPortal.addPoint(nbr);
    viewPortal.addPoint(ntr);

    viewPortal.reset();
}

void Scene::renderRecursive(int area, Portal &throughPortal, Kamera &kamera)
{
    std::vector<Portal> portals = m_areas[area].getPortals();

    for (int i = 0; i < portals.size(); ++i) {
        portals[i].reset();

        TVec3Array p = portals[i].getClippedPoints();
        TPlane plane(p[2], p[1], p[0]);

        if (plane.isFrontBack(kamera.getEyePos()) == -1)
            continue;

        clipPortal(throughPortal, portals[i], kamera.getEyePos());

        if (!portals[i].isEmpty())
            renderRecursive(portals[i].getAreaNeg(), portals[i], kamera);

        m_areas[area].render();
    }
}

void Scene::render(Kamera& kamera)
{
    for (int i = 0; i < m_areas.size(); ++i)
        m_areas[i].reset();

    int area = m_nodes.getArea(kamera.getEyePos());

    if (area >= 0) {
        for (int i = 0; i < m_areas.size(); ++i)
            m_areas[i].render();
    } else {
        area = -1 - area;

        Portal viewPortal;
        constructViewPortal(viewPortal, kamera);

        renderRecursive(area, viewPortal, kamera);
    }
}

void Scene::setProgram(GLuint program)
{
    //This is setting same programs for every model and surfaces... Just as example

    for (int i = 0; i < m_areas.size(); ++i)
        m_areas[i].setProgram(program);
}

void Scene::release()
{
    std::vector<ModelArea>::iterator it;

    for (it = m_areas.begin(); it < m_areas.end(); ++it)
        it->release();
}
