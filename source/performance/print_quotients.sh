#!/usr/bin/env bash
set -e

echo slope
pa.py stat --quotient timings.db SlopeTimerCase_time_slope_pcr_f32_random SlopeTimerCase_time_slope_pcrmc_f32_random

echo add
pa.py stat --quotient timings.db AddTimerCase_time_add_pcr_f32_random AddTimerCase_time_add_pcrmc_f32_random

echo sqrt
pa.py stat --quotient timings.db SqrtTimerCase_time_sqrt_pcr_f32_random SqrtTimerCase_time_sqrt_pcrmc_f32_random
