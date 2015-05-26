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

        numpy.testing.assert_equal(raster_.elements, [
            [4, 4],
            [4, 4],
            [4, 4],
        ])

        raster_ = raster.Raster(nr_rows, nr_cols, cell_size, fill_value=4.5)

        self.assertEqual(raster_.nr_rows, nr_rows)
        self.assertEqual(raster_.nr_cols, nr_cols)
        self.assertEqual(raster_.cell_size, cell_size)
        self.assertEqual(raster_.dtype, numpy.float64)

        numpy.testing.assert_almost_equal(raster_.elements, [
            [4.5, 4.5],
            [4.5, 4.5],
            [4.5, 4.5],
        ])

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
        numpy.testing.assert_equal(raster_.elements, [
            [False, False],
            [False, False],
            [False, False],
        ])

        # Default mask is False.
        numpy.testing.assert_equal(raster_.mask, [
            [False, False],
            [False, False],
            [False, False],
        ])

        raster_.mask_all()
        numpy.testing.assert_equal(raster_.mask, [
            [True, True],
            [True, True],
            [True, True],
        ])


if __name__ == "__main__":
    unittest.main()
