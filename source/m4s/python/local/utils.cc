#include <cassert>
#include <sstream>


#include "calc_nonspatial.h"
#include "calc_spatial.h"
#include "pcrdatatype.h"
#include "Globals.h"
#include "appargs.h"

#include "fern/algorithm/policy/execution_policy.h"

#include "m4s/python/local/mul.h"
#include "m4s/python/execution_policy.h"
#include "m4s/wrapper/multicore_field.h"
// #include "m4s/wrapper/multicore_field_traits.h"
// #include "m4s/wrapper/multicore_field_output_policy.h"
// #include "m4s/wrapper/multicore_field_input_policy.h"
// #include "m4s/python/execution_policy.h"
// 
#include "m4s/wrapper/multicore_nonspatial.h"
// #include "m4s/wrapper/multicore_nonspatial_traits.h"
// #include "m4s/wrapper/multicore_nonspatial_output_policy.h"
// #include "m4s/wrapper/multicore_nonspatial_input_policy.h"





namespace pcraster {
namespace python {
  extern Globals globals;
}
}


namespace fa = fern::algorithm;

namespace pcraster_multicore {
namespace python {




size_t nr_rows(){
  return pcraster::python::globals.cloneSpace().nrRows();
}
size_t nr_cols(){
  return pcraster::python::globals.cloneSpace().nrCols();
}
size_t nr_cells(){
  return pcraster::python::globals.cloneSpace().nrRows() * pcraster::python::globals.cloneSpace().nrCols();
}





bool scalar_valuescale(const calc::Field& aField){
  PCR_VS field_vs = VS_UNKNOWN;
  field_vs = aField.vs();
  return field_vs == VS_S ? true : false;
}


bool directional_valuescale(const calc::Field& aField){
  PCR_VS field_vs = VS_UNKNOWN;
  field_vs = aField.vs();
  return field_vs == VS_D ? true : false;
}


bool boolean_valuescale(const calc::Field& aField){
  PCR_VS field_vs = VS_UNKNOWN;
  field_vs = aField.vs();
  return field_vs == VS_B ? true : false;
}


bool ordinal_valuescale(const calc::Field& aField){
  PCR_VS field_vs = VS_UNKNOWN;
  field_vs = aField.vs();
  return field_vs == VS_O ? true : false;
}





void test_scalar_valuescale(const calc::Field& aField, const std::string& msg){
  PCR_VS field_vs = VS_UNKNOWN;
  field_vs = aField.vs();

  if(field_vs != VS_S){
    std::stringstream err_msg{};
    err_msg << msg << " is of type '" << field_vs << "', legal type is 'scalar'\n";
    throw std::runtime_error(err_msg.str());
  }
}


void test_ordinal_valuescale(const calc::Field& aField, const std::string& msg){
  PCR_VS field_vs = VS_UNKNOWN;
  field_vs = aField.vs();

  if(field_vs != VS_O){
    std::stringstream err_msg{};
    err_msg << msg << " is of type '" << field_vs << "', legal type is 'ordinal'\n";
    throw std::runtime_error(err_msg.str());
  }
}



calc::Field* degrees_radians(const multicore_field::Spatial<REAL4>* aField/*, size_t nr_cells*/){
// fa::ExecutionPolicy epol = execution_policy();
//     const REAL4 conversion_factor = M_PI/180.0f;
// 
//     calc::Field* field_conv = new calc::Spatial(VS_S, calc::CRI_f, nr_cells());
//     multicore_field::Spatial<REAL4> deg_rad(field_conv);
//     mul_field_number(epol, aField, conversion_factor, &deg_rad);
// 
//  return field_conv;
}

calc::Field* degrees_radians(const multicore_field::Nonspatial<REAL4>* aField){
//     const REAL4 conversion_factor = M_PI/180.0f;
// 
//     calc::Field* field_conv = new calc::NonSpatial(VS_S);
//     multicore_field::Nonspatial<REAL4> deg_rad(field_conv);
//     mul_number_number(aField, conversion_factor, &deg_rad);

// return field_conv;
}






bool global_option_directional(){
  return appDirection == APP_DEGREES ? true : false;
//   if(appDirection == APP_DEGREES){
//     return true;
//   }
//   else{
//     return false;
//   }
}


// the PCRaster nonspatials return with mutliple valuescales based on the input value
// that will break the value scale checking in the algorithms
calc::Field* newNonSpatialScalar(double value){
  return new calc::NonSpatial(VS_S, value);
}





} // namespace python
} // namespace pcraster_multicore

