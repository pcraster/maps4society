#include "m4s/python/local/not.h"

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
#include "fern/algorithm/algebra/boole/not.h"


namespace fa = fern::algorithm;


namespace pcraster_multicore {
namespace python {
namespace detail {


calc::Field* not_number(
         const multicore_field::Nonspatial<UINT1>* arg1,
         multicore_field::Nonspatial<UINT1>* res){

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreNonspatialInputNoDataPolicy<UINT1>>;
  InputNoDataPolicy input_no_data_policy{{*arg1}};

  MulticoreNonspatialOutputNoDataPolicy<UINT1> output_no_data_policy(*res);

  fa::algebra::not_(input_no_data_policy,
    output_no_data_policy, fa::sequential, *arg1, *res);

  return res->getField();
}


calc::Field* not_spatial(
         fa::ExecutionPolicy epol,
         const multicore_field::Spatial<UINT1>* arg1,
         multicore_field::Spatial<UINT1>* res){

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreFieldInputNoDataPolicy<UINT1>>;
  InputNoDataPolicy input_no_data_policy{{*arg1}};

  MulticoreFieldOutputNoDataPolicy<UINT1> output_no_data_policy(*res);

  fa::algebra::not_(input_no_data_policy,
    output_no_data_policy, epol, *arg1, *res);

  return res->getField();
}

} // namespace detail


calc::Field* _not(
         calc::Field* field_a){

  if(boolean_valuescale(*field_a) == false){
    std::stringstream msg{};
    msg << "operand is of type '" << field_a->vs() << "', legal type is 'boolean'\n";
    throw std::runtime_error(msg.str());
  }

  calc::Field* res_field = nullptr;

  if(field_a->isSpatial() == false){
    const multicore_field::Nonspatial<UINT1> arg1(field_a);
    res_field = new calc::NonSpatial(VS_B);
    multicore_field::Nonspatial<UINT1> res(res_field);

    return detail::not_number(&arg1, &res);
  }

  res_field = new calc::Spatial(VS_B, calc::CRI_1, nr_cells());
  multicore_field::Spatial<UINT1> res(res_field);

  fa::ExecutionPolicy epol = execution_policy();

  const multicore_field::Spatial<UINT1> arg1(field_a);

  return detail::not_spatial(epol, &arg1, &res);
}


} // namespace python
} // namespace pcraster_multicore

