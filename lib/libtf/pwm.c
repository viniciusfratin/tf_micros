#include <stdio.h>

#include <pwm.h>
#include <galileo2io.h>

int pwm_set_period(const int period)
{
	char period_str[32];
	snprintf(period_str, sizeof period_str, "%d", period);

	return pputs("/sys/class/pwm/pwmchip0/device/pwm_period", period_str);
}

int pwm_set_duty_cycle(const int duty_cycle)
{
	char duty_cycle_str[32];
	snprintf(duty_cycle_str, sizeof duty_cycle_str, "%d", duty_cycle);

	return pputs("/sys/class/pwm/pwmchip0/pwm1/duty_cycle", duty_cycle_str);
}

int pwm_start()
{
	return pputs("/sys/class/pwm/pwmchip0/pwm1/enable","1");
}

int pwm_stop()
{
	return pputs("/sys/class/pwm/pwmchip0/pwm1/enable","0");
}
