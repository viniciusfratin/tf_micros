// Trabalho Prático Microcontroladores
// Luciano Zancan - Rodrigo Dal Ri - Vinicius Fratin

#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

double pid(double *P_error, double *I_error, double *D_error, double *error, double *prevError, double setPoint, double processValue) {
    *prevError = *error;
    *error = setPoint - processValue;

    *P_error = *error;
    *I_error += *prevError;
    *D_error = *error - *prevError;


    return 0.1 * *P_error + 0.3 * *I_error + 0.02 * *D_error;
}

void main(void)
{
  // erro anterior
  double prevError = 0;
  // erro atual
  double error = 0;
  // erro proporcional
  double P_error = 0;
  // erro
  double I_error = 0;
  // erro derivativo
  double D_error = 0;
  // valor lido dos encoders
  int processValue = 0;
  // nova voltagem
  int newVoltage = 0;
  // receber o setPoint (sendo 180º (PI rad) da posição inicial)
  double setPoint = 4096.0/2.0;

  handles *h = initialize();

  setMotorVoltage(10);

  while(readLimitSwitches(h, 1) == 1 && readLimitSwitches(h, 2) == 1){
  }

  setMotorVoltage(0);

  while(1){
    processValue = readDecoder(h);
  	newVoltage = pid(&P_error, &I_error, &D_error, &error, &prevError, setPoint, processValue);

    if (newVoltage > 27)
  		newVoltage = 27;
  	else
  	if (newVoltage < -27)
  		newVoltage = -27;

    if(readLimitSwitches(h, 1) == 0 || readLimitSwitches(h, 2) == 0)
      setMotorVoltage(0);
  }


}
