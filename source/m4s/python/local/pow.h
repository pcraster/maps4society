#pragma once

#include "fern/algorithm/policy/execution_policy.h"
#include "calc_spatial.h"

namespace calc {
  class Field;
}

namespace multicore_field{
  template<class T>
  class multicore_field;
}

namespace pcraster_multicore {
namespace python {


calc::Field* power(
         calc::Field* field_a,
         calc::Field* field_b);

calc::Field* power_field_field(
         fern::algorithm::ExecutionPolicy epol,
         const multicore_field::multicore_field<REAL4>* arg1,
         const multicore_field::multicore_field<REAL4>* arg2,
         multicore_field::multicore_field<REAL4>* res);

calc::Field* power_field_number(
         fern::algorithm::ExecutionPolicy epol,
         const multicore_field::multicore_field<REAL4>* arg1,
         REAL4 arg2,
         multicore_field::multicore_field<REAL4>* res);

calc::Field* power_number_field(
         fern::algorithm::ExecutionPolicy epol,
         REAL4 arg1,
         const multicore_field::multicore_field<REAL4>* arg2,
         multicore_field::multicore_field<REAL4>* res);


} // namespace python
} // namespace pcraster_multicore

