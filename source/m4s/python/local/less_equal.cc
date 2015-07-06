#include "m4s/python/local/less_equal.h"

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
#include <fern/algorithm/algebra/elementary/less_equal.h>


namespace fa = fern::algorithm;


namespace pcraster_multicore {
namespace python {
namespace detail {


template<class T>
calc::Field* less_equal_number_number(
         const multicore_field::Nonspatial<T>* arg1,
         const multicore_field::Nonspatial<T>* arg2,
         multicore_field::Nonspatial<UINT1>* res){

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreNonspatialInputNoDataPolicy<T>,
        MulticoreNonspatialInputNoDataPolicy<T>>;
  InputNoDataPolicy input_no_data_policy{{*arg1},{*arg2}};

  MulticoreNonspatialOutputNoDataPolicy<UINT1> output_no_data_policy(*res);

  fa::algebra::less_equal(input_no_data_policy,
    output_no_data_policy, fa::sequential, *arg1, *arg2, *res);

  return res->getField();
}


template<class T>
calc::Field* less_equal_field_field(
         fa::ExecutionPolicy epol,
         const multicore_field::Spatial<T>* arg1,
         const multicore_field::Spatial<T>* arg2,
         multicore_field::Spatial<UINT1>* res){

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreFieldInputNoDataPolicy<T>,
        MulticoreFieldInputNoDataPolicy<T>>;
  InputNoDataPolicy input_no_data_policy{{*arg1},{*arg2}};

  MulticoreFieldOutputNoDataPolicy<UINT1> output_no_data_policy(*res);

  fa::algebra::less_equal(input_no_data_policy,
    output_no_data_policy, epol, *arg1, *arg2, *res);

  return res->getField();
}


template<class T>
calc::Field* less_equal_number_field(
         fern::algorithm::ExecutionPolicy epol,
         const multicore_field::Nonspatial<T>* arg1,
         const multicore_field::Spatial<T>* arg2,
         multicore_field::Spatial<UINT1>* res){

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreNonspatialInputNoDataPolicy<T>,
    MulticoreFieldInputNoDataPolicy<T>>;

  InputNoDataPolicy input_no_data_policy{{*arg1},{*arg2}};
  MulticoreFieldOutputNoDataPolicy<UINT1> output_no_data_policy(*res);

  fa::algebra::less_equal(input_no_data_policy,
    output_no_data_policy, epol, *arg1, *arg2, *res);

  return res->getField();
}


template<class T>
calc::Field* less_equal_field_number(
         fern::algorithm::ExecutionPolicy epol,
         const multicore_field::Spatial<T>* arg1,
         const multicore_field::Nonspatial<T>* arg2,
         multicore_field::Spatial<UINT1>* res){

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreFieldInputNoDataPolicy<T>,
    MulticoreNonspatialInputNoDataPolicy<T>>;

  InputNoDataPolicy input_no_data_policy{{*arg1},{*arg2}};
  MulticoreFieldOutputNoDataPolicy<UINT1> output_no_data_policy(*res);

  fa::algebra::less_equal(input_no_data_policy,
    output_no_data_policy, epol, *arg1, *arg2, *res);

  return res->getField();
}


template<class T>
calc::Field* less_equal(
         calc::Field* field_a,
         calc::Field* field_b){

  calc::Field* res_field = nullptr;

  if((field_a->isSpatial() == false) && (field_b->isSpatial() == false)){
    const multicore_field::Nonspatial<T> arg1(field_a);
    const multicore_field::Nonspatial<T> arg2(field_b);
    res_field = new calc::NonSpatial(VS_B);
    multicore_field::Nonspatial<UINT1> res(res_field);

    return detail::less_equal_number_number(&arg1, &arg2, &res);
  }


  res_field = new calc::Spatial(VS_B, calc::CRI_1, nr_cells());
  multicore_field::Spatial<UINT1> res(res_field);

  fa::ExecutionPolicy epol = execution_policy();

  if(field_b->isSpatial() == false){
    const multicore_field::Spatial<T> arg1(field_a);
    const multicore_field::Nonspatial<T> arg2(field_b);

    return detail::less_equal_field_number<T>(epol, &arg1, &arg2, &res);
  }
  else if(field_a->isSpatial() == false){
    const multicore_field::Nonspatial<T> arg1(field_a);
    const multicore_field::Spatial<T> arg2(field_b);

    return detail::less_equal_number_field<T>(epol, &arg1, &arg2, &res);
  }
  else{
    const multicore_field::Spatial<T> arg1(field_a);
    const multicore_field::Spatial<T> arg2(field_b);

    return detail::less_equal_field_field<T>(epol, &arg1, &arg2, &res);
  }
}


} // namespace detail


calc::Field* less_equal(
         calc::Field* field_a,
         calc::Field* field_b){
printf("less equal\n");

  // arguments must be of same VS
  if(ordinal_valuescale(*field_a) == true){
    test_ordinal_valuescale(*field_b, "right operand");
    detail::less_equal<INT4>(field_a, field_b);
  }
  else if(scalar_valuescale(*field_a) == true){
    test_scalar_valuescale(*field_b, "right operand");
    return detail::less_equal<REAL4>(field_a, field_b);
  }
  else{
    std::stringstream msg{};
    msg << "left operand is of type '" << field_b->vs() << "', legal type is either 'ordinal' or 'scalar'\n";
    throw std::runtime_error(msg.str());
  }
}


} // namespace python
} // namespace pcraster_multicore

