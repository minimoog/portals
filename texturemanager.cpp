#include "texturemanager.h"
#include <QImage>
#include <QGLWidget>

TextureManager::TextureManager(QGLWidget *glWidget)
    : m_glWidget(glWidget)
{
}

GLuint TextureManager::loadTexture(const std::wstring &filename)
{
    QString fn = QString::fromStdWString(filename);

    if (m_textures.contains(fn)) {
        return m_textures[fn];
    } else {
        GLuint textureid = m_glWidget->bindTexture(fn);

        if (textureid)
            m_textures[fn] = textureid;

        return textureid;
    }

    return 0;
}

void TextureManager::release()
{
    QHashIterator<QString, GLuint> iter(m_textures);

    while (iter.hasNext()) {
        iter.next();

        GLuint textureid = iter.value();

        m_glWidget->deleteTexture(textureid);
    }
}
