#include "m4s/python/local/sin.h"

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
#include "fern/algorithm/trigonometry/sin.h"


namespace fa = fern::algorithm;


namespace pcraster_multicore {
namespace python {
namespace detail {


calc::Field* sin_scalar(
         calc::Field* field){

  calc::Field* field_result = nullptr;

  if(field->isSpatial() == false){
    const multicore_field::Nonspatial<REAL4> arg(field);

    field_result = new calc::NonSpatial(VS_S);
    multicore_field::Nonspatial<REAL4> result(field_result);

    using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreNonspatialInputNoDataPolicy<REAL4>>;
    InputNoDataPolicy input_no_data_policy{{arg}};

    MulticoreNonspatialOutputNoDataPolicy<REAL4> output_no_data_policy(result);

    if(global_option_directional()){
      // fist convert input to radians...
      multicore_field::Nonspatial<REAL4> deg_rad(degrees_to_radians(&arg, &result));

      fa::trigonometry::sin<fa::sin::OutOfDomainPolicy>(input_no_data_policy,
        output_no_data_policy, fa::sequential, deg_rad, result);
    }
    else{
      fa::trigonometry::sin<fa::sin::OutOfDomainPolicy>(input_no_data_policy,
        output_no_data_policy, fa::sequential, arg, result);
    }
    return result.getField();
  }
  else{
    const multicore_field::Spatial<REAL4> arg(field);

    field_result = new calc::Spatial(VS_S, calc::CRI_f, nr_cells());
    multicore_field::Spatial<REAL4> result(field_result);

    fa::ExecutionPolicy epol = execution_policy();

    using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreFieldInputNoDataPolicy<REAL4>>;
    InputNoDataPolicy input_no_data_policy{{arg}};

    MulticoreFieldOutputNoDataPolicy<REAL4> output_no_data_policy(result);

    if(global_option_directional()){
      // fist convert input to radians...
      multicore_field::Spatial<REAL4> deg_rad(degrees_to_radians(&arg, &result));

      fa::trigonometry::sin<fa::sin::OutOfDomainPolicy>(input_no_data_policy,
        output_no_data_policy, epol, deg_rad, result);
    }
    else{
      fa::trigonometry::sin<fa::sin::OutOfDomainPolicy>(input_no_data_policy,
        output_no_data_policy, epol, arg, result);
    }

    return result.getField();
  }
}


calc::Field* sin_directional(
         calc::Field* field){

  calc::Field* field_result = nullptr;

  if(field->isSpatial() == false){
    const multicore_field::Nonspatial<REAL4> arg(field);

    field_result = new calc::NonSpatial(VS_S);
    multicore_field::Nonspatial<REAL4> result(field_result);

    using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreNonspatialInputNoDataPolicy<REAL4>>;
    InputNoDataPolicy input_no_data_policy{{arg}};

    MulticoreNonspatialOutputNoDataPolicy<REAL4> output_no_data_policy(result);

    if(global_option_directional()){
      // fist convert input to radians...
      multicore_field::Nonspatial<REAL4> deg_rad(degrees_to_radians(&arg, &result));

      fa::trigonometry::sin<OutOfDirectionalDomainPolicy>(input_no_data_policy,
        output_no_data_policy, fa::sequential, deg_rad, result);
    }
    else{
      fa::trigonometry::sin<OutOfDirectionalDomainPolicy>(input_no_data_policy,
        output_no_data_policy, fa::sequential, arg, result);
    }
    return result.getField();
  }
  else{
    const multicore_field::Spatial<REAL4> arg(field);

    field_result = new calc::Spatial(VS_S, calc::CRI_f, nr_cells());
    multicore_field::Spatial<REAL4> result(field_result);

    fa::ExecutionPolicy epol = execution_policy();

    using InputNoDataPolicy = fa::InputNoDataPolicies<MulticoreFieldInputNoDataPolicy<REAL4>>;
    InputNoDataPolicy input_no_data_policy{{arg}};

    MulticoreFieldOutputNoDataPolicy<REAL4> output_no_data_policy(result);

    if(global_option_directional()){
      // fist convert input to radians...
      multicore_field::Spatial<REAL4> deg_rad(degrees_to_radians(&arg, &result));

      fa::trigonometry::sin<OutOfDirectionalDomainPolicy>(input_no_data_policy,
        output_no_data_policy, epol, deg_rad, result);
    }
    else{
      fa::trigonometry::sin<OutOfDirectionalDomainPolicy>(input_no_data_policy,
        output_no_data_policy, epol, arg, result);
    }

    return result.getField();
  }
}


} // namespace detail



calc::Field* sin(
         calc::Field* field){
printf("sin\n");
  if(scalar_valuescale(*field)){
    return detail::sin_scalar(field);
  }
  else if(directional_valuescale(*field)){
    return detail::sin_directional(field);
  }
  else{
    throw std::runtime_error("argument type must be either 'scalar' or 'directional' \n");
  }
}


} // namespace python
} // namespace pcraster_multicore

