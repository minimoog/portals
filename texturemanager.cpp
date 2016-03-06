/*
* Copyright (c) 2008 Antonie Jovanoski <minimoog77_at_gmail.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include "texturemanager.h"
#include <QImage>
#include <QGLWidget>

TextureManager::TextureManager(QGLWidget *glWidget)
    : m_glWidget(glWidget)
{
}

GLuint TextureManager::loadTexture(const std::wstring &filename)
{
    QString fn = QString::fromStdWString(filename);

    if (m_textures.contains(fn)) {
        return m_textures[fn];
    } else {

#ifdef Q_WS_X11
        QImage image;
        image.load(fn);

        GLuint textureid = m_glWidget->bindTexture(image);
#else
        GLuint textureid = m_glWidget->bindTexture(fn);
#endif

        if (textureid)
            m_textures[fn] = textureid;

        return textureid;
    }

    return 0;
}

void TextureManager::release()
{
    QHashIterator<QString, GLuint> iter(m_textures);

    while (iter.hasNext()) {
        iter.next();

        GLuint textureid = iter.value();

        m_glWidget->deleteTexture(textureid);
    }
}
