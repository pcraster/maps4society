#include <boost/python.hpp>
#include "m4s/python/execution_policy.h"
#include "m4s/python/local/local.h"
#include "m4s/python/focal/focal.h"

namespace bp = boost::python;
namespace pmcpy = pcraster_multicore::python;



BOOST_PYTHON_MODULE(_pcraster_multicore){

  bp::def("set_nr_cpus", &pmcpy::set_nr_cpus,
    "Set the number of CPUs used in one algorithms");

  // Local operations
  bp::def("_and", &pmcpy::_and,
    bp::return_value_policy<bp::manage_new_object>());
//   bp::def("_or", &pmcpy::_or,
//     bp::return_value_policy<bp::manage_new_object>());
//   bp::def("_not", &pmcpy::_not,
//     bp::return_value_policy<bp::manage_new_object>());
//   bp::def("add", &pmcpy::add,
//     bp::return_value_policy<bp::manage_new_object>());
//   bp::def("sub", &pmcpy::sub,
//     bp::return_value_policy<bp::manage_new_object>());
//   bp::def("mul", &pmcpy::mul,
//     bp::return_value_policy<bp::manage_new_object>());
//   bp::def("div", &pmcpy::div,
//     bp::return_value_policy<bp::manage_new_object>());
// 
//   bp::def("sqrt", &pmcpy::sqrt,
//     bp::return_value_policy<bp::manage_new_object>());
// 
//   bp::def("power", &pmcpy::power,
//     bp::return_value_policy<bp::manage_new_object>());
// 
//   bp::def("cos", &pmcpy::cos,
//     bp::return_value_policy<bp::manage_new_object>());
//   bp::def("sin", &pmcpy::sin,
//     bp::return_value_policy<bp::manage_new_object>());
//   bp::def("tan", &pmcpy::tan,
//     bp::return_value_policy<bp::manage_new_object>());


  // Focal operations
//   bp::def("slope", &pmcpy::slope,
//     bp::return_value_policy<bp::manage_new_object>());
  //bp::def("upstream", &pmcpy::upstream,
  //  bp::return_value_policy<bp::manage_new_object>());
}
