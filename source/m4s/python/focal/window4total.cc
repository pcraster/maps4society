#include "m4s/python/focal/window4total.h"


// PCRaster
#include "pcrtree2/calc_spatial.h"


// Field wrapper
#include "m4s/wrapper/datatype_customization_points/multicore_spatial.h"
#include "m4s/wrapper/datatype_traits/multicore_spatial.h"
#include "m4s/wrapper/argument_customization_points/multicore_spatial.h"
#include "m4s/wrapper/argument_traits/multicore_spatial.h"

#include "m4s/python/execution_policy.h"
#include "m4s/python/local/utils.h"


// Fern
#include "fern/algorithm/convolution/neighborhood/square.h"
#include "fern/algorithm/convolution/neighborhood/square_traits.h"
#include "fern/algorithm/convolution/convolve.h"
#include "fern/algorithm/convolution/policies.h"
#include "fern/core/data_customization_point.h"



namespace fa = fern::algorithm;


namespace pcraster_multicore {
namespace python {
namespace detail {


template<
    typename InputNoDataPolicy,
    typename OutputNoDataPolicy,
    typename ExecutionPolicy,
    typename Value,
    typename Result
>
void w4t(
    InputNoDataPolicy const& input_no_data_policy,
    OutputNoDataPolicy& output_no_data_policy,
    ExecutionPolicy& execution_policy,
    Value const& value,
    Result& result){


    //fern::Square<bool, 1> window_kernel({ on the todo list
    fern::Square<INT4, 1> window_kernel({
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    });

    //test, test...
//     fern::Square<INT4, 1> window_kernel({
//     #include "buf.inc"
//     });

    fa::convolution::convolve<
        fern::algorithm::convolve::SkipNoData,
        fa::convolve::DontDivideByWeights,
        fern::algorithm::convolve::SkipOutOfImage,
        fa::convolve::OutOfRangePolicy>(
           input_no_data_policy, output_no_data_policy,
           execution_policy, value, window_kernel, result);

}


} //namespace detail


calc::Field* window4total(
         calc::Field * field){

  assert_equal_location_attributes(*field);
  assert_scalar_valuescale(*field, "argument");

  if(field->isSpatial() == false){
    throw std::runtime_error("argument is non-spatial, only spatial is allowed\n");
  }

  const multicore_field::Spatial<REAL4> arg(field);

  calc::Spatial* field_result = new calc::Spatial(VS_S, calc::CRI_f, nr_cells());
  multicore_field::Spatial<REAL4> result(field_result);

  fa::ExecutionPolicy epol = execution_policy();

  using InputNoDataPolicy = fa::InputNoDataPolicies<SpatialDetectNoData<REAL4>>;
  InputNoDataPolicy input_no_data_policy{{arg}};

  SpatialSetNoData<REAL4> output_no_data_policy(result);

  detail::w4t(input_no_data_policy, output_no_data_policy, epol, arg, result);

  return field_result;
}


} // namespace python
} // namespace pcraster_multicore
