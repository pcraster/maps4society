#include "m4s/python/local/tan.h"

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
#include "m4s/python/local/policies.h"

// Fern
#include "fern/algorithm/policy/policies.h"
#include "fern/algorithm/trigonometry/tan.h"


namespace fa = fern::algorithm;


namespace pcraster_multicore {
namespace python {
namespace detail {


calc::Field* tan_scalar(
         calc::Field* field){

  calc::Field* field_result = nullptr;

  if(field->isSpatial() == false){
    const multicore_field::Nonspatial<REAL4> arg(field);

    field_result = new calc::NonSpatial(VS_S);
    multicore_field::Nonspatial<REAL4> result(field_result);

    using InputNoDataPolicy = fa::InputNoDataPolicies<NonspatialDetectNoData<REAL4>>;
    InputNoDataPolicy input_no_data_policy{{arg}};

    NonspatialSetNoData<REAL4> output_no_data_policy(result);

    if(global_option_directional()){
      // fist convert input to radians...
      multicore_field::Nonspatial<REAL4> deg_rad(degrees_to_radians(&arg, &result));

      fa::trigonometry::tan<fa::tan::OutOfDomainPolicy>(input_no_data_policy,
        output_no_data_policy, fa::sequential, deg_rad, result);
    }
    else{
      fa::trigonometry::tan<fa::tan::OutOfDomainPolicy>(input_no_data_policy,
        output_no_data_policy, fa::sequential, arg, result);
    }
    return result.getField();
  }
  else{
    const multicore_field::Spatial<REAL4> arg(field);

    field_result = new calc::Spatial(VS_S, calc::CRI_f, nr_cells());
    multicore_field::Spatial<REAL4> result(field_result);

    fa::ExecutionPolicy epol = execution_policy();

    using InputNoDataPolicy = fa::InputNoDataPolicies<SpatialDetectNoData<REAL4>>;
    InputNoDataPolicy input_no_data_policy{{arg}};

    SpatialSetNoData<REAL4> output_no_data_policy(result);

    if(global_option_directional()){
      // fist convert input to radians...
      multicore_field::Spatial<REAL4> deg_rad(degrees_to_radians(&arg, &result));

      fa::trigonometry::tan<fa::tan::OutOfDomainPolicy>(input_no_data_policy,
        output_no_data_policy, epol, deg_rad, result);
    }
    else{
      fa::trigonometry::tan<fa::tan::OutOfDomainPolicy>(input_no_data_policy,
        output_no_data_policy, epol, arg, result);
    }

    return result.getField();
  }
}


calc::Field* tan_directional(
         calc::Field* field){

  calc::Field* field_result = nullptr;

  if(field->isSpatial() == false){
    const multicore_field::Nonspatial<REAL4> arg(field);

    field_result = new calc::NonSpatial(VS_S);
    multicore_field::Nonspatial<REAL4> result(field_result);

    using InputNoDataPolicy = fa::InputNoDataPolicies<NonspatialDetectNoData<REAL4>>;
    InputNoDataPolicy input_no_data_policy{{arg}};

    NonspatialSetNoData<REAL4> output_no_data_policy(result);

    if(global_option_directional()){
      // fist convert input to radians...
      multicore_field::Nonspatial<REAL4> deg_rad(degrees_to_radians(&arg, &result));

      fa::trigonometry::tan<OutOfDirectionalDomainPolicy>(input_no_data_policy,
        output_no_data_policy, fa::sequential, deg_rad, result);
    }
    else{
      fa::trigonometry::tan<OutOfDirectionalDomainPolicy>(input_no_data_policy,
        output_no_data_policy, fa::sequential, arg, result);
    }
    return result.getField();
  }
  else{
    const multicore_field::Spatial<REAL4> arg(field);

    field_result = new calc::Spatial(VS_S, calc::CRI_f, nr_cells());
    multicore_field::Spatial<REAL4> result(field_result);

    fa::ExecutionPolicy epol = execution_policy();

    using InputNoDataPolicy = fa::InputNoDataPolicies<SpatialDetectNoData<REAL4>>;
    InputNoDataPolicy input_no_data_policy{{arg}};

    SpatialSetNoData<REAL4> output_no_data_policy(result);

    if(global_option_directional()){
      // fist convert input to radians...
      multicore_field::Spatial<REAL4> deg_rad(degrees_to_radians(&arg, &result));

      fa::trigonometry::tan<OutOfDirectionalDomainPolicy>(input_no_data_policy,
        output_no_data_policy, epol, deg_rad, result);
    }
    else{
      fa::trigonometry::tan<OutOfDirectionalDomainPolicy>(input_no_data_policy,
        output_no_data_policy, epol, arg, result);
    }

    return result.getField();
  }
}


} // namespace detail



calc::Field* tan(
         calc::Field* field){
printf("tan\n");
  if(scalar_valuescale(*field)){
    return detail::tan_scalar(field);
  }
  else if(directional_valuescale(*field)){
    return detail::tan_directional(field);
  }
  else{
    throw std::runtime_error("argument type must be either 'scalar' or 'directional' \n");
  }
}


} // namespace python
} // namespace pcraster_multicore

