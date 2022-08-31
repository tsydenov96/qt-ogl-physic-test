#ifndef GRIDOBJECT_H
#define GRIDOBJECT_H

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

QT_BEGIN_NAMESPACE
class QOpenGLShaderProgram;
QT_END_NAMESPACE


/*! This class holds all data needed to draw a grid on the screen.
    We have only a coordinate buffer, which holds tightly packed 2 * vec2 (start and end points of lines, xz coords)
    with y=0 implied.
    Grid color is a uniform, as is background color.
    The grid is drawn with the grid shader program, which is passed to the create() function.
*/
class GridObject {
public:
    /*! The function is called during OpenGL initialization, where the OpenGL context is current. */
    void create(QOpenGLShaderProgram * shaderProgramm);
    void destroy();

    /*! Binds the buffer and paints. */
    void render();

    unsigned int				m_bufferSize;

    /*! Wraps an OpenGL VertexArrayObject, that references the vertex coordinates. */
    QOpenGLVertexArrayObject	m_vao;
    /*! Holds positions of grid lines. */
    QOpenGLBuffer				m_vbo;

};

#endif // GRIDOBJECT_H
