#include <cassert>

#include "calc_spatial.h"
#include "pcrdatatype.h"
#include "Globals.h"

#include "fern/algorithm/policy/execution_policy.h"

// #include "m4s/python/local/mul.h"
// #include "m4s/python/execution_policy.h"
// #include "m4s/wrapper/multicore_field.h"
// #include "m4s/wrapper/multicore_field_traits.h"
// #include "m4s/wrapper/multicore_field_output_policy.h"
// #include "m4s/wrapper/multicore_field_input_policy.h"
// #include "m4s/python/execution_policy.h"
// 
// #include "m4s/wrapper/multicore_nonspatial.h"
// #include "m4s/wrapper/multicore_nonspatial_traits.h"
// #include "m4s/wrapper/multicore_nonspatial_output_policy.h"
// #include "m4s/wrapper/multicore_nonspatial_input_policy.h"

#include <iostream>



namespace pcraster {
namespace python {
  extern Globals globals;
}
}


namespace fa = fern::algorithm;

namespace pcraster_multicore {
namespace python {

/// todo: this should be removed soon as we wrap the nonspatials now as well...
float nonspatial_value(const calc::Field* aField){
  assert(aField->isSpatial() == false);

  double value = 0.0;
  bool valid = aField->getCell(value, 1);
  assert(valid == true);

  return static_cast<REAL4>(value);
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





/// this is needed...
/*
calc::Field* degrees_radians(const multicore_field::multicore_field<REAL4>* aField, size_t nr_cells){
fa::ExecutionPolicy epol = execution_policy();
    const REAL4 conversion_factor = M_PI/180.0;

    calc::Field* field_conv = new calc::Spatial(VS_S, calc::CRI_f, nr_cells);
    multicore_field::multicore_field<REAL4> deg_rad(field_conv);
    mul_field_number(epol, aField, conversion_factor, &deg_rad);

 return field_conv;

}*/





size_t nr_rows(){
  return pcraster::python::globals.cloneSpace().nrRows();
}
size_t nr_cols(){
  return pcraster::python::globals.cloneSpace().nrCols();
}
size_t nr_cells(){
  return pcraster::python::globals.cloneSpace().nrRows() * pcraster::python::globals.cloneSpace().nrCols();
}




} // namespace python
} // namespace pcraster_multicore

