import matplotlib.pyplot as pyplot
from .. import raster


def visualize_rasters(
        rasters,
        filename,
        titles=None):
    nr_rows = rasters[0].nr_rows
    nr_cols = rasters[0].nr_cols

    if titles is None:
        titles = [None for raster in rasters]

    assert len(rasters) == len(titles)

    figure, axes = pyplot.subplots(1, len(rasters),
        figsize=(len(rasters) * 5, 5), subplot_kw={'xticks': [], 'yticks': []})

    figure.subplots_adjust(hspace=0.3, wspace=0.05)

    for axis, raster, title in zip(axes.flat if len(rasters) > 1 else [axes],
            rasters, titles):
        axis.imshow(raster.elements, interpolation="none")

        if title is not None:
            axis.set_title(title)

        for row in xrange(nr_rows):
            for col in xrange(nr_cols):
                if not raster.mask[row][col]:
                    value = raster[row][col]
                    axis.text(col, row, value, va='center', ha='center')

    pyplot.savefig(filename, transparent=True)
    pyplot.close(figure)


def visualize(
        data,
        filename,
        titles=None):
    if isinstance(data, list):
        visualize_rasters(data, filename, titles)
    elif isinstance(data, raster.Raster):
        visualize_rasters([data], filename,
            titles=None if titles is None else [titles])
    else:
        raise NotImplementedError
