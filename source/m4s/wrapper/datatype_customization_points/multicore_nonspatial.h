#pragma once

#include "m4s/wrapper/datatype_traits/multicore_nonspatial.h"
#include "m4s/wrapper/multicore_nonspatial.h"

namespace fern {



template<class T>
inline size_t size(
    multicore_nonspatial::multicore_nonspatial<T> const& /*aField*/){

  return 1;
}


template<class T>
inline T const& get(
    multicore_nonspatial::multicore_nonspatial<T> const& aField){

  return aField.get();
}


template<class T>
inline T& get(
    multicore_nonspatial::multicore_nonspatial<T>& aField){

  return aField.get();
}



} // namespace fern