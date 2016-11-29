#ifndef QEXCEPTION_H
#define QEXCEPTION_H

#include <QString>

#include <exception>


class QException : public std::exception
{
public:
    QException(const QString& msg, int skip = 0);
    virtual ~QException() throw () { }
    virtual const char* what() const throw () { return m_msg.toAscii().data(); }
private:
    QString m_msg;

    static const unsigned LIMIT = 25;
};

#endif
