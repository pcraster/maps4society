import os.path
import sys
import unittest
import numpy
sys.path = [os.path.join(os.path.dirname(__file__), "..")] + sys.path
import m4s.debug as debug
import m4s.raster as raster
import m4s.operation.spread as spread


class SpreadTest(unittest.TestCase):

    def test_spread(self):
        nr_rows = 5
        nr_cols = 5
        cell_size = 2.0
        dtype = numpy.int32
        points = raster.Raster(nr_rows, nr_cols, cell_size, dtype=dtype)

        points[0][4] = 6
        points[1][1] = 1
        points[1][2] = 1
        points[1][3] = 2
        points.mask[1][4] = True
        points[2][1] = 4
        points[3][1] = 2
        points[4][1] = 3

        cost, point_id = spread.spread_all(points, 0, 1)

        self.assertEqual(cost.dtype, numpy.float32)

        numpy.testing.assert_equal(cost.mask, [
            [False, False, False, False, False],
            [False, False, False, False, True],
            [False, False, False, False, False],
            [False, False, False, False, False],
            [False, False, False, False, False],
        ])

        numpy.testing.assert_almost_equal(cost.elements, [
            [2.8284271, 2.0, 2.0, 2.0, 0.0],
            [2.0, 0.0, 0.0, 0.0, numpy.nan],
            [2.0, 0.0, 2.0, 2.0, 2.8284271],
            [2.0, 0.0, 2.0, 4.0, 4.8284273],
            [2.0, 0.0, 2.0, 4.0, 6.0],
        ])

        numpy.testing.assert_equal(point_id.mask, [
            [False, False, False, False, False],
            [False, False, False, False, True],
            [False, False, False, False, False],
            [False, False, False, False, False],
            [False, False, False, False, False],
        ])

        numpy.testing.assert_equal(point_id.elements, [
            [1, 1, 1, 2, 6],
            [1, 1, 1, 2, numpy.nan],
            [4, 4, 4, 2, 2],
            [2, 2, 2, 2, 2],
            [3, 3, 3, 3, 3],
        ])


if __name__ == "__main__":
    unittest.main()
