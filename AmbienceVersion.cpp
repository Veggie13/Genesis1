#include <QStringList>

#include "AmbienceVersion.h"


static const char CURRENT_VERSION_STRING[] = "1.2 rev 00 beta";
const AmbienceVersion AmbienceVersion::CURRENT_VERSION(CURRENT_VERSION_STRING);
const char AmbienceVersion::VERSION_FORMAT[] = "%1.%2 rev %3%4";
const char AmbienceVersion::INVALID_VERSION[] = "Invalid version";

AmbienceVersion::AmbienceVersion(const QString& versionString)
:   m_versionValue( ComputeVersionValue(versionString) )
{ }

QString AmbienceVersion::GetVersionString() const
{
    if (!IsValid())
        return INVALID_VERSION;

    return QString(VERSION_FORMAT)
        .arg( GetMajor() )
        .arg( GetMinor() )
        .arg( GetRevision(), 2, 10, QLatin1Char('0') )
        .arg( IsBeta()?" beta":( IsAlpha()?" alpha":"" ) );
}

unsigned int AmbienceVersion::GetMajor() const
{
    return (m_versionValue >> 24) & 0xFF;
}

unsigned int AmbienceVersion::GetMinor() const
{
    return (m_versionValue >> 16) & 0xFF;
}

unsigned int AmbienceVersion::GetRevision() const
{
    return (m_versionValue >> 8 ) & 0xFF;
}

bool AmbienceVersion::IsBeta() const
{
    return (m_versionValue & 0xFF) == 1;
}

bool AmbienceVersion::IsAlpha() const
{
    return (m_versionValue & 0xFF) == 2;
}

bool AmbienceVersion::IsValid() const
{
    return (m_versionValue & 0xFF) != 0xFF;
}

bool AmbienceVersion::IsRelease() const
{
    return (m_versionValue & 0xFF) == 0;
}

bool AmbienceVersion::IsCurrent() const
{
    return (*this) == CURRENT_VERSION;
}

bool AmbienceVersion::operator == (const AmbienceVersion& right) const
{
    return m_versionValue == right.m_versionValue;
}

bool AmbienceVersion::operator < (const AmbienceVersion& right) const
{
    return !IsValid()
        || (GetMajor() < right.GetMajor())
        || (GetMinor() < right.GetMinor())
        || (GetRevision() < right.GetRevision())
        || (IsAlpha() && !right.IsAlpha())
        || (IsBeta() && right.IsRelease());
}

bool AmbienceVersion::operator > (const AmbienceVersion& right) const
{
    return !operator <= (right);
}

bool AmbienceVersion::operator != (const AmbienceVersion& right) const
{
    return !operator == (right);
}

bool AmbienceVersion::operator <= (const AmbienceVersion& right) const
{
    return operator == (right) || operator < (right);
}

bool AmbienceVersion::operator >= (const AmbienceVersion& right) const
{
    return !operator < (right);
}

unsigned int AmbienceVersion::ComputeVersionValue(const QString& versionString)
{
    // TODO: parse string to version value
    QStringList parts = versionString.split(".");
    if (parts.size() != 2)
        return 0xFF;

    bool ok = true;
    unsigned int MM = parts[0].toUInt(&ok);
    if (!ok)
        return 0xFF;

    parts = parts[1].split(" ", QString::SkipEmptyParts);
    if (parts.size() < 3 || parts.size() > 4)
        return 0xFF;

    if (parts[1] != "rev")
        return 0xFF;

    unsigned int Mm = parts[0].toUInt(&ok);
    if (!ok)
        return 0xFF;

    unsigned int rev = parts[2].toUInt(&ok);
    if (!ok)
        return 0xFF;

    unsigned int ba = 0;
    if (parts.size() == 4)
    {
        if (parts[3] == "beta")
            ba = 1;
        else if (parts[3] == "alpha")
            ba = 2;
        else
            return 0xFF;
    }

    return (MM << 24) | (Mm << 16) | (rev << 8) | ba;
}
