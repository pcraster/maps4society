#pragma once

#include "csftypes.h"
#include "com_mvop.h"

#include "multicore_nonspatial.h"
//#include "fern/core/data_type_traits/scalar.h"  /// todo
template<class T>
class MulticoreNonspatialInputNoDataPolicy
{

private:


public:

                   MulticoreNonspatialInputNoDataPolicy(multicore_field::Nonspatial<T> const& aField) noexcept;

                   MulticoreNonspatialInputNoDataPolicy(MulticoreNonspatialInputNoDataPolicy<T>&& other)=default;


    bool           is_no_data          () const noexcept;
    bool           is_no_data          (size_t index) const noexcept;  /// todo remove this!!!

private:

    multicore_field::Nonspatial<T> const&    _field;

};


template<class T>
inline MulticoreNonspatialInputNoDataPolicy<T>::MulticoreNonspatialInputNoDataPolicy(
    multicore_field::Nonspatial<T> const& aField) noexcept

    : _field(aField)

{
}


template<class T>
inline bool MulticoreNonspatialInputNoDataPolicy<T>::is_no_data() const noexcept {
  return pcr::isMV(_field.get_cells()[0]);
}


template<class T>
inline bool MulticoreNonspatialInputNoDataPolicy<T>::is_no_data(size_t index) const noexcept {
  // this method should not be necessary
  // remove this with newer version of fern supporting the () in 0d_2d ops
  return pcr::isMV(_field.get_cells()[0]);
}

