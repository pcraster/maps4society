#include <boost/python.hpp>
#include "m4s/python/execution_policy.h"
#include "m4s/python/local/local.h"

namespace bp = boost::python;
namespace pmcpy = pcraster_multicore::python;



BOOST_PYTHON_MODULE(_pcraster_multicore){

  bp::def("set_nr_cpus", &pmcpy::set_nr_cpus,
    "Set the number of CPUs used in one algorithms");

//  bp::def("add", &pmcpy::add,
//    bp::return_value_policy<bp::manage_new_object>());
//
//  bp::def("sub", &pmcpy::sub,
//    bp::return_value_policy<bp::manage_new_object>());
//
//  bp::def("mul", &pmcpy::mul,
//    bp::return_value_policy<bp::manage_new_object>());
//
  bp::def("div", &pmcpy::div,
    bp::return_value_policy<bp::manage_new_object>());




  bp::def("power", &pmcpy::power,
    bp::return_value_policy<bp::manage_new_object>());


}
