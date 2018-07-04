#include <pwm.h>
#include <motor.h>

void motor_set_relative_speed(const double relative_speed, const int period)
{
	int duty_cycle = (relative_speed + 1) * period / 2;
	pwm_set_duty_cycle(duty_cycle);
}
