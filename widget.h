#ifndef WIDGET_H
#define WIDGET_H

#include <GL/glew.h>
#include <QGLWidget>
#include "texturemanager.h"
#include "scene.h"

namespace Ui {
class Widget;
}

class Widget : public QGLWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    TextureManager m_textureManager;
    Scene m_scene;
};

#endif // WIDGET_H
