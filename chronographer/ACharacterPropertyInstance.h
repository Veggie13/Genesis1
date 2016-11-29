#pragma once

#include <QString>

class Character;
class ACharacterPropertyView;
class QWidget;
class Session;

class ACharacterPropertyInstance
{
public:
    ACharacterPropertyInstance( Session* session, Character* pOwner )
        : _pOwner(pOwner), _session(session) { }
    virtual ~ACharacterPropertyInstance() { }

    virtual ACharacterPropertyView* CreateView( QWidget* parent = 0 ) = 0;
    virtual QString Display() const = 0;

protected:
    Session* SessionContext() const { return _session; }
    Character* Owner() const { return _pOwner; }

private:
    Character* _pOwner;
    Session* _session;

};
