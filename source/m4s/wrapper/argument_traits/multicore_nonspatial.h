#pragma once

#include "fern/algorithm/core/argument_traits.h"

#include "m4s/wrapper/multicore_nonspatial_input_policy.h"
#include "m4s/wrapper/multicore_nonspatial_output_policy.h"
#include "m4s/wrapper/multicore_nonspatial.h"

namespace fern {
namespace algorithm {

template<class T>
struct ArgumentTraits<multicore_field::Nonspatial<T>>
{

    using Mask = multicore_field::Nonspatial<T>;

    using InputNoDataPolicy = NonspatialDetectNoData<T>;

    using OutputNoDataPolicy = NonspatialSetNoData<T>;

};

} // namespace algorithm
} // namespace fern
