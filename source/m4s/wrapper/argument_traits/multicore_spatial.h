#pragma once


#include "m4s/wrapper/multicore_field_input_policy.h"
#include "m4s/wrapper/multicore_field_output_policy.h"
#include "m4s/wrapper/multicore_field.h"
#include "fern/algorithm/core/argument_traits.h"

namespace fern {
namespace algorithm {

template<class T>
struct ArgumentTraits<multicore_field::Spatial<T>>
{

    using Mask = multicore_field::Spatial<T>;

    using InputNoDataPolicy = SpatialDetectNoData<T>;

    using OutputNoDataPolicy = SpatialSetNoData<T>;

};


} // namespace algorithm
} // namespace fern
