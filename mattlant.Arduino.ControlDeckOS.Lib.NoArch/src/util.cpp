#include "util.h"

	int lc_loops_per_sec[LC_LOOPS_TO_AVG] = {};
	unsigned long lc_last_time = 0;
	float lc_avg_loops_per_second = 0;
	int lc_loop_index = 0;
	int lc_loops_this_second = 0;

void lc_process()
{
	lc_loops_this_second++;
	unsigned long current_time = millis();
	if (current_time - lc_last_time > 1000)
	{
		//store loops
		lc_loops_per_sec[lc_loop_index++] = lc_loops_this_second;
		lc_loops_this_second = 0;
		lc_last_time = current_time;
		if (lc_loop_index == LC_LOOPS_TO_AVG) lc_loop_index = 0;

		int total_loops = 0;
		for (int i = 0; i < LC_LOOPS_TO_AVG; i++)
			total_loops += lc_loops_per_sec[i];

		lc_avg_loops_per_second = static_cast<float>(total_loops) / LC_LOOPS_TO_AVG;
		DBG_PRINT("Loops per second: ");
		DBG_PRINTLN(lc_avg_loops_per_second);
	}
}

void func_decl()
{
		digitalWrite(7, HIGH);
		delay(100);
		digitalWrite(7, LOW);
		delay(100);
}

