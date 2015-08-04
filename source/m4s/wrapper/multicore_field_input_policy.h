#pragma once

#include "csftypes.h"
#include "com_mvop.h"

#include "multicore_field.h"
#include "fern/core/data_type_traits/scalar.h"


template<class T>
class SpatialDetectNoData
{

private:

    using value_type = fern::value_type<T>;


public:

                   SpatialDetectNoData(multicore_field::Spatial<T> const& aField) noexcept;

                   ~SpatialDetectNoData()=default;

    bool           is_no_data          (size_t index) const;

    bool           is_no_data          (size_t row,
                                        size_t col) const;


                   SpatialDetectNoData (SpatialDetectNoData const& other)
                                            =default;
    SpatialDetectNoData&
                   operator=           (SpatialDetectNoData const&)=default;



protected:
                   SpatialDetectNoData (SpatialDetectNoData&& other) =default;

    SpatialDetectNoData&
                   operator=           (SpatialDetectNoData&&)=default;

                   SpatialDetectNoData ()=delete;

private:

    multicore_field::Spatial<T> const&    _field;

};


template<class T>
inline SpatialDetectNoData<T>::SpatialDetectNoData(
    multicore_field::Spatial<T> const& aField) noexcept

    : _field(aField)

{
}


template<class T>
inline bool SpatialDetectNoData<T>::is_no_data(
    size_t index) const
{
    return pcr::isMV(_field.get_cells()[index]);
}

