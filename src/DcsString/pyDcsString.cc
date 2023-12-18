#include "../headers.hh"

#include "SDICOS/String.h"

using namespace SDICOS;


void export_DCSSTRING(py::module &m)
{
    py::class_<DcsString>(m, "DcsString")
        .def(py::init<>())
        .def(py::init<const char*>(), py::arg("pstr"))
        .def(py::init<const wchar_t*>(), py::arg("pstr"))
        .def(py::init<const DcsString&>(), py::arg("str"))
        .def("Get", py::overload_cast<>(&DcsString::Get, py::const_))
        .def("Get", py::overload_cast<char&, const S_UINT32>(&DcsString::Get, py::const_), 
                     py::arg("str"), 
                     py::arg("nIndex"))
        .def("Get", py::overload_cast<wchar_t&, const S_UINT32>(&DcsString::Get, py::const_), 
                     py::arg("str"), 
                     py::arg("nIndex"));

     py::class_<DcsLongString, DcsString>(m, "DcsLongString")
        .def(py::init<>())
        .def(py::init<const char*>(), py::arg("pstr"))
        .def(py::init<const wchar_t*>(), py::arg("pstr"))
        .def(py::init<const DcsLongString&>(), py::arg("dcslongstring"))
        .def(py::init<const DcsString&>(), py::arg("dcsstring"))
        .def("__assign__", (DcsLongString& (DcsLongString::*)(const DcsLongString&)) &DcsLongString::operator=);


    py::class_<DcsLongText, DcsString>(m, "DcsLongText")
        .def(py::init<>())
        .def(py::init<const char*>(), py::arg("pstr"))
        .def(py::init<const wchar_t*>(), py::arg("pstr"))
        .def(py::init<const DcsLongText&>(), py::arg("dcslongtext"))
        .def(py::init<const DcsString&>(), py::arg("dcsstring"))
        .def("__assign__", (DcsLongText& (DcsLongText::*)(const DcsLongText&)) &DcsLongText::operator=)
        .def("__eq__", (bool (DcsLongText::*)(const char*) const) &DcsLongText::operator==)
        .def("__eq__", (bool (DcsLongText::*)(const wchar_t*) const) &DcsLongText::operator==)
        .def("__eq__", (bool (DcsLongText::*)(const DcsString &) const) &DcsLongText::operator==)
        .def("__eq__", (bool (DcsLongText::*)(const DcsLongText &) const) &DcsLongText::operator==)
        .def("__ne__", (bool (DcsLongText::*)(const char*) const) &DcsLongText::operator!=)
        .def("__ne__", (bool (DcsLongText::*)(const wchar_t*) const) &DcsLongText::operator!=)
        .def("__ne__", (bool (DcsLongText::*)(const DcsString &) const) &DcsLongText::operator!=)
        .def("__ne__", (bool (DcsLongText::*)(const DcsLongText &) const) &DcsLongText::operator!=);

    py::class_<DcsDate, DcsString>(m, "DcsDate")
        .def(py::init<>())
        .def(py::init<const S_UINT32, const S_UINT32, const S_UINT32>(), py::arg("nYear"), py::arg("nMonth"), py::arg("nDay"))
        .def(py::init<const char*>(), py::arg("pstr"))
        .def(py::init<const wchar_t*>(), py::arg("pstr"))
        .def(py::init<const DcsDate&>(), py::arg("dcsdate"))
        .def(py::init<const DcsString&>(), py::arg("dcsstring"))
        .def("__assign__", (DcsDate& (DcsDate::*)(const char*)) &DcsDate::operator=)
        .def("__assign__", (DcsDate& (DcsDate::*)(const wchar_t*)) &DcsDate::operator=)
        .def("__assign__", (DcsDate& (DcsDate::*)(const DcsDate &)) &DcsDate::operator=)
        .def("__eq__", (bool (DcsDate::*)(const char*) const) &DcsDate::operator==)
        .def("__eq__", (bool (DcsDate::*)(const wchar_t*) const) &DcsDate::operator==)
        .def("__eq__", (bool (DcsDate::*)(const DcsString &) const) &DcsDate::operator==)
        .def("__eq__", (bool (DcsDate::*)(const DcsDate &) const) &DcsDate::operator==)
        .def("__ne__", (bool (DcsDate::*)(const char*) const) &DcsDate::operator!=)
        .def("__ne__", (bool (DcsDate::*)(const wchar_t*) const) &DcsDate::operator!=)
        .def("__ne__", (bool (DcsDate::*)(const DcsString &) const) &DcsDate::operator!=)
        .def("__ne__", (bool (DcsDate::*)(const DcsDate &) const) &DcsDate::operator!=)
        
        .def("Set", &DcsDate::Set, py::arg("nYear"), py::arg("nMonth"), py::arg("nDay"))
        .def("Get", [](DcsDate &self, S_UINT32& nYear, S_UINT32& nMonth, S_UINT32& nDay) {
            return std::make_tuple(self.Get(nYear, nMonth, nDay), nYear, nMonth, nDay);
        }, py::arg("nYear"), py::arg("nMonth"), py::arg("nDay"))
        
        .def("SetStart", &DcsDate::Set, py::arg("nYear"), py::arg("nMonth"), py::arg("nDay"))
        .def("GetStart", [](DcsDate &self, S_UINT32& nYear, S_UINT32& nMonth, S_UINT32& nDay) {
            return std::make_tuple(self.Get(nYear, nMonth, nDay), nYear, nMonth, nDay);
        }, py::arg("nYear"), py::arg("nMonth"), py::arg("nDay"))

        .def("SetEnd", &DcsDate::Set, py::arg("nYear"), py::arg("nMonth"), py::arg("nDay"))
        .def("GetEnd", [](DcsDate &self, S_UINT32& nYear, S_UINT32& nMonth, S_UINT32& nDay) {
            return std::make_tuple(self.Get(nYear, nMonth, nDay), nYear, nMonth, nDay);
        }, py::arg("nYear"), py::arg("nMonth"), py::arg("nDay"))
        .def("Today", &DcsDate::Today);

    py::class_<DcsUniqueIdentifier, DcsString>(m, "DcsUniqueIdentifier")
        .def(py::init<>())
        .def(py::init<const char*>(), py::arg("pstr"))
        .def(py::init<const wchar_t*>(), py::arg("pstr"))
        .def(py::init<const DcsUniqueIdentifier&>(), py::arg("dcsuniqueidentifier"))
        .def(py::init<const DcsString&>(), py::arg("dcsstring"))
        .def("__assign__", (DcsUniqueIdentifier& (DcsUniqueIdentifier::*)(const DcsUniqueIdentifier&)) &DcsUniqueIdentifier::operator=)
        .def("__eq__", (bool (DcsUniqueIdentifier::*)(const char*) const) &DcsUniqueIdentifier::operator==)
        .def("__eq__", (bool (DcsUniqueIdentifier::*)(const wchar_t*) const) &DcsUniqueIdentifier::operator==)
        .def("__eq__", (bool (DcsUniqueIdentifier::*)(const DcsString &) const) &DcsUniqueIdentifier::operator==)
        .def("__eq__", (bool (DcsUniqueIdentifier::*)(const DcsUniqueIdentifier &) const) &DcsUniqueIdentifier::operator==)
        .def("__ne__", (bool (DcsUniqueIdentifier::*)(const char*) const) &DcsUniqueIdentifier::operator!=)
        .def("__ne__", (bool (DcsUniqueIdentifier::*)(const wchar_t*) const) &DcsUniqueIdentifier::operator!=)
        .def("__ne__", (bool (DcsUniqueIdentifier::*)(const DcsString &) const) &DcsUniqueIdentifier::operator!=)
        .def("__ne__", (bool (DcsUniqueIdentifier::*)(const DcsUniqueIdentifier &) const) &DcsUniqueIdentifier::operator!=)
        .def("SetGUID", &DcsUniqueIdentifier::SetGUID)
        .def("CreateGUID", &DcsUniqueIdentifier::CreateGUID);
        

        py::class_<DcsLongText, DcsString>(m, "DcsLongText")
        .def(py::init<>())
        .def(py::init<const char*>(), py::arg("pstr"))
        .def(py::init<const wchar_t*>(), py::arg("pstr"))
        .def(py::init<const DcsLongText&>(), py::arg("dcslongtext"))
        .def(py::init<const DcsString&>(), py::arg("dcsstring"))
        .def("__assign__", (DcsLongText& (DcsLongText::*)(const DcsLongText&)) &DcsLongText::operator=)
        .def("__eq__", (bool (DcsLongText::*)(const char*) const) &DcsLongText::operator==)
        .def("__eq__", (bool (DcsLongText::*)(const wchar_t*) const) &DcsLongText::operator==)
        .def("__eq__", (bool (DcsLongText::*)(const DcsString &) const) &DcsLongText::operator==)
        .def("__eq__", (bool (DcsLongText::*)(const DcsLongText &) const) &DcsLongText::operator==)
        .def("__ne__", (bool (DcsLongText::*)(const char*) const) &DcsLongText::operator!=)
        .def("__ne__", (bool (DcsLongText::*)(const wchar_t*) const) &DcsLongText::operator!=)
        .def("__ne__", (bool (DcsLongText::*)(const DcsString &) const) &DcsLongText::operator!=)
        .def("__ne__", (bool (DcsLongText::*)(const DcsLongText &) const) &DcsLongText::operator!=);

}


