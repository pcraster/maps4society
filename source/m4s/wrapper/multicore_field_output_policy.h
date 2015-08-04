#pragma once

#include "csftypes.h"

#include "m4s/wrapper/multicore_field.h"
//#include "m4s/wrapper/datatype_traits/multicore_spatial.h"
//#include "fern/core/data_type_traits.h"
//#include "fern/core/data_type_traits/scalar.h"

template<class T>
class SpatialSetNoData
{

private:

    using value_type = typename fern::DataTypeTraits<T>::value_type;//fern::value_type<T>;

public:

                   SpatialSetNoData    (multicore_field::Spatial<T> & aField);

                   ~SpatialSetNoData   ()=default;

    void           mark_as_no_data     (size_t index);

    void           mark_as_no_data     (size_t row,
                                        size_t col);

protected:

                   SpatialSetNoData    ()=delete;

                   SpatialSetNoData    (SpatialSetNoData const&)=delete;

                   SpatialSetNoData    (SpatialSetNoData&&)=default;

    SpatialSetNoData&    operator=     (SpatialSetNoData const&)=delete;

    SpatialSetNoData&    operator=     (SpatialSetNoData&&)=default;

private:

    multicore_field::Spatial<T> & _field;

};


template<class T>
inline SpatialSetNoData<T>::SpatialSetNoData(
    multicore_field::Spatial<T> & aField)

    : _field(aField)

{
}


template<class T>
inline void SpatialSetNoData<T>::mark_as_no_data(
    size_t index)
{
   _field.set_cell(index);
}

