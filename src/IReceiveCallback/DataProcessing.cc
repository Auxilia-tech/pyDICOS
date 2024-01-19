#include "DataProcessing.hh"


void DataProcessingMultipleConnections::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog)
{
    // The following are a few examples of what to do with the data:
    // -Write to a file using the function 'ct->Write()'
    // -Access data through several of the 'get' functions
    // -Gain ownership of data for processing later using the function 'ct.TakeOwnership()'
    // -Gain ownership of Tag-Level API with original data using the function 'ct.TakeOwnershipOriginal()'
 
    //Gain ownership of data for processing later using the function 'ct.TakeOwnership()'
    //If ownership is not taken with this function, the data is deleted when the function exits.
    SDICOS::CT *pCT = S_NULL;
    ct.TakeOwnership(pCT);
    DELETE_POINTER(pCT);
 
    //Gain ownership of original Tag-Level API data for processing later using the function 'ct.TakeOwnershipOriginal()'
    //If ownership is not taken with this function, the data is deleted when the function exits.
    SDICOS::AttributeManager *pmanagerOriginal = S_NULL;
    ct.TakeOwnershipOriginal(pmanagerOriginal);
    DELETE_POINTER(pmanagerOriginal);
 
    //Print connection information
    std::cout<<ct.GetClientIP().Get()<<std::endl;   //Client IP address that sent the data
    std::cout<<ct.GetServerIP().Get()<<std::endl;   //Server IP address that received the data
    std::cout<<ct.GetServerPort()<<std::endl;       //Server port number
}
 
// [User-Level API] Process all DX modalities received by the server
void DataProcessingMultipleConnections::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog)
{
    // The following are a few examples of what to do with the data:
    // -Write to a file using the function 'dx->Write()'
    // -Access data through several of the 'get' functions
    // -Gain ownership of data for processing later using the function 'dx.TakeOwnership()'
    // -Gain ownership of Tag-Level API with original data using the function 'dx.TakeOwnershipOriginal()'
}
 
// [User-Level API] Process all AIT 2D modalities received by the server
void DataProcessingMultipleConnections::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog)
{
    // The following are a few examples of what to do with the data:
    // -Write to a file using the function 'ait->Write()'
    // -Access data through several of the 'get' functions
    // -Gain ownership of data for processing later using the function 'ait.TakeOwnership()'
}
 
// [User-Level API] Process all AIT 3D modalities received by the server
void DataProcessingMultipleConnections::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog &errorlog)
{
    // The following are a few examples of what to do with the data:
    // -Write to a file using the function 'ait->Write()'
    // -Access data through several of the 'get' functions
    // -Gain ownership of data for processing later using the function 'ait.TakeOwnership()'
    // -Gain ownership of Tag-Level API with original data using the function 'ait.TakeOwnershipOriginal()'
}
 
// [User-Level API] Process all TDR modalities received by the server
void DataProcessingMultipleConnections::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr, const SDICOS::ErrorLog &errorlog)
{
    // The following are a few examples of what to do with the data:
    // -Write to a file using the function 'tdr->Write()'
    // -Access data through several of the 'get' functions
    // -Gain ownership of data for processing later using the function 'tdr.TakeOwnership()'
    // -Gain ownership of Tag-Level API with original data using the function 'ait.TakeOwnershipOriginal()'
}
 
// This function is only called when an error occurred during the DICOS network session
// that prevented any modalities from being processed. Overriding this function is required by any derived class.
void DataProcessingMultipleConnections::OnReceiveDicosFileError(const SDICOS::ErrorLog &errorlog, const SDICOS::Utils::SessionData &sessiondata)
{
    //Check the error log for errors and warnings with 'errorlog.GetErrorLog()'
    //or write error log to file 'errorlog.WriteLog()'
    //or print out the error
    std::cout<<errorlog<<std::endl;
}
 
