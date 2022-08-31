#include "SphereObject.h"

#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <cmath>
//#include <iostream>


SphereObject::SphereObject():
    m_vbo(QOpenGLBuffer::VertexBuffer),
    m_ebo(QOpenGLBuffer::IndexBuffer)
{


    SphereMesh s(10.0f, 18, 12);
    s.setFaceColors({Qt::blue, Qt::red, Qt::yellow, Qt::green, Qt::magenta, Qt::darkCyan});
    //s.setColor(Qt::blue);
    Transform3d transf;
    transf.setTranslation(0,20,0);
    s.transform(transf.toMatrix());
    m_spheres.push_back(s);

    SphereMesh s2(30.0f, 36, 24);
    //s2.setColor(Qt::red);
    s2.setFaceColors({Qt::yellow, Qt::green, Qt::magenta, Qt::darkCyan, Qt::blue, Qt::red});
    transf.setTranslation(80, 20, 0);
    s2.transform(transf.toMatrix());
    m_spheres.push_back(s2);

    //unsigned int NSpheres = m_spheres.size();

    unsigned int vertexCount = 0, indexCount = 0;
    for (SphereMesh & sm : m_spheres){
        vertexCount += sm.getVertexCount();
        indexCount += sm.getIndexCount();
    }
    m_vertexBufferData.resize(vertexCount);
    m_elementBufferData.resize(indexCount);

//    m_vertexBufferData.resize(NSpheres * s.getVertexCount());
//    m_elementBufferData.resize(NSpheres * s.getIndexCount());//???

    Vertex * vertexBuffer = m_vertexBufferData.data();
    vertexCount = 0; indexCount = 0;
    GLuint * elementBuffer = m_elementBufferData.data();
    //unsigned int elementsCount = 0;
    for (const SphereMesh & sm : m_spheres){
        sm.copy2Buffer(vertexBuffer, elementBuffer, vertexCount, indexCount);
//        vertexCount += sm.getVertexCount();
//        indexCount += sm.getIndexCount();
    }

}

void SphereObject::create(QOpenGLShaderProgram * shaderProgramm){
    m_vao.create();
    m_vao.bind();


    // create and bind vertex buffer
    m_vbo.create();
    m_vbo.bind();
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    int vertexMemSize = m_vertexBufferData.size() * sizeof(Vertex);
    qDebug() << "SphereObject - VertexBuffer size =" << vertexMemSize/1024.0 << "kByte";
    m_vbo.allocate(m_vertexBufferData.data(), vertexMemSize);

    // create and bind element buffer
    m_ebo.create();
    m_ebo.bind();
    m_ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    int elementMemSize = m_elementBufferData.size()*sizeof(GLuint);
    qDebug() << "SphereObject - ElementBuffer size =" << elementMemSize/1024.0 << "kByte";
    m_ebo.allocate(m_elementBufferData.data(), elementMemSize);

    // set shader attributes
    // tell shader program we have two data arrays to be used as input to the shaders

    // index 0 = position
    shaderProgramm->enableAttributeArray(0); // array with index/id 0
    shaderProgramm->setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(Vertex));
    // index 1 = color
    shaderProgramm->enableAttributeArray(1); // array with index/id 1
    shaderProgramm->setAttributeBuffer(1, GL_FLOAT, offsetof(Vertex, r), 3, sizeof(Vertex));//r?

    // Release (unbind) all
    m_vao.release();
    m_vbo.release();
    m_ebo.release();
}

void SphereObject::destroy() {
    m_vao.destroy();
    m_vbo.destroy();
    m_ebo.destroy();
}

void SphereObject::render() {
    // set the geometry ("position" and "color" arrays)
    m_vao.bind();

    // now draw the sphere by drawing individual triangles
    // - GL_TRIANGLES - draw individual triangles via elements
    glDrawElements(GL_TRIANGLES, m_elementBufferData.size(), GL_UNSIGNED_INT, nullptr);
    // release vertices again
    m_vao.release();
}

