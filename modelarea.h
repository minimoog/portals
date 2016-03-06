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

#ifndef MODELAREA_H
#define MODELAREA_H

#include <vector>
#include <fstream>
#include <GL/glew.h>
#include "portal.h"
#include "texturemanager.h"

struct Vertex
{
    float x;
    float y;
    float z;
    float s;
    float t;
    float nx;
    float ny;
    float nz;
};

struct Surface
{
    GLuint  vertexBuffer;
    GLuint  indexBuffer;
    GLuint  texture;

    int numVerts;
    int numIndexes;

    Surface() : vertexBuffer(0), indexBuffer(0), texture(0), numVerts(0), numIndexes(0) { }
};

class ModelArea
{
public:
    ModelArea();
    ~ModelArea();

    void render();
    bool readFromFile(std::wifstream& file, TextureManager& tm);
    void addPortal(const Portal& portal);
    void reset();
    void release();
    std::vector<Portal>& getPortals();
    void setProgram(GLuint program);

private:
    std::vector<Surface> m_surfaces;
    std::vector<Portal> m_portals;
    bool m_rendered;
    GLuint m_program;
    GLint m_posAttribIndex;
    GLint m_texAttribIndex;
    GLint m_normalAttribIndex;
    GLint m_texUniform;
};

#endif // MODELAREA_H
