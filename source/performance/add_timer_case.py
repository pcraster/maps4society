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


class AddTimerCase(timer_case.TimerCase):

    def set_up(self):
        self.f32_random_1_raster = pcr.readmap(
            self.data.raster_dataset_pathnames["f32_random_1"])
        self.f32_random_2_raster = pcr.readmap(
            self.data.raster_dataset_pathnames["f32_random_2"])

    def tear_down(self):
        pass

    def time_add_pcr_f32_random(self):
        result = pcr.pcrbadd(self.f32_random_1_raster,
            self.f32_random_2_raster)

    def time_add_pcrmc_f32_random(self):
        # pcrmc.set_nr_cpus(8)
        result = pcrmc.pcrmcAdd(self.f32_random_1_raster,
            self.f32_random_2_raster)

    # def time_add_pcr_f32_nodata(self):
    #     result = pcr.add(self.f32_nodata_raster, f32_nodata_raster)

    # def time_add_pcrmc_f32_nodata(self):
    #     result = pcrmc.add(self.f32_nodata_raster, f32_nodata_raster)
