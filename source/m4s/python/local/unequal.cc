#include "m4s/python/local/unequal.h"


// PCRaster
#include "calc_spatial.h"
#include "calc_nonspatial.h"


// Field wrapper
#include "m4s/python/local/utils.h"
#include "m4s/python/local/not.h"
#include "m4s/python/local/equal.h"



namespace pcraster_multicore {
namespace python {
namespace detail {


} // namespace detail


calc::Field* unequal(
         calc::Field* field_a,
         calc::Field* field_b){

  assert_equal_location_attributes(*field_a);
  assert_equal_location_attributes(*field_b);
  assert_equal_valuescale(*field_a, *field_b, "one operand");

  return _not(equal(field_a, field_b));
}

} // namespace python
} // namespace pcraster_multicore

