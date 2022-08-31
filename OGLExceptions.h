#ifndef OGLEXCEPTIONS_H
#define OGLEXCEPTIONS_H

#include <stdexcept>
#include <list>

#include <QString>

class OGLExceptions : public std::exception {
public:
    OGLExceptions(const QString & msg);
    OGLExceptions(const QString & msg, const QString & where);
    OGLExceptions(OGLExceptions & previous, const QString & msg);
    OGLExceptions(OGLExceptions & previous, const QString & msg, const QString & where);
    void writeMsgStackToStream(std::ostream & strm) const;

private:
    std::list<std::pair<QString, QString> > m_msgStack;
};

#define FUNCID(x) const char * const FUNC_ID = "[" #x "]"

#endif // OGLEXCEPTIONS_H
