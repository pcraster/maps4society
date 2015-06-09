#include <boost/python.hpp>
#include "execution_policy.h"
#include "local/local.h"

namespace bp = boost::python;
namespace pmcpy = pcraster_multicore::python;



BOOST_PYTHON_MODULE(_pcraster_multicore){

  bp::def("set_nr_cpus", &pmcpy::set_nr_cpus,
    "Set the number of CPUs used in one algorithms");

//  bp::def("div", &pmcpy::div,
//    bp::return_value_policy<bp::manage_new_object>());

  bp::def("power", &pmcpy::power,
    bp::return_value_policy<bp::manage_new_object>());


}
