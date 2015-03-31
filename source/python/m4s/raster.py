import numpy.ma


class Raster(object):
    """
    Create a raster, initialized with zeros or False, depending on the dtype
    passed in.
    """

    def __init__(self,
            nr_rows,
            nr_cols,
            dtype=None,
            fill_value=None):
        if dtype is None:
            if fill_value is not None:
                dtype = type(fill_value)
            # else:
            #     dtype = numpy.float64

        self.elements = numpy.ma.array(
            numpy.zeros((nr_rows, nr_cols), dtype=dtype),
            mask=numpy.zeros((nr_rows, nr_cols), dtype=numpy.bool_))

        if fill_value is not None:
            self.elements.fill(fill_value)

    def __getitem__(self, key):
        return self.elements[key]

    def __str__(self):
        return str(self.elements)

    @property
    def nr_rows(self):
        return self.elements.shape[0]

    @property
    def nr_cols(self):
        return self.elements.shape[1]

    @property
    def dtype(self):
        return self.elements.dtype

    @property
    def mask(self):
        return self.elements.mask

    def mask_all(self):
        self.elements.mask.fill(True)

    def masked(self,
            row,
            col):
        """
        Return whether the addressed cell falls within the raster and is not
        masked. Cells outside of the raster are consired masked cells, just
        like explicitly masked cells that lie within the raster.
        """
        return \
            row < 0 or row >= self.nr_rows or \
            col < 0 or col >= self.nr_cols or \
            self.mask[row][col]
