#include "transform3d.h"

void Transform3d::translate(const QVector3D &dt)
{
    m_dirty = true;
    m_translation += dt;
}

void Transform3d::scale(const QVector3D &ds)
{
    m_dirty = true;
    m_scale *= ds;
}

void Transform3d::rotate(const QQuaternion &dr)
{
    m_dirty = true;
    m_rotation = dr * m_rotation;
}

void Transform3d::grow(const QVector3D &ds)
{
    m_dirty = true;
    m_scale += ds;
}

// Transform To (Setters)
void Transform3d::setTranslation(const QVector3D &t)
{
    m_dirty = true;
    m_translation = t;
}

void Transform3d::setScale(const QVector3D &s)
{
    m_dirty = true;
    m_scale = s;
}

void Transform3d::setRotation(const QQuaternion &r)
{
    m_dirty = true;
    m_rotation = r;
}

// Accessors
const QMatrix4x4 &Transform3d::toMatrix() const {
    if (m_dirty) {
        m_dirty = false;
        m_world.setToIdentity();
        m_world.translate(m_translation);
        m_world.rotate(m_rotation);
        m_world.scale(m_scale);
    }
    return m_world;
}
