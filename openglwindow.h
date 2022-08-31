#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QWindow>
//#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLPaintDevice>


class OpenGLWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit OpenGLWindow(QWindow *parent = nullptr);
    //~OpenGLWindow();


//    virtual void render(QPainter *painter);
//    virtual void render();

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event) override;
    void exposeEvent(QExposeEvent *event) override;
    void resizeEvent(QResizeEvent *) override;

    virtual void initializeGL() = 0;

    //virtual void resiseGL(int width, int heght);
    virtual void resizeGL(int width, int height){Q_UNUSED(width) Q_UNUSED(height)}
    virtual void paintGL() = 0;

    QOpenGLContext *m_context = nullptr;
    QOpenGLPaintDevice *m_device = nullptr;


private:
    void initOpenGL();

};
#endif // OPENGLWINDOW_H
