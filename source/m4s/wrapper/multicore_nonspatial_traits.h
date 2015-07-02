#error




#pragma once

#include "fern/core/argument_traits.h"

#include "multicore_nonspatial.h"

namespace fern {


template<class T>
struct ArgumentTraits<multicore_nonspatial::multicore_nonspatial<T>>{

  using value_type = T;

  using reference = T&;

  using const_reference = T const&;

  using argument_category = constant_tag;

};



// template<class T>
// inline multicore_nonspatial::multicore_nonspatial<T> clone(
//     multicore_nonspatial::multicore_nonspatial<T> const& aField)
// {
//   return aField.getField()->createClone();
// }



template<class T>
inline size_t size(
    //T const& /* constant */)
    multicore_nonspatial::multicore_nonspatial<T> const& /*aField*/)
{
    return 1u;
}




template<class T>
inline T const& get(
    multicore_nonspatial::multicore_nonspatial<T> const& aField/*,
    size_t index*/){
//   (void)index;
  //std::cout << "traits inline T const& get "<< std::endl;
  return aField.get();
}


template<class T>
inline T& get(
    multicore_nonspatial::multicore_nonspatial<T>& aField/*,
    size_t index*/){
//   (void)index;
  //std::cout << "traits inline T& get "<< std::endl;
  return aField.get();
}


// template<typename T>
// inline size_t index(
//     multicore_nonspatial::multicore_nonspatial<T> const& aField,
//     size_t index1,
//     size_t index2){
//   return aField.index(index1, index2);
// }

// template<class T>
// inline double cell_size(
//     const multicore_nonspatial::multicore_nonspatial<T>& aField,
//     size_t index){
//   (void)index;
//   return aField.cell_size();
//}

} // namespace fern
