#ifndef I_TITLECARRIER_H
#define I_TITLECARRIER_H

#include <QMetaType>
#include <QString>


class I_TitleCarrier
{
public:
    virtual ~I_TitleCarrier() { }
    virtual const QString& Title() = 0;
};
Q_DECLARE_METATYPE(I_TitleCarrier*)

#endif
