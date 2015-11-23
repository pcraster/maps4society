import os
import sys

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


class SlopeTimerCase(timer_case.TimerCase):

    @classmethod
    def set_up_class(cls):
        cls.f32_random_1_raster = pcr.readmap(
            cls.data.raster_dataset_pathnames["f32_random_1"])


    def time_slope_pcr_f32_random(self):
        result = pcr.slope(
            self.f32_random_1_raster)


    def time_slope_pcrmc_f32_random(self):
        result = pcrmc.slope(
            self.f32_random_1_raster)


    # time_slope_pcr_f32_random.repeat = 3
    # time_slope_pcrmc_f32_random.repeat = 3
