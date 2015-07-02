#pragma once

#include "fern/algorithm/core/argument_traits.h"

#include "m4s/wrapper/multicore_nonspatial_input_policy.h"
#include "m4s/wrapper/multicore_nonspatial_output_policy.h"
#include "m4s/wrapper/multicore_nonspatial.h"

namespace fern {
namespace algorithm {

template<class T>
struct ArgumentTraits<multicore_nonspatial::multicore_nonspatial<T>>
{

    using Mask = multicore_nonspatial::multicore_nonspatial<T>;

    using InputNoDataPolicy = MulticoreNonspatialInputNoDataPolicy<Mask>;

    using OutputNoDataPolicy = MulticoreNonspatialOutputNoDataPolicy<T>;

};

} // namespace algorithm
} // namespace fern