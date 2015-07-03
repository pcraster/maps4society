#pragma once
#include <cassert>
//#include "fern/algorithm/policy/execution_policy.h"
#include "calc_spatial.h"
#include "pcrdatatype.h"

namespace calc {
  class Field;
}

namespace multicore_field{
  template<class T>
  class multicore_field;
}


namespace multicore_nonspatial{
  template<class T>
  class multicore_nonspatial;
}

namespace pcraster_multicore {
namespace python {


size_t nr_rows();
size_t nr_cols();
size_t nr_cells();

//float nonspatial_value(const calc::Field* aField);

bool scalar_valuescale(const calc::Field& aField);

bool directional_valuescale(const calc::Field& aField);

bool boolean_valuescale(const calc::Field& aField);

bool ordinal_valuescale(const calc::Field& aField);


void test_scalar_valuescale(const calc::Field& aField, const std::string& msg);

void test_ordinal_valuescale(const calc::Field& aField, const std::string& msg);

//multicore_nonspatial::multicore_nonspatial<REAL4>* degrees_radians_nonspatial(const calc::Field* aField);

calc::Field* degrees_radians(const multicore_field::multicore_field<REAL4>* aField, size_t nr_cells);


calc::Field* newNonSpatialScalar(double value);

} // namespace python
} // namespace pcraster_multicore

