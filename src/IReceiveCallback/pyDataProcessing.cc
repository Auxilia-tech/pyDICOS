#include "../headers.hh"
#include "SDICOS/IReceiveCallback.h"
#include "DataProcessing.hh"

using namespace SDICOS;
using namespace Network;


class PyDataProcessingMultipleConnections : public DataProcessingMultipleConnections {
public:
   using DataProcessingMultipleConnections::DataProcessingMultipleConnections;
   void OnReceiveDicosFileError(const SDICOS::ErrorLog &errorlog, const SDICOS::Utils::SessionData &sessiondata) override { 
      PYBIND11_OVERRIDE(void,  DataProcessingMultipleConnections, OnReceiveDicosFileError, errorlog, sessiondata); 
   }
   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AttributeManager> &manager, const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessingMultipleConnections, OnReceiveDicosFile, manager, errorlog); 
    }
   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessingMultipleConnections, OnReceiveDicosFile, ct, errorlog); 
    }
   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessingMultipleConnections, OnReceiveDicosFile, dx, errorlog); 
    }
   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessingMultipleConnections, OnReceiveDicosFile, ait, errorlog); 
    }

   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessingMultipleConnections, OnReceiveDicosFile, ait, errorlog); 
    }

   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr,  const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessingMultipleConnections, OnReceiveDicosFile, tdr, errorlog); 
    }

   void OnReceiveDicosEcho(const SDICOS::Utils::SessionData& sessiondata,  const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessingMultipleConnections, OnReceiveDicosEcho, sessiondata, errorlog); 
    }
};


class PyPublicDataProcessingMultipleConnections : public DataProcessingMultipleConnections {
public:
   using DataProcessingMultipleConnections::OnReceiveDicosFileError;
   using DataProcessingMultipleConnections::OnReceiveDicosFile;
   using DataProcessingMultipleConnections::OnReceiveDicosEcho;
    
};


void export_DataProcessingMultipleConnections(py::module &m)
{
   py::class_<DataProcessingMultipleConnections, Network::IReceiveCallback>(m, "SDICOS::DataProcessingMultipleConnections");
   py::class_<PyDataProcessingMultipleConnections, DataProcessingMultipleConnections, Network::IReceiveCallback>(m, "DataProcessingMultipleConnections")
      .def(py::init<>())
      .def("OnReceiveDicosFileError", py::overload_cast<const SDICOS::ErrorLog&, const SDICOS::Utils::SessionData&>
                                      (&PyPublicDataProcessingMultipleConnections::OnReceiveDicosFileError),
                                      py::arg("errorlog"), 
                                      py::arg("sessiondata"))

      .def("OnReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<SDICOS::AttributeManager> &, const SDICOS::ErrorLog &>
                                      (&PyPublicDataProcessingMultipleConnections::OnReceiveDicosFile),
                                      py::arg("manager"), 
                                      py::arg("errorlog"))

      .def("OnReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<SDICOS::CT> &, const SDICOS::ErrorLog &>
                                      (&PyPublicDataProcessingMultipleConnections::OnReceiveDicosFile),
                                      py::arg("ct"), 
                                      py::arg("errorlog"))

      .def("OnReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<SDICOS::DX> &, const SDICOS::ErrorLog &>
                                      (&PyPublicDataProcessingMultipleConnections::OnReceiveDicosFile),
                                      py::arg("dx"), 
                                      py::arg("errorlog"))    

      .def("OnReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<SDICOS::AIT2D> &, const SDICOS::ErrorLog &>
                                      (&PyPublicDataProcessingMultipleConnections::OnReceiveDicosFile),
                                      py::arg("ait"), 
                                      py::arg("errorlog"))

      .def("OnReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<SDICOS::AIT3D> &, const SDICOS::ErrorLog &>
                                      (&PyPublicDataProcessingMultipleConnections::OnReceiveDicosFile),
                                      py::arg("ait"), 
                                      py::arg("errorlog"))     

      .def("OnReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<SDICOS::TDR> &, const SDICOS::ErrorLog &>
                                      (&PyPublicDataProcessingMultipleConnections::OnReceiveDicosFile),
                                      py::arg("tdr"), 
                                      py::arg("errorlog"))    

      .def("OnReceiveDicosEcho", py::overload_cast<const SDICOS::Utils::SessionData &, const SDICOS::ErrorLog &>
                                      (&PyPublicDataProcessingMultipleConnections::OnReceiveDicosEcho),
                                      py::arg("sessiondata"), 
                                      py::arg("errorlog"));                                                                                                                                                                                
}






