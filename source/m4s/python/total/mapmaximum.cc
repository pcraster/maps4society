#include "m4s/python/total/mapmaximum.h"

// PCRaster
#include "pcrtree2/calc_spatial.h"
#include "pcrtree2/calc_nonspatial.h"
#include "pcrtree2/calc_cr.h"


// Field wrapper
#include "m4s/wrapper/datatype_customization_points/multicore_spatial.h"
#include "m4s/wrapper/datatype_traits/multicore_spatial.h"
#include "m4s/wrapper/argument_traits/multicore_spatial.h"

#include "m4s/wrapper/datatype_customization_points/multicore_nonspatial.h"
#include "m4s/wrapper/datatype_traits/multicore_nonspatial.h"
#include "m4s/wrapper/argument_traits/multicore_nonspatial.h"

#include "m4s/python/execution_policy.h"
#include "m4s/python/local/utils.h"


// Fern
#include "fern/algorithm/policy/policies.h"
#include "fern/algorithm/statistic/unary_max.h"

namespace fa = fern::algorithm;


namespace pcraster_multicore {
namespace python {
namespace detail {



template<class T>
calc::Field* mapmaximum(
         calc::Field* field,
         VS result_vs){

  const multicore_field::Spatial<T> arg1(field);
  using InputNoDataPolicy = fa::InputNoDataPolicies<SpatialDetectNoData<T>>;
  InputNoDataPolicy input_no_data_policy{{arg1}};

  calc::Field* res_field = nullptr;

  res_field = new calc::NonSpatial(result_vs);
  multicore_field::Nonspatial<T> res(res_field);

  NonspatialSetNoData<T> output_no_data_policy(res);

  fa::ExecutionPolicy epol = execution_policy();

  fa::statistic::unary_max(input_no_data_policy, output_no_data_policy, epol, arg1, res);

  return res.getField();
}


} // namespace detail


calc::Field* mapmaximum(
         calc::Field* field){

  assert_equal_location_attributes(*field);

  if(field->isSpatial() == false){
    throw std::runtime_error("argument is non-spatial, only spatial allowed\n");
  }

  VS result_vs = field->vs();

  if(scalar_valuescale(*field) == true){
    return detail::mapmaximum<REAL4>(field, result_vs);
  }
  else if(ordinal_valuescale(*field) == true){
    return detail::mapmaximum<INT4>(field, result_vs);
  }
  else{
    std::stringstream msg{};
    msg << "argument is of type '" << field->vs() << "', legal type is either 'ordinal' or 'scalar'\n";
    throw std::runtime_error(msg.str());
  }
}


} // namespace python
} // namespace pcraster_multicore
