#include "widget.h"

Widget::Widget(QWidget *parent) :
    QGLWidget(parent), m_textureManager(this)
{
    makeCurrent();

    GLenum err = glewInit();
    if (GLEW_OK != err) {
      /* Problem: glewInit failed, something is seriously wrong. */
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
}

void Widget::initializeGL()
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    m_scene.loadProc(std::wstring(L"./data/level.proc"), this, m_textureManager);

}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Widget::resizeGL(int w, int h)
{

}

Widget::~Widget()
{
}
