#include <stdio.h>
#include <stdlib.h>
#include <spi.h>
#include <decoder.h>
#include <pwm.h>
#include <motor.h>
#include <unistd.h>

#define TIME_STEP 10000
#define PWM_PERIOD 1500000

int main(int argc, char* argv[])
{
	double angular_position = 0;
	double reference_angular_position;
	double count_angle_constant = 1e-3;
	double p_gain, i_gain, d_gain;

	if(argc != 5 || argc != 6)
	{
		fprintf(stderr, "Usage: ./pid <reference_angular_position> <p_gain> <i_gain> <d_gain> [<count_angle_constant>]");
		exit(1);
	}

	else
	{
		sscanf(argv[1], "%lf", &reference_angular_position);
		sscanf(argv[2], "%lf", &p_gain);
		sscanf(argv[3], "%lf", &i_gain);
		sscanf(argv[4], "%lf", &d_gain);
	 	
		if(argc == 6)
		{
			sscanf(argv[5], "%lf", &count_angle_constant);
		}
	}
	

	spi_init();
	decoder_init();	
	pwm_start();
	pwm_set_period(PWM_PERIOD);

	double integral = 0, derivative;
	
	int last_count = decoder_read_counter();
	double last_error = 0;

	while(1)
	{
		usleep(TIME_STEP);

		int current_count = decoder_read_counter();
		int delta_count = current_count - last_count;

		angular_position += count_angle_constant * delta_count;
		
		double error = reference_angular_position - angular_position;
		integral += error * TIME_STEP;
		derivative = (error - last_error)/TIME_STEP;

		double relative_speed = p_gain * error + i_gain * integral + d_gain * derivative;
		motor_set_relative_speed(relative_speed, PWM_PERIOD);
		printf("New relative speed: %lf\n", relative_speed);

		last_count = current_count;
		last_error = error;
	}

	spi_finalize();
}
