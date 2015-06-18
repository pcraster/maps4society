#pragma once

#include "fern/core/argument_traits.h"

#include "multicore_field.h"

namespace fern {


template<class T>
struct ArgumentTraits<multicore_field::multicore_field<T>>{

  using value_type = T;

  using reference = T&;

  using const_reference = T const&;

  using argument_category = raster_2d_tag;

};



template<class T>
inline multicore_field::multicore_field<T> clone(
    multicore_field::multicore_field<T> const& aField)
{
  return aField.getField()->createClone();
}



template<class T>
inline size_t size(
    multicore_field::multicore_field<T> const& aField,
    size_t dimension){
  return aField.size(dimension);
}


template<class T>
inline T const& get(
    multicore_field::multicore_field<T> const& aField,
    size_t index){
  return aField.get(index);
}


template<class T>
inline T& get(
    multicore_field::multicore_field<T>& aField,
    size_t index){
  return aField.get(index);
}


template<typename T>
inline size_t index(
    multicore_field::multicore_field<T> const& aField,
    size_t index1,
    size_t index2){
  return aField.index(index1, index2);
}

template<class T>
inline double cell_size(
    const multicore_field::multicore_field<T>& aField,
    size_t index){
  (void)index;
  return aField.cell_size();
}

} // namespace fern
