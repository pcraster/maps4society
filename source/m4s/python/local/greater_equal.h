#pragma once

#include "calc_spatial.h"


namespace calc {
  class Field;
}


namespace pcraster_multicore {
namespace python {


calc::Field* greater_equal(
         calc::Field* field_a,
         calc::Field* field_b);


} // namespace python
} // namespace pcraster_multicore
