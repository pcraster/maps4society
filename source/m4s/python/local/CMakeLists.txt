set(_SOURCES

    and
    or
    xor
    not
    defined

    add
    sub
    mul
    div

    sqrt
    pow
    sqr
    abs
    fac
    ln
    log10
    roundup
    rounddown
    roundoff

    equal
    unequal
    less
    less_equal
    greater
    greater_equal

    ifthen
    ifthenelse

    cover
    minimum
    maximum

    cos
    sin
    tan
    acos
    asin
    atan

    utils
)

add_library(multicore_field_python_locals
    STATIC
        ${_SOURCES}
)




