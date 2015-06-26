#include "m4s/python/focal/slope.h"

#include <stdexcept>

// PCRaster
#include "calc_spatial.h"
#include "Globals.h"
#include "appargs.h"


// Field wrapper
#include "m4s/wrapper/multicore_field.h"
#include "m4s/wrapper/multicore_field_traits.h"
#include "m4s/wrapper/multicore_field_output_policy.h"
#include "m4s/wrapper/multicore_field_input_policy.h"
#include "m4s/python/execution_policy.h"

// Fern
#include "fern/algorithm/policy/policies.h"
#include "fern/algorithm/space/focal/slope.h"



namespace fa = fern::algorithm;


namespace pcraster_multicore {
namespace python {


calc::Field* slope(
         calc::Field* field_dem){

  if(appUnitTrue == false){
    throw std::runtime_error("not implemented for global option 'unitcell'\n");
  }

  if(field_dem->isSpatial() == false){
    throw std::runtime_error("argument is non-spatial, only spatial is allowed\n");
  }

  calc::Spatial* field_result = new calc::Spatial(VS_S, calc::CRI_f, field_dem->nrValues());
  multicore_field::multicore_field<REAL4> result(field_result);

  const multicore_field::multicore_field<REAL4> arg1(field_dem);

  fa::ExecutionPolicy epol = execution_policy();

  using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreFieldInputNoDataPolicy<REAL4>>;
  InputNoDataPolicy input_no_data_policy{{arg1}};

  MulticoreFieldOutputNoDataPolicy<REAL4> output_no_data_policy(result);

  fa::space::slope<fa::slope::OutOfRangePolicy>(
        input_no_data_policy, output_no_data_policy,
        epol, arg1, result);

  return result.getField();
}


} // namespace python
} // namespace pcraster_multicore

