#ifndef I_IMPORTTARGET_H
#define I_IMPORTTARGET_H

class A_SoundImport;

class I_ImportTarget
{
public:
    I_ImportTarget() { }
    virtual ~I_ImportTarget() { }

    virtual void AddImport(A_SoundImport* import) = 0;

};

#endif
