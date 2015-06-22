#include "m4s/python/local/pow.h"

// PCRaster
#include "calc_spatial.h"
#include "calc_nonspatial.h"
#include "Globals.h"

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
#include "fern/algorithm/algebra/elementary/pow.h"


namespace fa = fern::algorithm;

namespace pcraster {
namespace python {
  extern Globals globals;
}
}


namespace pcraster_multicore {
namespace python {

calc::Field* power(
         calc::Field* field_a,
         calc::Field* field_b){

  calc::Field* res_field = nullptr;

  if((field_a->isSpatial() == false) && (field_b->isSpatial() == false)){
    const multicore_nonspatial::multicore_nonspatial<REAL4> arg1(field_a);
    const multicore_nonspatial::multicore_nonspatial<REAL4> arg2(field_b);
    res_field = new calc::NonSpatial(VS_S);
    multicore_nonspatial::multicore_nonspatial<REAL4> res(res_field);

    return power_number_number(&arg1, &arg2, &res);
  }

  size_t r = pcraster::python::globals.cloneSpace().nrRows();
  size_t c = pcraster::python::globals.cloneSpace().nrCols();
  size_t nr_cells = r * c;

  res_field = new calc::Spatial(VS_S, calc::CRI_f, nr_cells);
  multicore_field::multicore_field<REAL4> res(res_field);

  fa::ExecutionPolicy epol = execution_policy();

  if(field_b->isSpatial() == false){
    const multicore_field::multicore_field<REAL4> arg1(field_a);
    return power_field_number(epol, &arg1, nonspatial_value(field_b), &res);
  }
  else if(field_a->isSpatial() == false){
    const multicore_field::multicore_field<REAL4> arg2(field_b);
    return power_number_field(epol, nonspatial_value(field_a), &arg2, &res);
  }
  else{
    const multicore_field::multicore_field<REAL4> arg1(field_a);
    const multicore_field::multicore_field<REAL4> arg2(field_b);
    return power_field_field(epol, &arg1, &arg2, &res);
  }
}

calc::Field* power_number_number(
         const multicore_nonspatial::multicore_nonspatial<REAL4>* arg1,
         const multicore_nonspatial::multicore_nonspatial<REAL4>* arg2,
         multicore_nonspatial::multicore_nonspatial<REAL4>* res){

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreNonspatialInputNoDataPolicy<REAL4>,
        MulticoreNonspatialInputNoDataPolicy<REAL4>>;
  InputNoDataPolicy input_no_data_policy{{*arg1},{*arg2}};

  MulticoreNonspatialOutputNoDataPolicy<REAL4> output_no_data_policy(*res);

  fa::algebra::pow<fa::pow::OutOfDomainPolicy,
    fa::pow::OutOfRangePolicy>(input_no_data_policy,
    output_no_data_policy, fa::sequential, *arg1, *arg2, *res);

  return res->getField();
}


calc::Field* power_field_field(
         fa::ExecutionPolicy epol,
         const multicore_field::multicore_field<REAL4>* arg1,
         const multicore_field::multicore_field<REAL4>* arg2,
         multicore_field::multicore_field<REAL4>* res){

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreFieldInputNoDataPolicy<REAL4>,
        MulticoreFieldInputNoDataPolicy<REAL4>>;
  InputNoDataPolicy input_no_data_policy{{*arg1},{*arg2}};

  MulticoreFieldOutputNoDataPolicy<REAL4> output_no_data_policy(*res);

  fa::algebra::pow<fa::pow::OutOfDomainPolicy,
    fa::pow::OutOfRangePolicy>(input_no_data_policy,
    output_no_data_policy, epol, *arg1, *arg2, *res);

  return res->getField();
}


calc::Field* power_field_number(
         fern::algorithm::ExecutionPolicy epol,
         const multicore_field::multicore_field<REAL4>* arg1,
         REAL4 arg2,
         multicore_field::multicore_field<REAL4>* res){

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreFieldInputNoDataPolicy<REAL4>,
        fa::SkipNoData>;

  InputNoDataPolicy input_no_data_policy{{*arg1},{}};
  MulticoreFieldOutputNoDataPolicy<REAL4> output_no_data_policy(*res);

  fa::algebra::pow<fa::pow::OutOfDomainPolicy,
    fa::pow::OutOfRangePolicy>(input_no_data_policy,
    output_no_data_policy, epol, *arg1, arg2, *res);

  return res->getField();
}


calc::Field* power_number_field(
         fern::algorithm::ExecutionPolicy epol,
         REAL4 arg1,
         const multicore_field::multicore_field<REAL4>* arg2,
         multicore_field::multicore_field<REAL4>* res){


  using InputNoDataPolicy = fa::InputNoDataPolicies<fa::SkipNoData,
    MulticoreFieldInputNoDataPolicy<REAL4>>;

  InputNoDataPolicy input_no_data_policy{{},{*arg2}};
  MulticoreFieldOutputNoDataPolicy<REAL4> output_no_data_policy(*res);

  fa::algebra::pow<fa::pow::OutOfDomainPolicy,
    fa::pow::OutOfRangePolicy>(input_no_data_policy,
    output_no_data_policy, epol, arg1, *arg2, *res);

  return res->getField();
}


} // namespace python
} // namespace pcraster_multicore

