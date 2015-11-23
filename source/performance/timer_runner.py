#!/usr/bin/env python
import performance_analyst as pa


loader = pa.TimerLoader()


# pa.StreamTimerRunner().run(
pa.SQLiteTimerRunner(database_name="timings.db").run(
    pa.TimerSuite([
        loader.load_timers_from_name("add_timer_case.AddTimerCase"),
        loader.load_timers_from_name("sqrt_timer_case.SqrtTimerCase"),
]))
