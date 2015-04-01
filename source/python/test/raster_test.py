import os.path
import sys
import unittest
import numpy
sys.path = [os.path.join(os.path.dirname(__file__), "..")] + sys.path
import m4s.raster as raster


class RasterTest(unittest.TestCase):

    def test_fill_value(self):
        nr_rows = 3
        nr_cols = 2
        cell_size = 5.0

        raster_ = raster.Raster(nr_rows, nr_cols, cell_size, fill_value=4)

        self.assertEqual(raster_.nr_rows, nr_rows)
        self.assertEqual(raster_.nr_cols, nr_cols)
        self.assertEqual(raster_.cell_size, cell_size)
        self.assertEqual(raster_.dtype, numpy.int64)

        self.assertEqual(raster_[0][0], 4)
        self.assertEqual(raster_[0][1], 4)
        self.assertEqual(raster_[1][0], 4)
        self.assertEqual(raster_[1][1], 4)
        self.assertEqual(raster_[2][0], 4)
        self.assertEqual(raster_[2][1], 4)

        raster_ = raster.Raster(nr_rows, nr_cols, cell_size, fill_value=4.5)

        self.assertEqual(raster_.nr_rows, nr_rows)
        self.assertEqual(raster_.nr_cols, nr_cols)
        self.assertEqual(raster_.cell_size, cell_size)
        self.assertEqual(raster_.dtype, numpy.float64)

        self.assertEqual(raster_[0][0], 4.5)
        self.assertEqual(raster_[0][1], 4.5)
        self.assertEqual(raster_[1][0], 4.5)
        self.assertEqual(raster_[1][1], 4.5)
        self.assertEqual(raster_[2][0], 4.5)
        self.assertEqual(raster_[2][1], 4.5)

    def test_boole_raster(self):
        nr_rows = 3
        nr_cols = 2
        cell_size = 4.5
        dtype = numpy.bool_
        raster_ = raster.Raster(nr_rows, nr_cols, cell_size, dtype=dtype)

        self.assertEqual(raster_.nr_rows, nr_rows)
        self.assertEqual(raster_.nr_cols, nr_cols)
        self.assertEqual(raster_.cell_size, cell_size)
        self.assertEqual(raster_.dtype, dtype)

        # Default value is False.
        self.assertEqual(raster_[0][0], False)
        self.assertEqual(raster_[0][1], False)
        self.assertEqual(raster_[1][0], False)
        self.assertEqual(raster_[1][1], False)
        self.assertEqual(raster_[2][0], False)
        self.assertEqual(raster_[2][1], False)

        # Default mask is False.
        self.assertEqual(raster_.mask[0][0], False)
        self.assertEqual(raster_.mask[0][1], False)
        self.assertEqual(raster_.mask[1][0], False)
        self.assertEqual(raster_.mask[1][1], False)
        self.assertEqual(raster_.mask[2][0], False)
        self.assertEqual(raster_.mask[2][1], False)

        raster_.mask_all()
        self.assertEqual(raster_.mask[0][0], True)
        self.assertEqual(raster_.mask[0][1], True)
        self.assertEqual(raster_.mask[1][0], True)
        self.assertEqual(raster_.mask[1][1], True)
        self.assertEqual(raster_.mask[2][0], True)
        self.assertEqual(raster_.mask[2][1], True)


if __name__ == "__main__":
    unittest.main()
