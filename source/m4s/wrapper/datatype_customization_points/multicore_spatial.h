#pragma once

//#include "fern/core/data_type_traits/scalar.h"  /// todo
#include "m4s/wrapper/datatype_traits/multicore_spatial.h"
#include "m4s/wrapper/multicore_field.h"

namespace fern {



template<class T>
inline multicore_field::Spatial<T> clone(
    multicore_field::Spatial<T> const& aField)
{
  return aField.getField()->createClone();
}



template<class T>
inline size_t size(
    multicore_field::Spatial<T> const& aField,
    size_t dimension){
  return aField.size(dimension);
}


template<class T>
inline T const& get(
    multicore_field::Spatial<T> const& aField,
    size_t index){
  return aField.get(index);
}


template<class T>
inline T& get(
    multicore_field::Spatial<T>& aField,
    size_t index){
  return aField.get(index);
}


template<typename T>
inline size_t index(
    multicore_field::Spatial<T> const& aField,
    size_t index1,
    size_t index2){
  return aField.index(index1, index2);
}


template<class T>
inline double cell_size(
    const multicore_field::Spatial<T>& aField,
    size_t index){
  (void)index;
  return aField.cell_size();
}

} // namespace fern
