#pragma once

#include <cstddef>

#include "pcrtree2/calc_spatial.h"
#include "pcrtree2/com_mvop.h"


namespace multicore_field {


template<class T>
class Nonspatial {

public:

  Nonspatial  (calc::Field* field);

  ~Nonspatial (){};

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
Nonspatial<T>::Nonspatial(calc::Field* field){
  pcr_field = field;
  the_cells = static_cast<T*>(pcr_field->dest());
  /// todo clean this up...
//   rows = pcraster::python::globals.cloneSpace().nrRows();
//   cols = pcraster::python::globals.cloneSpace().nrCols();
//   _cell_size = pcraster::python::globals.cloneSpace().cellSize();
}


template<class T>
inline calc::Field* Nonspatial<T>::getField() const {
  return pcr_field;
}


template<class T>
inline T const & Nonspatial<T>::get() const {
  return the_cells[0];
}


template<class T>
inline T& Nonspatial<T>::get(){
  return the_cells[0];
}


// template<class T>
// inline size_t Nonspatial<T>::size(size_t dimension) const {
//   if(dimension == 0){
//     return 1;
//   }
//   else if (dimension == 1){
//     return 1;
//   }
//   return 0;
// }


template<class T>
inline void Nonspatial<T>::set_mv() const {
  pcr::setMV(the_cells[0]);
}


// template<class T>
// inline size_t Nonspatial<T>::index(size_t idx1, size_t idx2) const {
//   (void)idx1;
//   (void)idx2;
//   return 0;
// }


template<class T>
inline T* Nonspatial<T>::get_cells() const {
  return the_cells;
}


// template<class T>
// inline double Nonspatial<T>::cell_size() const {
//   return _cell_size;
// }

} // namespace multicore_field
