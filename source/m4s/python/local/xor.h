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


calc::Field* _xor(
         calc::Field* field_a,
         calc::Field* field_b);


} // namespace python
} // namespace pcraster_multicore

