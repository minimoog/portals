#include "widget.h"
#include <QtDebug>
#include <QFile>

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

    // shader mader
    GLuint program = glCreateProgram();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    QFile vertexFile;
    vertexFile.setFileName("simple.vsh");
    vertexFile.open(QIODevice::ReadOnly);

    QFile fragmentFile;
    fragmentFile.setFileName("simple.fsh");
    fragmentFile.open(QIODevice::ReadOnly);

    QByteArray vertexByteArray = vertexFile.readAll();
    vertexByteArray.append('\0');
    const char *vsSource = vertexByteArray.constData();

    QByteArray fragmentByteArray = fragmentFile.readAll();
    fragmentByteArray.append('\0');
    const char *fsSource = fragmentByteArray.constData();

    glShaderSource(vertexShader, 1, &vsSource, NULL);
    glCompileShader(vertexShader);
    checkShader(vertexShader);

    glShaderSource(fragmentShader, 1, &fsSource, NULL);
    glCompileShader(fragmentShader);
    checkShader(fragmentShader);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    checkProgram(program);

    m_scene.setProgram(program);
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

void Widget::checkShader(GLuint shader)
{
    GLint status;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE)
        qDebug() << "Compile error";
    else
        qDebug() << "Compile ok";

    int loglen;
    char logBuffer[1024];
    glGetShaderInfoLog(shader, sizeof(logBuffer), &loglen, logBuffer);

    if (loglen > 0)
        qDebug() << logBuffer;
}

void Widget::checkProgram(GLuint program)
{
    GLint status;

    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
        qDebug() << "Linker error";
    else
        qDebug() << "Linker ok";

    int loglen;
    char logbuffer[1024];

    glGetProgramInfoLog(program, sizeof(logbuffer), &loglen, logbuffer);
    if (loglen > 0)
        qDebug() << logbuffer;

    glValidateProgram(program);
    glGetProgramInfoLog(program, sizeof(logbuffer), &loglen, logbuffer);

    if (loglen > 0)
        qDebug() << logbuffer;
}
