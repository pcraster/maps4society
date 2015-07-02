#pragma once

#include "m4s/wrapper/multicore_field.h"
#include "fern/algorithm/core/argument_customization_point.h"

namespace fern {
namespace algorithm {

template<typename T>
inline multicore_nonspatial::multicore_nonspatial<T>& mask(
    multicore_nonspatial::multicore_nonspatial<T>& argument)
{
    return argument;
}

} // namespace algorithm
} // namespace fern
