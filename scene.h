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

    bool loadProc(const std::wstring& filename, QGLWidget *glwidget, TextureManager& texManager);
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
