import os
import sys
import psutil

sys.path = [
    # TODO Use ${PCRASTER_PYTHON_ROOT}
    os.path.join(os.environ["PEACOCK_PREFIX"],
        "maps4society/linux/linux/gcc-4/x86_64/include/../python"),
    # TODO Use ${CMAKE_BINARY_DIR}/bin
    os.path.join(os.environ["OBJECTS"], os.environ["MY_DEVENV_BUILD_TYPE"],
        "maps4society/bin"),
] + sys.path

import pcraster as pcr
import pcraster5.multicore as pcrmc
import timer_case


class SqrtTimerCase(timer_case.TimerCase):

    @classmethod
    def set_up_class(cls):
        cls.f32_random_1_raster = pcr.readmap(
            cls.data.raster_dataset_pathnames["f32_random_1"])


    def set_up(self):
        # Set the number of cpus to use by the algorithm to the default.
        pcrmc.set_nr_cpus(psutil.cpu_count(logical=True))


    def time_sqrt_pcr_f32_random(self):
        result = pcr.sqrt(
            self.f32_random_1_raster)


    def time_sqrt_pcrmc_f32_random(self):
        result = pcrmc.sqrt(
            self.f32_random_1_raster)


    # time_sqrt_pcr_f32_random.repeat = 3
    # time_sqrt_pcrmc_f32_random.repeat = 3


def create_method(
        nr_logical_cpus):

    def method(self):
        pcrmc.set_nr_cpus(nr_logical_cpus)
        result = pcrmc.sqrt(
            self.f32_random_1_raster)

    method.__name__ = "time_sqrt_{}".format(nr_logical_cpus)

    return method


def add_sqrt_cases():

    for n in xrange(1, psutil.cpu_count(logical=True) + 1):
        SqrtTimerCase.add_method(create_method(n))


add_sqrt_cases()