// This function is only called when the host receives a C-Echo from a client
void DataProcessingMultipleConnections::OnReceiveDicosEcho(const SDICOS::Utils::SessionData& sessiondata, const SDICOS::ErrorLog& errorlog)
{
    //Below are examples of how to identify which client sent the c-echo
    sessiondata.m_dsClientAppName;
    sessiondata.m_dsClientIP;
    sessiondata.m_nClientPort;
}
 
// [Tag-Level API] Process DICOS data at received by the server
void DataProcessingMultipleConnections::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AttributeManager> &manager, const SDICOS::ErrorLog &errorlog)
{
    // The following are a few examples of what to do with the data:
    // -Write to a file using the function 'manager->Write()'
    // -Access data using the 'manager->FindAttribute()' functions
}


 
// This function is only called when an error occurred during the DICOS network session
// that prevented any modalities from being processed. Overriding this function is required by any derived class.
void DataProcessingConnectionsSpecificClientApplications::OnReceiveDicosFileError(const SDICOS::ErrorLog &errorlog, const SDICOS::Utils::SessionData &sessiondata)
{
    //Check the error log for errors and warnings with 'errorlog.GetErrorLog()'
    //or write error log to file 'errorlog.WriteLog()'
    //or print out the error
    std::cout<<errorlog<<std::endl;
}


void DataProcessingConnectionsSpecificClientApplications::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AttributeManager> &manager, const SDICOS::ErrorLog &errorlog)
{
      // The following are a few examples of what to do with the data:
    // -Write to a file using the function 'manager->Write()'
    // -Access data using the 'manager->FindAttribute()' functions
 
    //Gain ownership of data for processing later using the function 'manager.TakeOwnership()'
    //If ownership is not taken with this function, the data is deleted when the function exits.
    SDICOS::AttributeManager *pmanager = S_NULL;
    manager.TakeOwnership(pmanager);
    DELETE_POINTER(pmanager);
 
    //Print connection information
    std::cout<<manager.GetClientIP().Get()<<std::endl;  //Client IP address that sent the data
    std::cout<<manager.GetServerIP().Get()<<std::endl;  //Server IP address that received the data
    std::cout<<manager.GetServerPort()<<std::endl;      //Server port number
}
 

void DataProcessingConnectionsSpecificClientApplications::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog)
{
    // The following are a few examples of what to do with the data:
    // -Write to a file using the function 'ct->Write()'
    // -Access data through several of the 'get' functions
    // -Gain ownership of data for processing later using the function 'ct.TakeOwnership()'
}
 
// [User-Level API] Process all DX modalities received by the server
void DataProcessingConnectionsSpecificClientApplications::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog)
{
    // The following are a few examples of what to do with the data:
    // -Write to a file using the function 'dx->Write()'
    // -Access data through several of the 'get' functions
    // -Gain ownership of data for processing later using the function 'dx.TakeOwnership()'
}
 
// [User-Level API] Process all AIT 2D modalities received by the server
void DataProcessingConnectionsSpecificClientApplications::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog)
{
    // The following are a few examples of what to do with the data:
    // -Write to a file using the function 'ait->Write()'
    // -Access data through several of the 'get' functions
    // -Gain ownership of data for processing later using the function 'ait.TakeOwnership()'
}
 
// [User-Level API] Process all AIT 3D modalities received by the server
void DataProcessingConnectionsSpecificClientApplications::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog &errorlog)
{
    // The following are a few examples of what to do with the data:
    // -Write to a file using the function 'ait->Write()'
    // -Access data through several of the 'get' functions
    // -Gain ownership of data for processing later using the function 'ait.TakeOwnership()'
}
 
// [User-Level API] Process all TDR modalities received by the server
void DataProcessingConnectionsSpecificClientApplications::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr, const SDICOS::ErrorLog &errorlog)
{
    // The following are a few examples of what to do with the data:
    // -Write to a file using the function 'tdr->Write()'
    // -Access data through several of the 'get' functions
    // -Gain ownership of data for processing later using the function 'tdr.TakeOwnership()'
}
 