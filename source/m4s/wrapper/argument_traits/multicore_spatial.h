#pragma once

#include "fern/algorithm/core/argument_traits.h"

#include "m4s/wrapper/multicore_field_input_policy.h"
#include "m4s/wrapper/multicore_field_output_policy.h"
#include "m4s/wrapper/multicore_field.h"

namespace fern {
namespace algorithm {

template<class T>
struct ArgumentTraits<multicore_field::Spatial<T>>
{

    using Mask = multicore_field::Spatial<T>;

    using InputNoDataPolicy = MulticoreFieldInputNoDataPolicy<Mask>;

    using OutputNoDataPolicy = MulticoreFieldOutputNoDataPolicy<T>;

};


} // namespace algorithm
} // namespace fern
