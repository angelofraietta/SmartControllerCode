
#define NUM_WD_FLASHES	8

//#ifndef WATCHDOG_PIN
#define WATCHDOG_PIN	PIN_C0
//#endif

void FlashWatchdog(int16 ms_time)
{
		output_high (WATCHDOG_PIN);
		restart_wdt();
#ifndef _SIMULATE
		delay_ms (ms_time);
#endif
		restart_wdt();
		output_low (WATCHDOG_PIN);
#ifndef _SIMULATE
		delay_ms (ms_time);
#endif
		restart_wdt();
}

void SetWatchdogLed (short value)
{
	output_bit (WATCHDOG_PIN, value);
}

void InitialiseWatchdog()
{
	int i;
	for (i = 0; i < NUM_WD_FLASHES; i++)
		{
			FlashWatchdog(100);
			restart_wdt();
		}
}

