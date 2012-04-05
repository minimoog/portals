#ifndef WIDGET_H
#define WIDGET_H

#include <QGLWidget>

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
};

#endif // WIDGET_H
