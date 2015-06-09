#pragma once

// PCRaster
#include "calc_spatial.h"

// Field wrapper
#include "multicore_field_traits.h"
#include "multicore_field_output_policy.h"
#include "multicore_field_input_policy.h"
#include "../execution_policy.h"

#include "fern/algorithm/algebra/elementary/pow.h"
#include "fern/algorithm/policy/policies.h"


namespace fa = fern::algorithm;



namespace pcraster_multicore {
namespace python {


inline calc::Field* power_field_field(calc::Field * field_a,
          calc::Field * field_b){

  calc::Spatial* res_field = new calc::Spatial(VS_S, calc::CRI_f, field_a->nrValues());

  const multicore_field::multicore_field<REAL4> arg1(field_a);
  const multicore_field::multicore_field<REAL4> arg2(field_b);
  multicore_field::multicore_field<REAL4> res(res_field);

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreFieldInputNoDataPolicy<REAL4>,
        MulticoreFieldInputNoDataPolicy<REAL4>>;
  InputNoDataPolicy input_no_data_policy{{arg1},{arg2}};

  MulticoreFieldOutputNoDataPolicy<REAL4> output_no_data_policy(res);

  fa::ExecutionPolicy epol = execution_policy();
  fa::algebra::pow<fa::pow::OutOfDomainPolicy,
    fa::pow::OutOfRangePolicy>(input_no_data_policy,
    output_no_data_policy, epol, arg1, arg2, res);

  return res.getField();
}


inline calc::Field* power_field_number(calc::Field * field_a,
          calc::Field * field_b){

  calc::Spatial* res_field = new calc::Spatial(VS_S, calc::CRI_f, field_a->nrValues());

  const multicore_field::multicore_field<REAL4> arg1(field_a);
  double arg2 = -999.9;
  field_b->getCell(arg2, 1);
  multicore_field::multicore_field<REAL4> res(res_field);

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreFieldInputNoDataPolicy<REAL4>,
        fa::SkipNoData>;

  InputNoDataPolicy input_no_data_policy{{arg1},{}};
  MulticoreFieldOutputNoDataPolicy<REAL4> output_no_data_policy(res);

  fa::ExecutionPolicy epol = execution_policy();
  fa::algebra::pow<fa::pow::OutOfDomainPolicy,
    fa::pow::OutOfRangePolicy>(input_no_data_policy,
    output_no_data_policy, epol, arg1, static_cast<REAL4>(arg2), res);

  return res.getField();
}



inline calc::Field* power_number_field(calc::Field * field_a,
          calc::Field * field_b){

  calc::Spatial* res_field = new calc::Spatial(VS_S, calc::CRI_f, field_b->nrValues());

  double arg1 = -999.9;
  field_a->getCell(arg1, 1);
  const multicore_field::multicore_field<REAL4> arg2(field_b);
  multicore_field::multicore_field<REAL4> res(res_field);

  using InputNoDataPolicy = fa::InputNoDataPolicies<fa::SkipNoData,
    MulticoreFieldInputNoDataPolicy<REAL4>>;

  InputNoDataPolicy input_no_data_policy{{},{arg2}};
  MulticoreFieldOutputNoDataPolicy<REAL4> output_no_data_policy(res);

  fa::ExecutionPolicy epol = execution_policy();
  fa::algebra::pow<fa::pow::OutOfDomainPolicy,
    fa::pow::OutOfRangePolicy>(input_no_data_policy,
    output_no_data_policy, epol, static_cast<REAL4>(arg1), arg2, res);

  return res.getField();
}


inline calc::Field * power(calc::Field * field_a, calc::Field * field_b){

  if(!(field_b->isSpatial())){
    return power_field_number(field_a, field_b);
  }
  else if(!(field_a->isSpatial())){
    return power_number_field(field_a, field_b);
  }
  else{
    return power_field_field(field_a, field_b);
  }
}


} // namespace python
} // namespace pcraster_multicore

