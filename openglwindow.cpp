#include "OpenGLWindow.h"

#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QPainter>

OpenGLWindow::OpenGLWindow(QWindow *parent)
    : QWindow(parent),
      m_context(nullptr)
{
    setSurfaceType(QWindow::OpenGLSurface);
}

//OpenGLWindow::~OpenGLWindow()
//{

//}

void OpenGLWindow::renderLater() {
    // Schedule an UpdateRequest event in the event loop
    // that will be send with the next VSync.
    requestUpdate(); // call public slot requestUpdate()
}


void OpenGLWindow::renderNow() {
    if (!isExposed())
        return;

    // initialize on first call
    if (m_context == nullptr)
        initOpenGL();

    m_context->makeCurrent(this);

    paintGL(); // call user code

    m_context->swapBuffers(this);
}

bool OpenGLWindow::event(QEvent *event) {
    switch (event->type()) {
    case QEvent::UpdateRequest:
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void OpenGLWindow::exposeEvent(QExposeEvent * /*event*/) {
    qDebug() << "OpenGLWindow::exposeEvent()";
    renderNow(); // update right now
}

void OpenGLWindow::resizeEvent(QResizeEvent * event) {
    qDebug() << "OpenGLWindow::resizeEvent()";
    QWindow::resizeEvent(event);

    // initialize on first call
    if (m_context == nullptr)
        initOpenGL();

    resizeGL(width(), height());
}


void OpenGLWindow::initOpenGL() {
    Q_ASSERT(m_context == nullptr);

    m_context = new QOpenGLContext(this);
    m_context->setFormat(requestedFormat());
    m_context->create();

    m_context->makeCurrent(this);
    Q_ASSERT(m_context->isValid());

    initializeOpenGLFunctions();
    initializeGL(); // call user code
}
