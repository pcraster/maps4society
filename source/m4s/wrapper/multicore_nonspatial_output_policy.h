#pragma once

#include "csftypes.h"

#include "m4s/wrapper/multicore_nonspatial.h"
//#include "fern/core/data_type_traits/scalar.h"  /// todo

template<class T>
class MulticoreNonspatialOutputNoDataPolicy
{

private:


public:

                   MulticoreNonspatialOutputNoDataPolicy(
                                        multicore_field::Nonspatial<T> const& aField) noexcept;


    void           mark_as_no_data     () const noexcept;
    //void           mark_as_no_data     (size_t index) const noexcept;

//     void           mark_as_no_data     (size_t row,
//                                         size_t col) const noexcept;

private:

    multicore_field::Nonspatial<T> const & _field;
};

template<class T>
inline MulticoreNonspatialOutputNoDataPolicy<T>::MulticoreNonspatialOutputNoDataPolicy(
    multicore_field::Nonspatial<T> const& aField) noexcept

    : _field(aField)

{
}


template<class T>
inline void MulticoreNonspatialOutputNoDataPolicy<T>::mark_as_no_data() const noexcept {
   _field.set_mv();
}
