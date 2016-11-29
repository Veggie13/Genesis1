#include <windows.h>

#include <QDomDocument>
#include <QFile>
#include <QVector>

#include "Character.h"
#include "CustomEvent.h"
#include "IntProperty.h"
#include "ISerializable.h"
#include "Session.h"
#include "XmlSerialElement.h"

int main(int argc, char* argv[])
{
    bool loadData = true;
    bool saveData = !loadData;


    class Doc : public ISerializable
    {
    public:
        QList<CustomEvent::Factory*> eventFactoryList;
        QList<Character*> charList;
        QList<ACharacterProperty*> propList;
        Session* session;

        virtual void Serialize( ISerializer* dest ) const
        {
            QVector<ISerializable*> factoryVec( eventFactoryList.count() );
            qCopy( eventFactoryList.begin(), eventFactoryList.end(), factoryVec.begin() );
            dest->Serialize( "eventFactoryList", factoryVec.toList() );

            QVector<ISerializable*> charVec( charList.count() );
            qCopy( charList.begin(), charList.end(), charVec.begin() );
            dest->Serialize( "charList", charVec.toList() );

            QVector<ISerializable*> propVec( propList.count() );
            qCopy( propList.begin(), propList.end(), propVec.begin() );
            dest->Serialize( "propList", propVec.toList() );

            dest->Serialize( "session", session );
        }

        virtual void Deserialize( const IDeserializer* source )
        {
            QList<IDeserializer*> charDeserial, propDeserial, factoryDeserial;
            source->Deserialize( "charList", charDeserial );
            source->Deserialize( "propList", propDeserial );
            source->Deserialize( "eventFactoryList", factoryDeserial );

            for ( QList<IDeserializer*>::iterator it = charDeserial.begin();
                  it != charDeserial.end();
                  it++ )
            {
                charList.append( new Character( *it ) );
                delete (*it);
            }
            for ( QList<IDeserializer*>::iterator it = propDeserial.begin();
                  it != propDeserial.end();
                  it++ )
            {
                propList.append( ACharacterProperty::IFactory::Deserialize( *it ) );
                delete (*it);
            }
            for ( QList<IDeserializer*>::iterator it = factoryDeserial.begin();
                  it != factoryDeserial.end();
                  it++ )
            {
                eventFactoryList.append( new CustomEvent::Factory( *it ) );
                delete (*it);
            }
            session = new Session( source->SubElement( "session" ) );
        }
    } docObj;

    if ( loadData )
    {
        QFile file("C:\\doc.xml");
        file.open( QIODevice::ReadWrite );
        QDomDocument doc;
        doc.setContent( &file );
        file.close();

        XmlSerialElement el( doc.documentElement() );
        docObj.Deserialize( &el );
    }
    else
    {
        docObj.charList.append( new Character("Bob") );
        docObj.charList.append( new Character("Jim") );
        docObj.charList.append( new Character("Gary") );

        docObj.propList.append( new IntProperty("HP") );

        CustomEvent::Factory& eventFactory = *( new CustomEvent::Factory("Blah") );
        docObj.eventFactoryList.append( &eventFactory );

        docObj.session = new Session();
        Session& session = *(docObj.session);

        session.Start();
        Sleep(500);
        session.PostEvent( eventFactory.Create() );
        Sleep(500);
        session.PostEvent( eventFactory.Create() );
        Sleep(500);
        session.TogglePause();
        Sleep(500);
        session.TogglePause();
        Sleep(500);
        session.PostEvent( eventFactory.Create() );
        Sleep(500);
        session.Stop();
    }

    QDomDocument doc("test");
    doc.appendChild( doc.createElement("doc") );
    XmlSerialElement el( doc.documentElement() );

    docObj.Serialize( &el );

    if ( saveData )
    {
        QFile file("C:\\doc.xml");
        file.open( QIODevice::ReadWrite );
        file.write( doc.toString().toAscii() );
        file.close();
    }
    else
    {
        printf( "%s", doc.toString().toAscii().data() );
    }

    return 0;
}

