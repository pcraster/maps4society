#pragma once

#include "calc_spatial.h"
#include "fern/algorithm/policy/execution_policy.h"

namespace calc {
  class Field;
}

namespace multicore_field{
  template<class T>
  class multicore_field;
}

namespace multicore_nonspatial{
  template<class T>
  class multicore_nonspatial;
}


namespace pcraster_multicore {
namespace python {


calc::Field* add(
         calc::Field* field_a,
         calc::Field* field_b);

calc::Field* add_field_field(
         fern::algorithm::ExecutionPolicy epol,
         const multicore_field::multicore_field<REAL4>* arg1,
         const multicore_field::multicore_field<REAL4>* arg2,
         multicore_field::multicore_field<REAL4>* res);

calc::Field* add_field_number(
         fern::algorithm::ExecutionPolicy epol,
         const multicore_field::multicore_field<REAL4>* arg1,
         REAL4 arg2,
         multicore_field::multicore_field<REAL4>* res);

calc::Field* add_number_field(
         fern::algorithm::ExecutionPolicy epol,
         REAL4 arg1,
         const multicore_field::multicore_field<REAL4>* arg2,
         multicore_field::multicore_field<REAL4>* res);

calc::Field* add_number_number(
         const multicore_nonspatial::multicore_nonspatial<REAL4>* arg1,
         const multicore_nonspatial::multicore_nonspatial<REAL4>* arg2,
         multicore_nonspatial::multicore_nonspatial<REAL4>* res);


} // namespace python
} // namespace pcraster_multicore

