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
    glClearColor(0.0, 0.0, 0.0, 1.0);
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

    glBindAttribLocation(program, 0, "vertexPosition");
    glBindAttribLocation(program, 1, "vertexTexCoord");

    glLinkProgram(program);
    checkProgram(program);

    m_scene.setProgram(program);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    m_ViewMatrix = glGetUniformLocation(program, "viewMatrix");
    m_ProjectionMatrix = glGetUniformLocation(program,"projectionMatrix");

    TVec3 at(2558.0f, -1779.0f, 76.0f);
    TVec3 eye(2558.0f, -1759.0f, 76.0f);
    TVec3 up(0.0f, 0.0f, 1.0f);

    m_kamera.lookat(eye.vec_array, at.vec_array, up.vec_array);
    m_kamera.setPerspectiveViewFOV(float(3.14 * 0.25), float(width()) / float(height()), 0.1f, 5000.0f);

    glUniformMatrix4fv(m_ProjectionMatrix, 1, GL_FALSE, m_kamera.getProjMatrix());
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniformMatrix4fv(m_ViewMatrix, 1, GL_FALSE, m_kamera.getViewMatrix().mat_array);

    m_scene.render(m_kamera);

    glError(__FILE__, __LINE__);
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

void Widget::glError(const char *file, int line)
{
    GLenum err (glGetError());

    while (err!=GL_NO_ERROR) {
        QString error;

        switch(err) {
        case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
        case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
        case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
        case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
        }

        qDebug() << "GL_" << error << " - " << file << ":" << line;

        err=glGetError();
    }
}
