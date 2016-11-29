#ifndef AMBIENCEVERSION_H
#define AMBIENCEVERSION_H

#include <QString>


class AmbienceVersion
{
public:
    static const AmbienceVersion CURRENT_VERSION;


    AmbienceVersion(const QString& versionString);

    QString GetVersionString() const;

    unsigned int GetMajor() const;
    unsigned int GetMinor() const;
    unsigned int GetRevision() const;

    bool IsBeta() const;
    bool IsAlpha() const;
    bool IsValid() const;
    bool IsRelease() const;
    bool IsCurrent() const;

    bool operator == (const AmbienceVersion& right) const;
    bool operator <  (const AmbienceVersion& right) const;
    bool operator >  (const AmbienceVersion& right) const;
    bool operator != (const AmbienceVersion& right) const;
    bool operator <= (const AmbienceVersion& right) const;
    bool operator >= (const AmbienceVersion& right) const;

private:
    unsigned int m_versionValue;


    static unsigned int ComputeVersionValue(const QString& versionString);

    static const char VERSION_FORMAT[];
    static const char INVALID_VERSION[];

};

#endif
