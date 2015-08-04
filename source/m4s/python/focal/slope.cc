#include "m4s/python/focal/slope.h"

#include <stdexcept>

// PCRaster
#include "calc_spatial.h"
#include "Globals.h"
#include "appargs.h"


// Field wrapper
#include "m4s/wrapper/argument_customization_points/multicore_spatial.h"
#include "m4s/wrapper/datatype_customization_points/multicore_spatial.h"
#include "m4s/wrapper/datatype_traits/multicore_spatial.h"
#include "m4s/wrapper/argument_traits/multicore_spatial.h"

#include "m4s/python/execution_policy.h"

// Fern
#include "fern/core/data_type_traits/scalar.h"  /// todo
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
  multicore_field::Spatial<REAL4> result(field_result);

  fa::ExecutionPolicy epol = execution_policy();

  const multicore_field::Spatial<REAL4> arg(field_dem);
  using InputNoDataPolicy = fa::InputNoDataPolicies<SpatialDetectNoData<REAL4>>;
  InputNoDataPolicy input_no_data_policy{{arg}};

  SpatialSetNoData<REAL4> output_no_data_policy(result);

//   fa::space::slope<fa::slope::OutOfRangePolicy>(
//         input_no_data_policy, output_no_data_policy,
//         fa::sequential, arg, result);

  fa::space::slope<fa::slope::OutOfRangePolicy>(
        input_no_data_policy, output_no_data_policy,
        fa::sequential, arg, result);

  return result.getField();
}


} // namespace python
} // namespace pcraster_multicore

