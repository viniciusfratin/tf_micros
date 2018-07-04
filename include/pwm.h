#ifndef PWM_H_
#define PWM_H_

int pwm_set_period(const int period);
int pwm_set_duty_cycle(const int duty_cycle);
int pwm_start();
int pwm_stop();

#endif
