#include "m4s/python/local/or.h"

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
#include "fern/algorithm/algebra/boole/or.h"




namespace fa = fern::algorithm;


namespace pcraster_multicore {
namespace python {
namespace detail {

calc::Field* or_number_number(
         const multicore_nonspatial::multicore_nonspatial<UINT1>* arg1,
         const multicore_nonspatial::multicore_nonspatial<UINT1>* arg2,
         multicore_nonspatial::multicore_nonspatial<UINT1>* res){

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreNonspatialInputNoDataPolicy<UINT1>,
        MulticoreNonspatialInputNoDataPolicy<UINT1>>;
  InputNoDataPolicy input_no_data_policy{{*arg1},{*arg2}};

  MulticoreNonspatialOutputNoDataPolicy<UINT1> output_no_data_policy(*res);

  fa::algebra::or_(input_no_data_policy,
    output_no_data_policy, fa::sequential, *arg1, *arg2, *res);

  return res->getField();
}


calc::Field* or_field_field(
         fa::ExecutionPolicy epol,
         const multicore_field::multicore_field<UINT1>* arg1,
         const multicore_field::multicore_field<UINT1>* arg2,
         multicore_field::multicore_field<UINT1>* res){

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreFieldInputNoDataPolicy<UINT1>,
        MulticoreFieldInputNoDataPolicy<UINT1>>;
  InputNoDataPolicy input_no_data_policy{{*arg1},{*arg2}};

  MulticoreFieldOutputNoDataPolicy<UINT1> output_no_data_policy(*res);

  fa::algebra::or_(input_no_data_policy,
    output_no_data_policy, epol, *arg1, *arg2, *res);

  return res->getField();
}


calc::Field* or_number_field(
         fern::algorithm::ExecutionPolicy epol,
         const multicore_nonspatial::multicore_nonspatial<UINT1>* arg1,
         const multicore_field::multicore_field<UINT1>* arg2,
         multicore_field::multicore_field<UINT1>* res){

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreNonspatialInputNoDataPolicy<UINT1>,
    MulticoreFieldInputNoDataPolicy<UINT1>>;

  InputNoDataPolicy input_no_data_policy{{*arg1},{*arg2}};
  MulticoreFieldOutputNoDataPolicy<UINT1> output_no_data_policy(*res);

  fa::algebra::or_(input_no_data_policy,
    output_no_data_policy, epol, *arg1, *arg2, *res);

  return res->getField();
}

} // namespace detail


calc::Field* _or(
         calc::Field* field_a,
         calc::Field* field_b){

  if(boolean_valuescale(*field_a) == false){
    std::stringstream msg{};
    msg << "left operand is of type '" << field_a->vs() << "', legal type is 'boolean'\n";
    throw std::runtime_error(msg.str());
  }
  if(boolean_valuescale(*field_b) == false){
    std::stringstream msg{};
    msg << "right operand is of type '" << field_b->vs() << "', legal type is 'boolean'\n";
    throw std::runtime_error(msg.str());
  }

  calc::Field* res_field = nullptr;

  if((field_a->isSpatial() == false) && (field_b->isSpatial() == false)){
    const multicore_nonspatial::multicore_nonspatial<UINT1> arg1(field_a);
    const multicore_nonspatial::multicore_nonspatial<UINT1> arg2(field_b);
    res_field = new calc::NonSpatial(VS_B);
    multicore_nonspatial::multicore_nonspatial<UINT1> res(res_field);

    return detail::or_number_number(&arg1, &arg2, &res);
  }

  res_field = new calc::Spatial(VS_B, calc::CRI_1, nr_cells());
  multicore_field::multicore_field<UINT1> res(res_field);

  fa::ExecutionPolicy epol = execution_policy();

  if(field_b->isSpatial() == false){
    const multicore_field::multicore_field<UINT1> arg1(field_a);
    const multicore_nonspatial::multicore_nonspatial<UINT1> arg2(field_b);
    return detail::or_number_field(epol, &arg2, &arg1, &res);
  }
  else if(field_a->isSpatial() == false){
    const multicore_nonspatial::multicore_nonspatial<UINT1> arg1(field_a);
    const multicore_field::multicore_field<UINT1> arg2(field_b);
    return detail::or_number_field(epol, &arg1, &arg2, &res);
  }
  else{
    const multicore_field::multicore_field<UINT1> arg1(field_a);
    const multicore_field::multicore_field<UINT1> arg2(field_b);
    return detail::or_field_field(epol, &arg1, &arg2, &res);
  }
}


} // namespace python
} // namespace pcraster_multicore
