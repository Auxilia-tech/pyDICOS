#include "../headers.hh"

#include "SDICOS/IHost.h"

using namespace SDICOS;

void export_IDCSSERVER(py::module &m)
{
     py::enum_<Network::IDcsServer::RESULT>(m, "RESULT_IDCSSERVER")
        .value("enumResultUnknown", Network::IDcsServer::RESULT::enumResultUnknown)
        .value("enumResultNone", Network::IDcsServer::RESULT::enumResultNone)
        .value("enumResultBusy", Network::IDcsServer::RESULT::enumResultBusy)
        .value("enumResultSuccess", Network::IDcsServer::RESULT::enumResultSuccess)
        .value("enumResultFailed", Network::IDcsServer::RESULT::enumResultFailed)
        .value("enumResultCancelled", Network::IDcsServer::RESULT::enumResultCancelled)
        .value("enumResultAborted", Network::IDcsServer::RESULT::enumResultAborted)
        .value("enumResultRejectedDestinationApplicationName", Network::IDcsServer::RESULT::enumResultRejectedDestinationApplicationName)
        .value("enumResultRejectedSourceApplicationName", Network::IDcsServer::RESULT::enumResultRejectedSourceApplicationName)
        .value("enumResultRejectedUnsupportedUserType", Network::IDcsServer::RESULT::enumResultRejectedUnsupportedUserType)
        .value("enumResultRejectedUserTypeMismatch", Network::IDcsServer::RESULT::enumResultRejectedUserTypeMismatch)
        .value("enumResultRejectedInvalidUserData", Network::IDcsServer::RESULT::enumResultRejectedInvalidUserData)
        .value("enumResultRejectedUnsupportedApplicationContextName", Network::IDcsServer::RESULT::enumResultRejectedUnsupportedApplicationContextName)
        .value("enumResultAbortedExpectedData,", Network::IDcsServer::RESULT::enumResultAbortedExpectedData)
        .value("enumResultAbortedUnknownPDU", Network::IDcsServer::RESULT::enumResultAbortedUnknownPDU)
        .value("enumResultAbortedUnknownPDV", Network::IDcsServer::RESULT::enumResultAbortedUnknownPDV)
        .value("enumResultAbortCastFailed", Network::IDcsServer::RESULT::enumResultAbortCastFailed)
        .value("enumResultFailedToReceiveCompleteData", Network::IDcsServer::RESULT::enumResultFailedToReceiveCompleteData)
        .export_values();

     py::enum_<Network::IDcsServer::RETRIEVE_METHOD>(m, "RETRIEVE_METHOD")
        .value("enumMethodTagAPI", Network::IDcsServer::RETRIEVE_METHOD::enumMethodTagAPI)
        .value("enumMethodModuleAPI", Network::IDcsServer::RETRIEVE_METHOD::enumMethodModuleAPI)
        .value("enumMethodUserAPI", Network::IDcsServer::RETRIEVE_METHOD::enumMethodUserAPI)
        .export_values();

     py::class_<Network::IDcsServer>(m, "IDcsServer")
        .def_property_readonly_static("RESULT_IDCSSERVER", [m](py::object) {
            return m.attr("RESULT_IDCSSERVER");
        })  
        .def_property_readonly_static("RETRIEVE_METHOD", [m](py::object) {
            return m.attr("RETRIEVE_METHOD");
        });
}