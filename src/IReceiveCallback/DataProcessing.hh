#ifndef DATAPROCESSING_FILE_H
#define DATAPROCESSING_FILE_H

#include "SDICOS/DICOS.h" 

using namespace SDICOS;

class DataProcessingMultipleConnections : public Network::IReceiveCallback
{
public:
 
protected:
    virtual void OnReceiveDicosFileError(const ErrorLog &errorlog, const Utils::SessionData &sessiondata);
 
    virtual void OnReceiveDicosFile(Utils::DicosData<SDICOS::AttributeManager> &manager, const ErrorLog &errorlog);
 
    virtual void OnReceiveDicosFile(Utils::DicosData<CT> &ct, const ErrorLog &errorlog);
    virtual void OnReceiveDicosFile(Utils::DicosData<DX> &dx, const ErrorLog &errorlog);
    virtual void OnReceiveDicosFile(Utils::DicosData<AIT2D> &ait, const ErrorLog &errorlog);
    virtual void OnReceiveDicosFile(Utils::DicosData<AIT3D> &ait, const ErrorLog &errorlog);
    virtual void OnReceiveDicosFile(Utils::DicosData<TDR> &tdr, const ErrorLog &errorlog);
 
    virtual void OnReceiveDicosEcho(const Utils::SessionData& sessiondata, const ErrorLog& errorlog);
};

class DataProcessingConnectionsSpecificClientApplications : public Network::IReceiveCallback
{
public:
 
protected:
    virtual void OnReceiveDicosFileError(const ErrorLog &errorlog, const Utils::SessionData &sessiondata);
 
    virtual void OnReceiveDicosFile(Utils::DicosData<SDICOS::AttributeManager> &manager, const ErrorLog &errorlog);
 
    virtual void OnReceiveDicosFile(Utils::DicosData<CT> &ct, const ErrorLog &errorlog);
    virtual void OnReceiveDicosFile(Utils::DicosData<DX> &dx, const ErrorLog &errorlog);
    virtual void OnReceiveDicosFile(Utils::DicosData<AIT2D> &ait, const ErrorLog &errorlog);
    virtual void OnReceiveDicosFile(Utils::DicosData<AIT3D> &ait, const ErrorLog &errorlog);
    virtual void OnReceiveDicosFile(Utils::DicosData<TDR> &tdr, const ErrorLog &errorlog);
 
    virtual void OnReceiveDicosEcho(const Utils::SessionData& sessiondata, const ErrorLog& errorlog);
};

#endif