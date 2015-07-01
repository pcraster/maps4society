#pragma once

#include <cstddef>

#include "calc_spatial.h"
#include "com_mvop.h"
//#include "Globals.h"


// namespace pcraster {
// namespace python {
//   extern Globals globals;
// }
// }


namespace multicore_nonspatial {


template<class T>
class multicore_nonspatial{

public:

  multicore_nonspatial  (calc::Field* field);

  ~multicore_nonspatial (){};

  T&               get();

  T const&         get() const;

  //size_t           index(size_t idx1, size_t idx2) const;

  //size_t           size(size_t dimension) const;

  T*               get_cells() const;

  void             set_mv() const;

  calc::Field*     getField() const;

  //double           cell_size() const;

protected:

private:

  calc::Field*     pcr_field;

  T*               the_cells;

  //size_t           rows;

  //size_t           cols;

  //double           _cell_size;

};


template<class T>
multicore_nonspatial<T>::multicore_nonspatial(calc::Field* field){
  pcr_field = field;
  the_cells = static_cast<T*>(pcr_field->dest());
//   rows = pcraster::python::globals.cloneSpace().nrRows();
//   cols = pcraster::python::globals.cloneSpace().nrCols();
//   _cell_size = pcraster::python::globals.cloneSpace().cellSize();
}


template<class T>
inline calc::Field* multicore_nonspatial<T>::getField() const {
  return pcr_field;
}


template<class T>
inline T const & multicore_nonspatial<T>::get() const {
  //std::cout << "nsp inline T const & multicore_nonspatial<T>::get() " << (int)the_cells[0]<< std::endl;
  return the_cells[0];
}


template<class T>
inline T& multicore_nonspatial<T>::get(){
  //std::cout << "nsp inline T& multicore_nonspatial<T>::get() " << (int)the_cells[0]<< std::endl;
  return the_cells[0];
}


// template<class T>
// inline size_t multicore_nonspatial<T>::size(size_t dimension) const {
//   if(dimension == 0){
//     return 1;
//   }
//   else if (dimension == 1){
//     return 1;
//   }
//   return 0;
// }


template<class T>
inline void multicore_nonspatial<T>::set_mv() const {
  pcr::setMV(the_cells[0]);
}


// template<class T>
// inline size_t multicore_nonspatial<T>::index(size_t idx1, size_t idx2) const {
//   (void)idx1;
//   (void)idx2;
//   return 0;
// }


template<class T>
inline T* multicore_nonspatial<T>::get_cells() const {
  return the_cells;
}


// template<class T>
// inline double multicore_nonspatial<T>::cell_size() const {
//   return _cell_size;
// }

} // namespace multicore_nonspatial
