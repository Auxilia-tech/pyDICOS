#ifndef T_CUSTOMARRAY1D_H
#define T_CUSTOMARRAY1D_H

#include "SDICOS/DICOS.h" //Header for DICOS
#include <iostream>
#include <map>
#include "../headers.hh"
#include <pybind11/numpy.h>
#include "SDICOS/Array1D.h"

using namespace SDICOS;

template<typename T>
class CustomArray1D : public Array1D<T>
{
public:
    CustomArray1D() : Array1D<T>() {}

    CustomArray1D(S_UINT32 size) : Array1D<T>(size) {}

    CustomArray1D(const CustomArray1D& other) : Array1D<T>(other) {}

    CustomArray1D(S_UINT32 size, const T& initialValue) : Array1D<T>(size)
    {
        for (S_UINT32 i = 0; i < size; ++i)
            (*this)[i] = initialValue;
    }

    void SetBuffer(S_UINT32 i, const T& value)
    {
        if (i >= 0 && i < this->GetSize())
            this->GetBuffer()[i] = value;
    }

};
#endif