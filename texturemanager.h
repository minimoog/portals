#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <QHash>
#include <QGLWidget>

class TextureManager
{
public:
    TextureManager(QGLWidget *glWidget);
    GLuint loadTexture(const QString& filename);
    void release();

private:
    QGLWidget *m_glWidget;
    QHash<QString, GLuint> m_textures;
};

#endif // TEXTUREMANAGER_H
