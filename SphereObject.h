#ifndef SPHEREOBJECT_H
#define SPHEREOBJECT_H

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <vector>

QT_BEGIN_NAMESPACE
class QOpenGLShaderProgram;//
QT_END_NAMESPACE

#include <SphereMesh.h>

class SphereObject
{
public:
    SphereObject();


    void create(QOpenGLShaderProgram* shaderProgram);
    void destroy();
    void render();

    std::vector<SphereMesh> m_spheres;

    std::vector<Vertex> m_vertexBufferData;
    std::vector<GLuint> m_elementBufferData;

    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLBuffer m_ebo;

protected:

private:

};

#endif // SPHEREOBJECT_H
