#!/usr/bin/env bash
set -e
pa.py plot --real slope.pdf timings.db SlopeTimerCase_time_slope_pcr_f32_random SlopeTimerCase_time_slope_pcrmc_f32_random
pa.py plot --real add.pdf timings.db AddTimerCase_time_add_pcr_f32_random AddTimerCase_time_add_pcrmc_f32_random
pa.py plot --real sqrt.pdf timings.db SqrtTimerCase_time_sqrt_pcr_f32_random SqrtTimerCase_time_sqrt_pcrmc_f32_random
