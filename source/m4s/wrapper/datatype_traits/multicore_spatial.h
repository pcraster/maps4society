#pragma once

#include "fern/core/data_type_traits.h"
#include "m4s/wrapper/multicore_field.h"


namespace fern {


template<class T>
struct DataTypeTraits<multicore_field::multicore_field<T>>{

  using value_type = T;

  using reference = T&;

  using const_reference = T const&;

  using argument_category = raster_2d_tag;

};

} // namespace fern
