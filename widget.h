#ifndef WIDGET_H
#define WIDGET_H

#include <GL/glew.h>
#include <QGLWidget>
#include "texturemanager.h"
#include "scene.h"
#include "kamera.h"

namespace Ui {
class Widget;
}

class Widget : public QGLWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    static void checkShader(GLuint shader);
    static void checkProgram(GLuint program);
    static void glError(const char *file, int line);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    TextureManager m_textureManager;
    Scene m_scene;
    GLint m_ViewMatrix;
    GLint m_ProjectionMatrix;
    Kamera m_kamera;
};

#endif // WIDGET_H
