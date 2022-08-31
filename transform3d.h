#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

class Transform3d{

public:
    Transform3d();

    //transforms
    void translate(const QVector3D &dt);
    void translate(float dx, float dy, float dz);
    void scale(const QVector3D &ds);
    void scale(float dx, float dy, float dz);
    void scale(float factor);
    void rotate(const QQuaternion &dr);
    void rotate(float angle, const QVector3D &axis);
    void rotate(float angle, float ax, float ay, float az);
    void grow(const QVector3D &ds);
    void grow(float dx, float dy, float dz);
    void grow(float factor);

    void setTranslation(const QVector3D &t);
    void setTranslation(float x, float y, float z);
    void setScale(const QVector3D &s);
    void setScale(float x, float y, float z);
    void setScale(float k);
    void setRotation(const QQuaternion &r);
    void setRotation(float angle, const QVector3D &axis);
    void setRotation(float angle, float ax, float ay, float az);

    // accessors
    const QVector3D& translation() const;
    const QVector3D& scale() const;
    const QQuaternion& rotation() const;
    const QMatrix4x4& toMatrix() const;


protected:

    QVector3D m_translation;
    QVector3D m_scale;
    QQuaternion m_rotation;
    mutable QMatrix4x4 m_world; // is updated in the const toMatrix() function
    mutable bool m_dirty;

};

Q_DECLARE_TYPEINFO(Transform3d, Q_MOVABLE_TYPE);

inline Transform3d::Transform3d() : m_scale(1.0f, 1.0f, 1.0f), m_dirty(true) {}

// Transform By (Add/Scale)
inline void Transform3d::translate(float dx, float dy,float dz) { translate(QVector3D(dx, dy, dz)); }
inline void Transform3d::scale(float dx, float dy,float dz) { scale(QVector3D(dx, dy, dz)); }
inline void Transform3d::scale(float factor) { scale(QVector3D(factor, factor, factor)); }
inline void Transform3d::rotate(float angle, const QVector3D &axis) { rotate(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void Transform3d::rotate(float angle, float ax, float ay,float az) { rotate(QQuaternion::fromAxisAndAngle(ax, ay, az, angle)); }
inline void Transform3d::grow(float dx, float dy, float dz) { grow(QVector3D(dx, dy, dz)); }
inline void Transform3d::grow(float factor) { grow(QVector3D(factor, factor, factor)); }

// Transform To (Setters)
inline void Transform3d::setTranslation(float x, float y, float z) { setTranslation(QVector3D(x, y, z)); }
inline void Transform3d::setScale(float x, float y, float z) { setScale(QVector3D(x, y, z)); }
inline void Transform3d::setScale(float k) { setScale(QVector3D(k, k, k)); }
inline void Transform3d::setRotation(float angle, const QVector3D &axis) { setRotation(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void Transform3d::setRotation(float angle, float ax, float ay, float az) { setRotation(QQuaternion::fromAxisAndAngle(ax, ay, az, angle)); }

// Accessors
inline const QVector3D& Transform3d::translation() const { return m_translation; }
inline const QVector3D& Transform3d::scale() const { return m_scale; }
inline const QQuaternion& Transform3d::rotation() const { return m_rotation; }


#endif // TRANSFORM3D_H
