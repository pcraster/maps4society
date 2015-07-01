#pragma once

#include "csftypes.h"

#include "m4s/wrapper/multicore_nonspatial.h"

template<class T>
class MulticoreNonspatialOutputNoDataPolicy
{

private:


public:

                   MulticoreNonspatialOutputNoDataPolicy(
                                        multicore_nonspatial::multicore_nonspatial<T> const& aField) noexcept;


    void           mark_as_no_data     () const noexcept;
    //void           mark_as_no_data     (size_t index) const noexcept;

//     void           mark_as_no_data     (size_t row,
//                                         size_t col) const noexcept;

private:

    multicore_nonspatial::multicore_nonspatial<T> const & _field;
};

template<class T>
inline MulticoreNonspatialOutputNoDataPolicy<T>::MulticoreNonspatialOutputNoDataPolicy(
    multicore_nonspatial::multicore_nonspatial<T> const& aField) noexcept

    : _field(aField)

{
}


template<class T>
inline void MulticoreNonspatialOutputNoDataPolicy<T>::mark_as_no_data() const noexcept {
 // std::cout << "inline void MulticoreNonspatialOutputNoDataPolicy<T>::mark_as_no_data( " << index << " " << _field.get_cells()[0]<< " " << pcr::isMV(_field.get_cells()[0])<< std::endl;
  
  //(void)index;
   _field.set_mv();
}
