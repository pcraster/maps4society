#include <iostream>

#include "execution_policy.h"


namespace fa = fern::algorithm;


namespace pcraster_multicore {
namespace python {


static fa::ExecutionPolicy _execution_policy{
    fa::ParallelExecutionPolicy{}};


void set_nr_cpus(size_t cpus){
  size_t max_cpus = std::thread::hardware_concurrency();
  if(cpus > max_cpus){
    std::cout << "Number of CPUs requested (" << cpus << ") larger than CPUs available, limiting to " << max_cpus << " CPUs" << std::endl;
    cpus = max_cpus;
  }
  if(cpus < 1){
    cpus = 1;
  }
  _execution_policy = fa::ParallelExecutionPolicy{cpus};
}


fa::ExecutionPolicy const& execution_policy(){
  return _execution_policy;
}

} // namespace python
} // namespace pcraster_multicore
