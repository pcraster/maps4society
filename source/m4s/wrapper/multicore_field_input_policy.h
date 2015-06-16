#pragma once

#include "csftypes.h"
#include "com_mvop.h"

#include "multicore_field.h"

template<class T>
class MulticoreFieldInputNoDataPolicy
{

private:


public:

                   MulticoreFieldInputNoDataPolicy(multicore_field::multicore_field<T> const& aField) noexcept;

                   MulticoreFieldInputNoDataPolicy(MulticoreFieldInputNoDataPolicy<T>&& other)=default;

    bool           is_no_data          (size_t index) const noexcept;

    bool           is_no_data          (size_t row,
                                        size_t col) const noexcept;

private:

    multicore_field::multicore_field<T> const&    _field;

};

template<class T>
inline MulticoreFieldInputNoDataPolicy<T>::MulticoreFieldInputNoDataPolicy(
    multicore_field::multicore_field<T> const& aField) noexcept

    : _field(aField)

{
}

template<class T>
inline bool MulticoreFieldInputNoDataPolicy<T>::is_no_data(
    size_t index) const noexcept
{
    return pcr::isMV(_field.get_cell()[index]);
}
