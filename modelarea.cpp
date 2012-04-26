#include "modelarea.h"
#include "procutil.h"

#define BUFFER_OFFSET(i) (reinterpret_cast<void*>(i))

ModelArea::ModelArea()
    :   m_rendered(false)
{
}

ModelArea::~ModelArea()
{
}


bool ModelArea::readFromFile(std::wifstream &file, TextureManager &tm)
{
    int numSurfaces = ProcUtil::ProcGetNextInt(file);

    for (int i = 0; i < numSurfaces; ++i) {
        Surface surface;

        std::wstring textureName = ProcUtil::ProcGetNextString(file);
        textureName += L".dds";

        surface.texture = tm.loadTexture(textureName);

        if (!surface.texture) {
            return false;
        }

        surface.numVerts = ProcUtil::ProcGetNextInt(file);
        surface.numIndexes = ProcUtil::ProcGetNextInt(file);

        Vertex *vertices = new Vertex[surface.numVerts];
        unsigned int *indexes = new unsigned int[surface.numIndexes];

        for (int j = 0; j < surface.numVerts; ++j) {
            vertices[j].x  = ProcUtil::ProcGetNextFloat(file);
            vertices[j].y  = ProcUtil::ProcGetNextFloat(file);
            vertices[j].z  = ProcUtil::ProcGetNextFloat(file);
            vertices[j].s  = ProcUtil::ProcGetNextFloat(file);
            vertices[j].t  = ProcUtil::ProcGetNextFloat(file);
            vertices[j].nx = ProcUtil::ProcGetNextFloat(file);
            vertices[j].ny = ProcUtil::ProcGetNextFloat(file);
            vertices[j].nz = ProcUtil::ProcGetNextFloat(file);
        }

        for (int j = 0; j < surface.numIndexes; ++j) {
            indexes[j] = ProcUtil::ProcGetNextInt(file);
        }

        //vertex buffer
        glGenBuffers(1, &surface.vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, surface.vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, surface.numVerts * sizeof(Vertex), vertices, GL_STATIC_DRAW);

        //index buffer
        glGenBuffers(1, &surface.indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, surface.indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, surface.numIndexes * sizeof(unsigned int), indexes, GL_STATIC_DRAW);

        m_surfaces.push_back(surface);

        delete []vertices;
        delete []indexes;

        return true;
    }

    return false;
}

void ModelArea::setProgram(GLuint program)
{
    m_program = program;

    glUseProgram(program);

    m_posAttribIndex = glGetAttribLocation(m_program, "vertexPosition");
    m_texAttribIndex = glGetAttribLocation(m_program, "vertexTexCoord");
    //m_normalAttribIndex = glGetAttribLocation(m_program, "vertexNormal");
    m_texUniform = glGetUniformLocation(m_program, "texture");

    glUniform1i(m_texUniform, 0);
}

void ModelArea::render()
{
    glUseProgram(m_program);

    if (!m_rendered) {
        for (int i = 0; i < m_surfaces.size(); ++i) {

            glBindTexture(GL_TEXTURE_2D, m_surfaces[i].texture);

            glBindBuffer(GL_ARRAY_BUFFER, m_surfaces[i].vertexBuffer);
            glVertexAttribPointer(m_posAttribIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
            glVertexAttribPointer(m_texAttribIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(3 * sizeof(float)));
            //glVertexAttribPointer(m_normalAttribIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(5 * sizeof(float)));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_surfaces[i].indexBuffer);

            glDrawElements(GL_TRIANGLES, m_surfaces[i].numIndexes, GL_UNSIGNED_BYTE, 0);

        }

        m_rendered = true;
    }
}

void ModelArea::addPortal(const Portal &portal)
{
    m_portals.push_back(portal);
}

void ModelArea::reset()
{
    m_rendered = false;
}

std::vector<Portal>& ModelArea::getPortals()
{
    return m_portals;
}

void ModelArea::release()
{
    for (int i = 0; i < m_surfaces.size(); ++i) {
        glDeleteBuffers(1, &m_surfaces[i].vertexBuffer);
        m_surfaces[i].vertexBuffer = 0;

        glDeleteBuffers(1, &m_surfaces[i].indexBuffer);
        m_surfaces[i].indexBuffer = 0;
    }
}
