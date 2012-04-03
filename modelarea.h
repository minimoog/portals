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
