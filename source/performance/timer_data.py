import os
import numpy
from osgeo import gdal
from osgeo.gdalconst import *
import configuration


def write_array_to_raster(
        array,
        pathname):
    tmp_pathname = "{}.tif".format(pathname)
    nr_rows, nr_cols = array.shape

    tiff_driver = gdal.GetDriverByName("GTiff")
    tiff_dataset = tiff_driver.Create(tmp_pathname, nr_cols, nr_rows, 1,
        gdal.GDT_Float32)
    tiff_dataset.GetRasterBand(1).WriteArray(array)

    pcr_driver = gdal.GetDriverByName("PCRaster")
    pcr_dataset = pcr_driver.CreateCopy(pathname, tiff_dataset, 0)

    os.remove(tmp_pathname)


class TimerData(object):
    """
    Timer cases require all kinds of data sets. Instances of this class
    generate data, if necessary. No data is generated if it alread exists.
    """

    nr_rows = 6000
    nr_cols = 80000

    def __init__(self):
        self.raster_dataset_pathnames = {}
        self.make_workspace_directory()
        self.generate_f32_random_raster("f32_random_1")
        self.generate_f32_random_raster("f32_random_2")
        # self.generate_f32_nodata_raster("f32_nodata")

    def dataset_pathname(self,
            dataset_name):
        return os.path.join(os.path.abspath(configuration.workspace),
            dataset_name)

    def make_workspace_directory(self):
        pathname = configuration.workspace

        if not os.path.exists(pathname):
            os.mkdir(pathname)

    def generate_f32_random_raster(self,
            dataset_name):
        pathname = self.dataset_pathname(dataset_name) + ".map"

        if not os.path.exists(pathname):
            # - Generate a 2D numpy array with random values.
            # - Pass the array to GDAL and create a PCRaster raster from it.
            array = numpy.random.rand(self.nr_rows, self.nr_cols)
            write_array_to_raster(array, pathname)

        self.raster_dataset_pathnames[dataset_name] = pathname

    def generate_f32_nodata_raster(self,
            dataset_name):
        pathname = self.dataset_pathname(dataset_name) + ".map"

        if not os.path.exists(pathname):
            print "go!"

        self.raster_dataset_pathnames[dataset_name] = pathname
