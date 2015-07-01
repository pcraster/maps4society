#include "m4s/python/local/less.h"

// PCRaster
#include "calc_spatial.h"
#include "calc_nonspatial.h"

// Field wrapper
#include "m4s/wrapper/multicore_field.h"
#include "m4s/wrapper/multicore_field_traits.h"
#include "m4s/wrapper/multicore_field_output_policy.h"
#include "m4s/wrapper/multicore_field_input_policy.h"

#include "m4s/wrapper/multicore_nonspatial.h"
#include "m4s/wrapper/multicore_nonspatial_traits.h"
#include "m4s/wrapper/multicore_nonspatial_output_policy.h"
#include "m4s/wrapper/multicore_nonspatial_input_policy.h"

#include "m4s/python/execution_policy.h"
#include "m4s/python/local/utils.h"

// Fern
#include "fern/algorithm/policy/policies.h"
#include <fern/algorithm/algebra/elementary/less.h>


namespace fa = fern::algorithm;


namespace pcraster_multicore {
namespace python {
namespace detail {

// calc::Field* and_number_number(
//          const multicore_nonspatial::multicore_nonspatial<UINT1>* arg1,
//          const multicore_nonspatial::multicore_nonspatial<UINT1>* arg2,
//          multicore_nonspatial::multicore_nonspatial<UINT1>* res){
// 
//   using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreNonspatialInputNoDataPolicy<UINT1>,
//         MulticoreNonspatialInputNoDataPolicy<UINT1>>;
//   InputNoDataPolicy input_no_data_policy{{*arg1},{*arg2}};
// 
//   MulticoreNonspatialOutputNoDataPolicy<UINT1> output_no_data_policy(*res);
// 
//   fa::algebra::and_(input_no_data_policy,
//     output_no_data_policy, fa::sequential, *arg1, *arg2, *res);
// 
//   return res->getField();
// }
// 
//

template<class T>
calc::Field* less_field_field(
         fa::ExecutionPolicy epol,
         const multicore_field::multicore_field<T>* arg1,
         const multicore_field::multicore_field<T>* arg2,
         multicore_field::multicore_field<UINT1>* res){

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreFieldInputNoDataPolicy<T>,
        MulticoreFieldInputNoDataPolicy<T>>;
  InputNoDataPolicy input_no_data_policy{{*arg1},{*arg2}};

  MulticoreFieldOutputNoDataPolicy<UINT1> output_no_data_policy(*res);

  fa::algebra::less(input_no_data_policy,
    output_no_data_policy, epol, *arg1, *arg2, *res);

  return res->getField();
}

template<class T>
calc::Field* less_number_field(
         fern::algorithm::ExecutionPolicy epol,
         const multicore_nonspatial::multicore_nonspatial<T>* arg1,
         const multicore_field::multicore_field<T>* arg2,
         multicore_field::multicore_field<UINT1>* res){

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreNonspatialInputNoDataPolicy<T>,
    MulticoreFieldInputNoDataPolicy<T>>;

  InputNoDataPolicy input_no_data_policy{{*arg1},{*arg2}};
  MulticoreFieldOutputNoDataPolicy<UINT1> output_no_data_policy(*res);

  fa::algebra::less(input_no_data_policy,
    output_no_data_policy, epol, *arg1, *arg2, *res);

  return res->getField();
}

template<class T>
calc::Field* less_field_number(
         fern::algorithm::ExecutionPolicy epol,
         const multicore_field::multicore_field<T>* arg1,
         const multicore_nonspatial::multicore_nonspatial<T>* arg2,
         multicore_field::multicore_field<UINT1>* res){

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreFieldInputNoDataPolicy<T>,
    MulticoreNonspatialInputNoDataPolicy<T>>;

  InputNoDataPolicy input_no_data_policy{{*arg1},{*arg2}};
  MulticoreFieldOutputNoDataPolicy<UINT1> output_no_data_policy(*res);

  fa::algebra::less(input_no_data_policy,
    output_no_data_policy, epol, *arg1, *arg2, *res);

  return res->getField();
}


template<class T>
calc::Field* less(
         calc::Field* field_a,
         calc::Field* field_b){

  calc::Field* res_field = nullptr;

  if((field_a->isSpatial() == false) && (field_b->isSpatial() == false)){
//     const multicore_nonspatial::multicore_nonspatial<UINT1> arg1(field_a);
//     const multicore_nonspatial::multicore_nonspatial<UINT1> arg2(field_b);
//     res_field = new calc::NonSpatial(VS_B);
//     multicore_nonspatial::multicore_nonspatial<UINT1> res(res_field);
// 
//     return detail::and_number_number(&arg1, &arg2, &res);
throw std::runtime_error("WIP");
  }


  res_field = new calc::Spatial(VS_B, calc::CRI_1, nr_cells());
  multicore_field::multicore_field<UINT1> res(res_field);

  fa::ExecutionPolicy epol = execution_policy();

  if(field_b->isSpatial() == false){
    const multicore_field::multicore_field<T> arg1(field_a);
    const multicore_nonspatial::multicore_nonspatial<T> arg2(field_b);
      printf("less FN detail less real\n");
    return detail::less_field_number<T>(epol, &arg1, &arg2, &res);
  }
  else if(field_a->isSpatial() == false){
    const multicore_nonspatial::multicore_nonspatial<T> arg1(field_a);
    const multicore_field::multicore_field<T> arg2(field_b);
      printf("less NF detail less real\n");
    return detail::less_number_field<T>(epol, &arg1, &arg2, &res);
  }
  else{
    const multicore_field::multicore_field<T> arg1(field_a);
    const multicore_field::multicore_field<T> arg2(field_b);
      printf("less FF detail less real\n");
    return detail::less_field_field<T>(epol, &arg1, &arg2, &res);
  }
}

} // namespace detail


calc::Field* less(
         calc::Field* field_a,
         calc::Field* field_b){

  // all kind of error checking first...
  // arguments must be of same VS
  if(ordinal_valuescale(*field_a) == true){
    if(ordinal_valuescale(*field_b) == true){
       detail::less<INT4>(field_a, field_b);
    }
    else{
      std::stringstream msg{};
      msg << "right operand is of type '" << field_b->vs() << "', legal type is 'ordinal'\n";
      throw std::runtime_error(msg.str());
    }
  }
  else if(scalar_valuescale(*field_a) == true){
    if(scalar_valuescale(*field_b) == true){
      printf("less FF real\n");
      return detail::less<REAL4>(field_a, field_b);
    }
    else{
      std::stringstream msg{};
      msg << "right operand is of type '" << field_b->vs() << "', legal type is 'scalar'\n";
      throw std::runtime_error(msg.str());
    }
  }
  else{
    std::stringstream msg{};
    msg << "left operand is of type '" << field_b->vs() << "', legal type is either 'ordinal' or 'scalar'\n";
    throw std::runtime_error(msg.str());
  }
}


} // namespace python
} // namespace pcraster_multicore

