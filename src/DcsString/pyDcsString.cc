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


    py::class_<DcsDateTime>(m, "DcsDateTime")
        .def(py::init<>())
        .def(py::init<const DcsDate&, const DcsTime&>(), py::arg("dcsDate"), py::arg("dcsTime"))
        .def(py::init<const DcsDateTime&>(), py::arg("dcsdatetime"))
        .def("__assign__", (DcsDateTime& (DcsDateTime::*)(const DcsDateTime&)) &DcsDateTime::operator=)
        .def("__eq__", (bool (DcsDateTime::*)(const DcsDateTime&) const) &DcsDateTime::operator==)
        .def("__ne__", (bool (DcsDateTime::*)(const DcsDateTime&) const) &DcsDateTime::operator!=)
        .def("SetNow", &DcsDateTime::SetNow)
             
        .def("Set", py::overload_cast<const DcsDate&, const DcsTime&, const S_INT16>(&DcsDateTime::Set), 
                    py::arg("dcsdate"), 
                    py::arg("dcsTime"), 
                    py::arg("nOffset"))
        .def("Set", py::overload_cast<const DcsDate&, const DcsTime&>(&DcsDateTime::Set), 
                    py::arg("dcsdate"), 
                    py::arg("dcsTime"))  
        .def("Set", py::overload_cast<const DcsDate&, const S_INT16>(&DcsDateTime::Set), 
                    py::arg("dcsdate"), 
                    py::arg("nOffset"))  
        .def("Set", py::overload_cast<const DcsDate&>(&DcsDateTime::Set), 
                    py::arg("dcsdate")) 

        .def("SetRangeStart", py::overload_cast<const DcsDate&, const DcsTime&, const S_INT16>(&DcsDateTime::Set), 
                    py::arg("dcsDateStart"), 
                    py::arg("dcsTimeStart"), 
                    py::arg("nOffsetStart"))      
        .def("SetRangeStart", py::overload_cast<const DcsDate&, const DcsTime&>(&DcsDateTime::Set), 
                    py::arg("dcsDateStart"), 
                    py::arg("dcsTimeStart"))   

        .def("SetRangeEnd", py::overload_cast<const DcsDate&, const DcsTime&, const S_INT16>(&DcsDateTime::Set), 
                    py::arg("dcsDateEnd"), 
                    py::arg("dcsTimeEnd"), 
                    py::arg("nOffsetEnd"))      
        .def("SetRangeEnd", py::overload_cast<const DcsDate&, const DcsTime&>(&DcsDateTime::Set), 
                    py::arg("dcsDateEnd"), 
                    py::arg("dcsTimeEnd"))   

        .def("Get", [](DcsDateTime &self, DcsDate& strDate, DcsTime& strTime, S_INT16& strOffsetFromUTC) {
            return std::make_tuple(self.Get(strDate, strTime, strOffsetFromUTC), strDate, strTime, strOffsetFromUTC);
        }, py::arg("strDate"), py::arg("strTime"), py::arg("strOffsetFromUTC"));

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


    py::class_<DcsShortText, DcsString>(m, "DcsShortText")
        .def(py::init<>())
        .def(py::init<const char*>(), py::arg("pstr"))
        .def(py::init<const wchar_t*>(), py::arg("pstr"))
        .def(py::init<const DcsShortText&>(), py::arg("dcsshorttext"))
        .def(py::init<const DcsString&>(), py::arg("dcsstring"))
        .def("__assign__", (DcsShortText& (DcsShortText::*)(const DcsShortText&)) &DcsShortText::operator=)
        .def("__eq__", (bool (DcsShortText::*)(const char*) const) &DcsShortText::operator==)
        .def("__eq__", (bool (DcsShortText::*)(const wchar_t*) const) &DcsShortText::operator==)
        .def("__eq__", (bool (DcsShortText::*)(const DcsShortText &) const) &DcsShortText::operator==)
        .def("__ne__", (bool (DcsShortText::*)(const char*) const) &DcsShortText::operator!=)
        .def("__ne__", (bool (DcsShortText::*)(const wchar_t*) const) &DcsShortText::operator!=)
        .def("__ne__", (bool (DcsShortText::*)(const DcsShortText &) const) &DcsShortText::operator!=);


    py::class_<DcsShortString, DcsString>(m, "DcsShortString")
        .def(py::init<>())
        .def(py::init<const char*>(), py::arg("pstr"))
        .def(py::init<const wchar_t*>(), py::arg("pstr"))
        .def(py::init<const DcsShortString&>(), py::arg("dcsshortstring"))
        .def(py::init<const DcsString&>(), py::arg("dcsstring"))
        .def("__assign__", (DcsShortString& (DcsShortString::*)(const DcsShortString&)) &DcsShortString::operator=)
        .def("__eq__", (bool (DcsShortString::*)(const char*) const) &DcsShortString::operator==)
        .def("__eq__", (bool (DcsShortString::*)(const wchar_t*) const) &DcsShortString::operator==)
        .def("__eq__", (bool (DcsShortString::*)(const DcsString &) const) &DcsShortString::operator==)
        .def("__eq__", (bool (DcsShortString::*)(const DcsShortString &) const) &DcsShortString::operator==)
        .def("__ne__", (bool (DcsShortString::*)(const char*) const) &DcsShortString::operator!=)
        .def("__ne__", (bool (DcsShortString::*)(const wchar_t*) const) &DcsShortString::operator!=)
        .def("__ne__", (bool (DcsShortString::*)(const DcsString &) const) &DcsShortString::operator!=)
        .def("__ne__", (bool (DcsShortString::*)(const DcsShortString &) const) &DcsShortString::operator!=);

    py::class_<DcsApplicationEntity, DcsString>(m , "DcsApplicationEntity")
        .def(py::init<>())
        .def(py::init<const char*>(), py::arg("pstr"))
        .def(py::init<const wchar_t*>(), py::arg("pstr"))
        .def(py::init<const DcsString&>(), py::arg("dcsstring"))
        .def(py::init<const DcsApplicationEntity&>(), py::arg("dcsapplicationentity"));
}


