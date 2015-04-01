import math
import sys
import numpy
from .. import debug
from .. import raster


# Terminology:
# - cost: friction * distance


# Order matters. This is the order in which the original PCRaster algorithm
# visited the cells. If you change the order, the answer will be different
# in case the cost of visiting multiply neighboring cells is equal.
neighbors = (
    (1, -1), (1, 0), (1, 1),     # South cells.
    (0, -1), (0, 1),             # West and east cells.
    (-1, -1), (-1, 0), (-1, 1))  # North cells.


class AddressesToVisit(object):

    def __init__(self,
            nr_rows,
            nr_cols,
            cell_size):
        # List of row, col tuples of cells to spread from.
        self.list_of_cells = []

        # Raster with cells to spread from marked.
        # Boolean raster. False means 'not in list', True means 'in list'.
        self.raster = raster.Raster(nr_rows, nr_cols, cell_size,
            dtype=numpy.bool_)

    def __nonzero__(self):
        return len(self.list_of_cells) > 0

    def push(self,
            row,
            col):
        assert ((row, col) in self.list_of_cells) == self.raster[row][col]

        if not (row, col) in self.list_of_cells:
            self.list_of_cells.append((row, col))
            self.raster[row][col] = True

        assert ((row, col) in self.list_of_cells) == self.raster[row][col]

    def pop(self):
        assert len(self.list_of_cells) > 0

        row, col = self.list_of_cells.pop()
        assert self.raster[row][col]
        self.raster[row][col] = False

        assert ((row, col) in self.list_of_cells) == self.raster[row][col]

        return row, col


def calc_spread_value(
        cost,
        point_id,
        friction,
        row,
        col):
    f = friction[row][col]
    cell_size = cost.cell_size

    min_costs = sys.float_info.max
    new_id = 0

    for neighbor in neighbors:
        row_next = row + neighbor[0]
        col_next = col + neighbor[1]

        if not cost.masked(row_next, col_next) and not \
                friction.masked(row_next, col_next):
            f_next = friction[row_next][col_next]
            costs = (f + f_next) / 2.0

            if 0 in neighbor:
                # Vertical/horizonal neighbor.
                costs *= cell_size
            else:
                # Diagonal neighbor.
                costs *= cell_size * math.sqrt(2.0)

            costs += cost[row_next][col_next]

            if costs < min_costs:
                # Cheapest path from neighbor to row, col.
                min_costs = costs
                new_id = point_id[row_next][col_next]
                assert new_id != 0

    # If new_id is still 0, then no cheaper path was found. In that case,
    # min_costs is still the max float value.
    assert (new_id == 0 and min_costs == sys.float_info.max) or \
        (new_id != 0 and min_costs < sys.float_info.max)

    # new_id   : id of cheapest neighbor.
    # min_costs: minimum costs to get to row, col.
    return min_costs, new_id


def perform_spread(
        cost,
        point_id,
        addresses_to_visit,
        friction):

    nr_rows = cost.nr_rows
    nr_cols = cost.nr_cols

    # While there are points to spread from.
    iteration = 0
    while(addresses_to_visit):
        iteration += 1
        debug.visualize(addresses_to_visit.raster,
            "cells_to_visit_{}.png".format(iteration))
        # Pop address of cell from the current collection with addresses to
        # visit.
        row, col = addresses_to_visit.pop()

        # Iterate over all neighboring cells.
        for neighbor in neighbors:
            row_next = row + neighbor[0]
            col_next = col + neighbor[1]

            if not friction.masked(row_next, col_next) and not \
                    point_id.masked(row_next, col_next):

                id = point_id[row_next][col_next]

                if id != 0:
                    # Already visited.
                    current_cost = cost[row_next][col_next]

                new_cost, new_id = calc_spread_value(cost, point_id, friction,
                    row_next, col_next)

                if new_id != 0 and (
                        # First route was found.
                        (id == 0) or
                        # Cheaper route was found.
                        (new_cost < current_cost and (not numpy.isclose(
                            new_cost, current_cost)))):

                    # A cheaper or first route to this cell was found.
                    # Inspect the neighbors too.
                    addresses_to_visit.push(row_next, col_next)
                    cost.mask[row_next][col_next] = False
                    cost[row_next][col_next] = new_cost
                    point_id[row_next][col_next] = new_id

    return cost, point_id


def spread_all(
        points,
        initial_cost,
        friction):
    assert isinstance(points, raster.Raster)

    nr_rows = points.nr_rows
    nr_cols = points.nr_cols
    cell_size = points.cell_size

    if isinstance(initial_cost, (int, float)):
        initial_cost = raster.Raster(nr_rows, nr_cols, cell_size,
            dtype=numpy.float32, fill_value=initial_cost)

    if isinstance(friction, (int, float)):
        friction = raster.Raster(nr_rows, nr_cols, cell_size,
            dtype=numpy.float32, fill_value=friction)

    # Initialize the collection identifying the cells that need to be
    # visited. Initially, this collection is empty.
    addresses_to_visit = AddressesToVisit(nr_rows, nr_cols, cell_size)

    # Mask all result costs.
    cost = raster.Raster(nr_rows, nr_cols, cell_size, dtype=numpy.float32)
    cost.mask_all()

    # Initialize result point_id with 0, which is not a valid id for points
    # passed into this function. None of the result point id cells is masked.
    point_id = raster.Raster(nr_rows, nr_cols, cell_size, dtype=points.dtype)

    # Iterate over all cells.
    for row in xrange(nr_rows):
        for col in xrange(nr_cols):

            # Select cells with a valid point and friction.
            if not points.mask[row][col] and not friction.mask[row][col]:

                # Verify friction value is within domain.
                f = friction[row][col]
                if f < 0.0:
                    raise RuntimeError("Domain error: friction must be >= 0.0")

                p = points[row][col]

                # Select cells with non-zero point. Points with a value of
                # zero are not considered.
                if p != 0:

                    if initial_cost.mask[row][col]:
                        # No valid initial cost for this cell.
                        point_id.mask[row][col] = True
                    else:
                        cost.mask[row][col] = False
                        cost[row][col] = initial_cost[row][col]
                        point_id[row][col] = p
                        addresses_to_visit.push(row, col)
            else:
                # No valid point or friction for this cell.
                point_id.mask[row][col] = True

    cost, point_id = perform_spread(cost, point_id, addresses_to_visit,
        friction)

    return cost, point_id


def spread_zone(
        points,
        initial_cost,
        friction):
    return spread_all(points, initial_cost, friction)[1]


def spread(
        points,
        initial_cost,
        friction):
    return spread_all(points, initial_cost, friction)[0]
