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

#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>
#include <iostream>
#include "texturemanager.h"
#include "modelarea.h"
#include "bsptree.h"
#include "portal.h"
#include "kamera.h"

class Scene
{
public:
    Scene();
    ~Scene();

    bool loadProc(const char * filename, QGLWidget *glwidget, TextureManager& texManager);
    void renderRecursive(int area, Portal& throughPortal, Kamera& kamera);
    void render(Kamera& camera);
    void release();

    void setProgram(GLuint program);

private:
    std::vector<ModelArea> m_areas;
    BspTree m_nodes;

    bool clipPortal(Portal& firstPortal, Portal& secondPortal, TVec3& cameraPosition);
    void constructViewPortal(Portal& viewPortal, Kamera& camera);
};

#endif // SCENE_H