class PyDataProcessingConnectionsSpecificClientApplications : public DataProcessingConnectionsSpecificClientApplications {
public:
   using DataProcessingConnectionsSpecificClientApplications::DataProcessingConnectionsSpecificClientApplications;
   void OnReceiveDicosFileError(const SDICOS::ErrorLog &errorlog, const SDICOS::Utils::SessionData &sessiondata) override { 
      PYBIND11_OVERRIDE(void,  DataProcessingConnectionsSpecificClientApplications, OnReceiveDicosFileError, errorlog, sessiondata); 
   }
   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AttributeManager> &manager, const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessingConnectionsSpecificClientApplications, OnReceiveDicosFile, manager, errorlog); 
    }
   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessingConnectionsSpecificClientApplications, OnReceiveDicosFile, ct, errorlog); 
    }
   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessingConnectionsSpecificClientApplications, OnReceiveDicosFile, dx, errorlog); 
    }
   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessingConnectionsSpecificClientApplications, OnReceiveDicosFile, ait, errorlog); 
    }

   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessingConnectionsSpecificClientApplications, OnReceiveDicosFile, ait, errorlog); 
    }

   void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr,  const SDICOS::ErrorLog &errorlog) override { 
      PYBIND11_OVERRIDE(void,  DataProcessingConnectionsSpecificClientApplications, OnReceiveDicosFile, tdr, errorlog); 
    }
};


class PyPublicDataProcessingConnectionsSpecificClientApplications : public DataProcessingConnectionsSpecificClientApplications {
public:
   using DataProcessingConnectionsSpecificClientApplications::OnReceiveDicosFileError;
   using DataProcessingConnectionsSpecificClientApplications::OnReceiveDicosFile;
};


void export_DataProcessingConnectionsSpecificClientApplications(py::module &m)
{
   py::class_<DataProcessingConnectionsSpecificClientApplications, Network::IReceiveCallback>(m, "SDICOS::DataProcessingConnectsSpecificClientApps");
   py::class_<PyDataProcessingConnectionsSpecificClientApplications, DataProcessingConnectionsSpecificClientApplications, Network::IReceiveCallback>(m, "DataProcessingConnectsSpecificClientApps")
      .def(py::init<>())
      .def("OnReceiveDicosFileError", py::overload_cast<const SDICOS::ErrorLog&, const SDICOS::Utils::SessionData&>
                                      (&PyPublicDataProcessingConnectionsSpecificClientApplications::OnReceiveDicosFileError),
                                      py::arg("errorlog"), 
                                      py::arg("sessiondata"))

      .def("OnReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<SDICOS::AttributeManager> &, const SDICOS::ErrorLog &>
                                      (&PyPublicDataProcessingConnectionsSpecificClientApplications::OnReceiveDicosFile),
                                      py::arg("manager"), 
                                      py::arg("errorlog"))

      .def("OnReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<SDICOS::CT> &, const SDICOS::ErrorLog &>
                                      (&PyPublicDataProcessingConnectionsSpecificClientApplications::OnReceiveDicosFile),
                                      py::arg("ct"), 
                                      py::arg("errorlog"))

      .def("OnReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<SDICOS::DX> &, const SDICOS::ErrorLog &>
                                      (&PyPublicDataProcessingConnectionsSpecificClientApplications::OnReceiveDicosFile),
                                      py::arg("dx"), 
                                      py::arg("errorlog"))    

      .def("OnReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<SDICOS::AIT2D> &, const SDICOS::ErrorLog &>
                                      (&PyPublicDataProcessingConnectionsSpecificClientApplications::OnReceiveDicosFile),
                                      py::arg("ait"), 
                                      py::arg("errorlog"))

      .def("OnReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<SDICOS::AIT3D> &, const SDICOS::ErrorLog &>
                                      (&PyPublicDataProcessingConnectionsSpecificClientApplications::OnReceiveDicosFile),
                                      py::arg("ait"), 
                                      py::arg("errorlog"))     

      .def("OnReceiveDicosFile", py::overload_cast<SDICOS::Utils::DicosData<SDICOS::TDR> &, const SDICOS::ErrorLog &>
                                      (&PyPublicDataProcessingConnectionsSpecificClientApplications::OnReceiveDicosFile),
                                      py::arg("tdr"), 
                                      py::arg("errorlog"));                                                                                                                                                                              
}