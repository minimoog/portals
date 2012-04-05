#include "widget.h"

Widget::Widget(QWidget *parent) :
    QGLWidget(parent)
{
}

void Widget::initializeGL()
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
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
