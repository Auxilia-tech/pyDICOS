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
        .def("__copy__", [](const DcsString &self) { return DcsString(self); })
        .def("__deepcopy__", [](const DcsString &self, py::dict) { return DcsString(self); });

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

    py::class_<DcsTime, DcsString>(m, "DcsTime")
        .def(py::init<>())
        .def(py::init<const S_UINT32, const S_UINT32, const S_UINT32, const S_UINT32>(), 
                      py::arg("nHour"), py::arg("nMinute"), py::arg("nSecond"), py::arg("nSecondFraction"))
        .def(py::init<const char*>(), py::arg("pstr"))
        .def(py::init<const wchar_t*>(), py::arg("pstr"))
        .def(py::init<const DcsTime&>(), py::arg("dcstime"))
        .def(py::init<const DcsString&>(), py::arg("dcsstring"))
        .def("__assign__", (DcsTime& (DcsTime::*)(const char*)) &DcsTime::operator=)
        .def("__assign__", (DcsTime& (DcsTime::*)(const wchar_t*)) &DcsTime::operator=)
        .def("__assign__", (DcsTime& (DcsTime::*)(const DcsTime &)) &DcsTime::operator=)
        .def("__eq__", (bool (DcsTime::*)(const char*) const) &DcsTime::operator==)
        .def("__eq__", (bool (DcsTime::*)(const wchar_t*) const) &DcsTime::operator==)
        .def("__eq__", (bool (DcsTime::*)(const DcsString &) const) &DcsTime::operator==)
        .def("__eq__", (bool (DcsTime::*)(const DcsTime &) const) &DcsTime::operator==)
        .def("__ne__", (bool (DcsTime::*)(const char*) const) &DcsTime::operator!=)
        .def("__ne__", (bool (DcsTime::*)(const wchar_t*) const) &DcsTime::operator!=)
        .def("__ne__", (bool (DcsTime::*)(const DcsString &) const) &DcsTime::operator!=)
        .def("__ne__", (bool (DcsTime::*)(const DcsTime &) const) &DcsTime::operator!=)
        
        .def("Set", &DcsTime::Set, py::arg("nHour"), py::arg("nMinute"), py::arg("nSecond"),  py::arg("nSecondFraction"))
        .def("Get", [](DcsTime &self, S_UINT32& nHour, S_UINT32& nMinute, S_UINT32& nSecond, S_UINT32& nSecondFraction) {
            return std::make_tuple(self.Get(nHour, nMinute, nSecond, nSecondFraction), nHour, nMinute, nSecond, nSecondFraction);
        }, py::arg("nHour"), py::arg("nMinute"), py::arg("nSecond"), py::arg("nSecondFraction"))
        
        .def("SetStart", &DcsTime::Set, py::arg("nHour"), py::arg("nMinute"), py::arg("nSecond"),  py::arg("nSecondFraction"))
        .def("GetStart", [](DcsTime &self, S_UINT32& nHour, S_UINT32& nMinute, S_UINT32& nSecond, S_UINT32& nSecondFraction) {
            return std::make_tuple(self.Get(nHour, nMinute, nSecond, nSecondFraction), nHour, nMinute, nSecond, nSecondFraction);
        }, py::arg("nHour"), py::arg("nMinute"), py::arg("nSecond"), py::arg("nSecondFraction"))

        .def("SetEnd", &DcsTime::Set, py::arg("nHour"), py::arg("nMinute"), py::arg("nSecond"), py::arg("nSecondFraction"))
        .def("GetEnd", [](DcsTime &self, S_UINT32& nHour, S_UINT32& nMinute, S_UINT32& nSecond, S_UINT32& nSecondFraction) {
            return std::make_tuple(self.Get(nHour, nMinute, nSecond, nSecondFraction), nHour, nMinute, nSecond, nSecondFraction);
        }, py::arg("nHour"), py::arg("nMinute"), py::arg("nSecond"), py::arg("nSecondFraction"))
        .def("Now", &DcsTime::Now);

}


