#!/usr/bin/env python
import performance_analyst as pa


loader = pa.TimerLoader()


pa.StreamTimerRunner().run(
    loader.load_timers_from_name("add_timer_case.AddTimerCase"),
)
