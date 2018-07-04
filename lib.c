// Trabalho Prático Microcontroladores
// Luciano Zancan - Rodrigo Dal Ri - Vinicius Fratin

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib.h"

/*
	IO3  - input  -
	IO4  - output -
	IO10 - input  - SS (Slave Select)
  IO11 - input  - MOSI
  IO12 - output - MISO
  1O13 - input  - SClK
*/

/** Frequência máxima da galileo*/
#define GALILEOFREQ 1500
/** Voltagem máxima (27V) */
#define MOTORVOLTAGE 27
/** Número máximo de ranhuras*/
#define NUMBEROFMARKS 4096

//Estrutura utilizada para ler os bits do contador e os sensores de fim de curso
struct sHandles
{
	FILE *fileBit[16];
	FILE *fileLim1;
	FILE *fileLim2;
};

static void setPWMDutyCycle(int dutyCycle);

//Seta a ciclo de trabalho do PWM
static void setPWMDutyCycle(int dutyCycle)
{
    char tempStringDutyCycle[100];
    sprintf(tempStringDutyCycle, "echo %d > /sys/class/pwm/pwmchip0/pwm1/duty_cycle", dutyCycle);
    system(tempStringDutyCycle);
}

// Seta a voltagem do motor
void setMotorVoltage(double voltage)
{
  double period = 1.0/GALILEOFREQ * 1000000000;

	int cycle = (int)(voltage/MOTORVOLTAGE * 0.5 * period + 0.5 * period);

	if(cycle > period*0.9)
        cycle = period * 0.9;

	setPWMDutyCycle(cycle);
}

//Seta o período do PWM
void setPWMPeriod(int period)
{
    char tempStringPeriod[100];
    sprintf(tempStringPeriod, "echo %d > /sys/class/pwm/pwmchip0/device/pwm_period", period);
    system(tempStringPeriod);
}

//Lê o decoder
int readDecoder(handles* h)
{


}

//Lê os valores de fim de curso
int readLimitSwitches(handles *h, int num)
{


}
