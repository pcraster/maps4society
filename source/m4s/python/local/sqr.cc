#include "m4s/python/local/sqr.h"


// PCRaster
#include "pcrtree2/calc_spatial.h"
#include "pcrtree2/calc_nonspatial.h"


// Field wrapper
#include "m4s/wrapper/datatype_customization_points/multicore_nonspatial.h"
#include "m4s/wrapper/datatype_traits/multicore_nonspatial.h"
#include "m4s/wrapper/argument_traits/multicore_nonspatial.h"

#include "m4s/python/local/utils.h"
#include "m4s/python/local/pow.h"


namespace pcraster_multicore {
namespace python {
namespace detail {


} // namespace detail


calc::Field* sqr(
         calc::Field* field){

  assert_equal_location_attributes(*field);
  assert_scalar_valuescale(*field, "argument");

  calc::Field* two = new calc::NonSpatial(VS_S, 2.0);

  return power(field, two);
}

} // namespace python
} // namespace pcraster_multicore

