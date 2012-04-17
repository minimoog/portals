#include "texturemanager.h"
#include <QImage>
#include <QGLWidget>

TextureManager::TextureManager(QGLWidget *glWidget)
    : m_glWidget(glWidget)
{
}

GLuint TextureManager::loadTexture(const std::wstring &filename)
{
    m_glWidget->makeCurrent();

    QString fn = QString::fromStdWString(filename);

    if (m_textures.contains(fn)) {
        return m_textures[fn];
    } else {
        QImage img;

        if (img.load(fn)) {
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

            m_textures[fn] = texture;
        }
    }

    return 0;
}

void TextureManager::release()
{
    m_glWidget->makeCurrent();

    QHashIterator<QString, GLuint> iter(m_textures);

    while (iter.hasNext()) {
        iter.next();

        GLuint texture = iter.value();

        glDeleteTextures(1, &texture);
    }
}
