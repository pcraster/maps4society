#pragma once

#include "csftypes.h"

#include "m4s/wrapper/multicore_field.h"

template<class T>
class MulticoreFieldOutputNoDataPolicy
{

private:


public:

                   MulticoreFieldOutputNoDataPolicy(
                                        multicore_field::multicore_field<T> const& aField) noexcept;

    void           mark_as_no_data     (size_t index) const noexcept;

    void           mark_as_no_data     (size_t row,
                                        size_t col) const noexcept;

private:

    multicore_field::multicore_field<T> const & _field;
};

template<class T>
inline MulticoreFieldOutputNoDataPolicy<T>::MulticoreFieldOutputNoDataPolicy(
    multicore_field::multicore_field<T> const& aField) noexcept

    : _field(aField)

{
}


template<class T>
inline void MulticoreFieldOutputNoDataPolicy<T>::mark_as_no_data(
    size_t index) const noexcept
{
   _field.set_cell(index);
}
