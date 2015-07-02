#pragma once

#include "calc_spatial.h"
#include "fern/algorithm/policy/execution_policy.h"


namespace calc {
  class Field;
}


namespace pcraster_multicore {
namespace python {


calc::Field* _and(
         calc::Field* field_a,
         calc::Field* field_b);


} // namespace python
} // namespace pcraster_multicore

