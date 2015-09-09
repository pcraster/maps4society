#include "m4s/python/total/maptotal.h"

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
#include "fern/algorithm/statistic/sum.h"

namespace fa = fern::algorithm;


namespace pcraster_multicore {
namespace python {
namespace detail {

} // namespace detail


calc::Field* maptotal(
         calc::Field* field){

  assert_equal_location_attributes(*field);

  if(field->isSpatial() == false){
    throw std::runtime_error("argument is non-spatial, only spatial allowed\n");
  }

  if(scalar_valuescale(*field) == true){
    const multicore_field::Spatial<REAL4> arg1(field);
    using InputNoDataPolicy = fa::InputNoDataPolicies<SpatialDetectNoData<REAL4>>;
    InputNoDataPolicy input_no_data_policy{{arg1}};

    calc::Field* res_field = nullptr;

    res_field = new calc::NonSpatial(VS_S);
    multicore_field::Nonspatial<REAL4> res(res_field);

    NonspatialSetNoData<REAL4> output_no_data_policy(res);

    fa::ExecutionPolicy epol = execution_policy();

    fa::statistic::sum<fa::sum::OutOfRangePolicy>(input_no_data_policy, output_no_data_policy, epol, arg1, res);

    return res.getField();
  }
  else{
    std::stringstream msg{};
    msg << "argument is of type '" << field->vs() << "', legal type is 'scalar'\n";
    throw std::runtime_error(msg.str());
  }
}


} // namespace python
} // namespace pcraster_multicore
