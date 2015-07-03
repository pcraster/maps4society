#include "m4s/python/local/sqrt.h"
#include "m4s/python/local/utils.h"

// PCRaster
#include "calc_spatial.h"
#include "calc_nonspatial.h"


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
#include "fern/algorithm/algebra/elementary/sqrt.h"



namespace fa = fern::algorithm;


namespace pcraster_multicore {
namespace python {
namespace detail {

} // namespace detail


calc::Field* sqrt(
         calc::Field* field){

  test_scalar_valuescale(*field, "argument");

  calc::Field* field_result = nullptr;

  if(field->isSpatial() == false){
    const multicore_field::Nonspatial<REAL4> arg(field);

    field_result = new calc::NonSpatial(VS_S);
    multicore_field::Nonspatial<REAL4> result(field_result);

    using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreNonspatialInputNoDataPolicy<REAL4>>;
    InputNoDataPolicy input_no_data_policy{{arg}};

    MulticoreNonspatialOutputNoDataPolicy<REAL4> output_no_data_policy(result);

     fa::algebra::sqrt<fa::sqrt::OutOfDomainPolicy>(input_no_data_policy,
       output_no_data_policy, fa::sequential, arg, result);

    return result.getField();
  }

  const multicore_field::Spatial<REAL4> arg(field);

  field_result = new calc::Spatial(VS_S, calc::CRI_f, nr_cells());
  multicore_field::Spatial<REAL4> result(field_result);

  fa::ExecutionPolicy epol = execution_policy();

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreFieldInputNoDataPolicy<REAL4>>;
  InputNoDataPolicy input_no_data_policy{{arg}};

  MulticoreFieldOutputNoDataPolicy<REAL4> output_no_data_policy(result);

 fa::algebra::sqrt<fa::sqrt::OutOfDomainPolicy>(input_no_data_policy,
   output_no_data_policy, epol, arg, result);

  return result.getField();
}


} // namespace python
} // namespace pcraster_multicore

