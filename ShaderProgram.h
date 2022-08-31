#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QString>
#include <QStringList>

QT_BEGIN_NAMESPACE
class QOpenGLShaderProgram;
QT_END_NAMESPACE


class ShaderProgram
{
public:
    ShaderProgram();
    ShaderProgram(const QString & vertexShaderFilePath, const QString & fragmentShaderFilePath);

    /*! Creates shader program, compiles and links the programs. */
    void create();
    /*! Destroys OpenGL resources, OpenGL context must be made current before this function is callded! */
    void destroy();

    void bind();

    /*! Access to the native shader program. */
    QOpenGLShaderProgram * shaderProgram() { return m_program; }

    /*! Path to vertex shader program, used in create(). */
    QString		m_vertexShaderFilePath;
    /*! Path to fragment shader program, used in create(). */
    QString		m_fragmentShaderFilePath;


    // Note: Uniform-Handling is pretty simple, probably better to wrap that somehow.

    /*! List of uniform values to be resolved. Values is used in create(). */
    QStringList	m_uniformNames;

    /*! Holds uniform Ids to be used in conjunction with setUniformValue(). */
    QList<int>	m_uniformIDs;

private:
    /*! The wrapped native QOpenGLShaderProgram. */
    QOpenGLShaderProgram	*m_program;
};

#endif // SHADERPROGRAM_H
