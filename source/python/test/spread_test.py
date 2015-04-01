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

        debug.visualize([cost, point_id], "cost_point_id.png",
            titles=["cost", "point_id"])

        self.assertFalse(cost.mask[0][0])
        self.assertFalse(cost.mask[0][1])
        self.assertFalse(cost.mask[0][2])
        self.assertFalse(cost.mask[0][3])
        self.assertFalse(cost.mask[0][4])
        self.assertFalse(cost.mask[1][0])
        self.assertFalse(cost.mask[1][1])
        self.assertFalse(cost.mask[1][2])
        self.assertFalse(cost.mask[1][3])
        self.assertTrue(cost.mask[1][4])
        self.assertFalse(cost.mask[2][0])
        self.assertFalse(cost.mask[2][1])
        self.assertFalse(cost.mask[2][2])
        self.assertFalse(cost.mask[2][3])
        self.assertFalse(cost.mask[2][4])
        self.assertFalse(cost.mask[3][0])
        self.assertFalse(cost.mask[3][1])
        self.assertFalse(cost.mask[3][2])
        self.assertFalse(cost.mask[3][3])
        self.assertFalse(cost.mask[3][4])
        self.assertFalse(cost.mask[4][0])
        self.assertFalse(cost.mask[4][1])
        self.assertFalse(cost.mask[4][2])
        self.assertFalse(cost.mask[4][3])
        self.assertFalse(cost.mask[4][4])

        self.assertEqual(cost[0][0], 2.83)
        self.assertEqual(cost[0][1], 2.0)
        self.assertEqual(cost[0][2], 2.0)
        self.assertEqual(cost[0][3], 2.0)
        self.assertEqual(cost[0][4], 0.0)
        self.assertEqual(cost[1][0], 2.0)
        self.assertEqual(cost[1][1], 0.0)
        self.assertEqual(cost[1][2], 0.0)
        self.assertEqual(cost[1][3], 0.0)
        self.assertEqual(cost[2][0], 2.0)
        self.assertEqual(cost[2][1], 0.0)
        self.assertEqual(cost[2][2], 2.0)
        self.assertEqual(cost[2][3], 2.0)
        self.assertEqual(cost[2][4], 2.83)
        self.assertEqual(cost[3][0], 2.0)
        self.assertEqual(cost[3][1], 0.0)
        self.assertEqual(cost[3][2], 2.0)
        self.assertEqual(cost[3][3], 4.0)
        self.assertEqual(cost[3][4], 4.83)
        self.assertEqual(cost[4][0], 2.0)
        self.assertEqual(cost[4][1], 0.0)
        self.assertEqual(cost[4][2], 2.0)
        self.assertEqual(cost[4][3], 4.0)
        self.assertEqual(cost[4][4], 6.0)

        self.assertFalse(point_id.mask[0][0])
        self.assertFalse(point_id.mask[0][1])
        self.assertFalse(point_id.mask[0][2])
        self.assertFalse(point_id.mask[0][3])
        self.assertFalse(point_id.mask[0][4])
        self.assertFalse(point_id.mask[1][0])
        self.assertFalse(point_id.mask[1][1])
        self.assertFalse(point_id.mask[1][2])
        self.assertFalse(point_id.mask[1][3])
        self.assertTrue(point_id.mask[1][4])
        self.assertFalse(point_id.mask[2][0])
        self.assertFalse(point_id.mask[2][1])
        self.assertFalse(point_id.mask[2][2])
        self.assertFalse(point_id.mask[2][3])
        self.assertFalse(point_id.mask[2][4])
        self.assertFalse(point_id.mask[3][0])
        self.assertFalse(point_id.mask[3][1])
        self.assertFalse(point_id.mask[3][2])
        self.assertFalse(point_id.mask[3][3])
        self.assertFalse(point_id.mask[3][4])
        self.assertFalse(point_id.mask[4][0])
        self.assertFalse(point_id.mask[4][1])
        self.assertFalse(point_id.mask[4][2])
        self.assertFalse(point_id.mask[4][3])
        self.assertFalse(point_id.mask[4][4])

        self.assertEqual(point_id[0][0], 1)
        self.assertEqual(point_id[0][1], 1)
        self.assertEqual(point_id[0][2], 1)
        self.assertEqual(point_id[0][3], 2)
        self.assertEqual(point_id[0][4], 6)
        self.assertEqual(point_id[1][0], 1)
        self.assertEqual(point_id[1][1], 1)
        self.assertEqual(point_id[1][2], 1)
        self.assertEqual(point_id[1][3], 2)
        self.assertEqual(point_id[2][0], 4)
        self.assertEqual(point_id[2][1], 4)
        self.assertEqual(point_id[2][2], 4)
        self.assertEqual(point_id[2][3], 2)
        self.assertEqual(point_id[2][4], 2)
        self.assertEqual(point_id[3][0], 2)
        self.assertEqual(point_id[3][1], 2)
        self.assertEqual(point_id[3][2], 2)
        self.assertEqual(point_id[3][3], 2)
        self.assertEqual(point_id[3][4], 2)
        self.assertEqual(point_id[4][0], 3)
        self.assertEqual(point_id[4][1], 3)
        self.assertEqual(point_id[4][2], 3)
        self.assertEqual(point_id[4][3], 3)
        self.assertEqual(point_id[4][4], 3)


if __name__ == "__main__":
    unittest.main()
