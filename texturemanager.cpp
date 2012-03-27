#include "texturemanager.h"
#include <QImage>
#include <QGLWidget>

TextureManager::TextureManager(QGLWidget *glWidget)
    : m_glWidget(glWidget)
{
}

GLuint TextureManager::loadTexture(const QString &filename)
{
    if (m_textures.contains(filename)) {
        return m_textures[filename];
    } else {
        QImage img;

        if (img.load(filename)) {
            QImage imgTexture = QGLWidget::convertToGLFormat(img);

            GLuint texture;

            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            glTexImage2D(GL_TEXTURE_2D,
                         0,
                         GL_RGBA,
                         imgTexture.width(),
                         imgTexture.height(),
                         0,
                         GL_RGBA,
                         GL_UNSIGNED_BYTE,
                         imgTexture.bits());

            m_textures[filename] = texture;
        }
    }

    return 0;
}

void TextureManager::release()
{
    QHashIterator<QString, GLuint> iter(m_textures);

    while (iter.hasNext()) {
        iter.next();

        GLuint texture = iter.value();

        glDeleteTextures(1, &texture);
    }
}
