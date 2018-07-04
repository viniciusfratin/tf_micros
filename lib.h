// Trabalho Prático Microcontroladores
// Luciano Zancan - Rodrigo Dal Ri - Vinicius Fratin

#ifndef lib
#define lib

typedef struct sHandles handles;

handles *initialize(void);
void setMotorVoltage(double voltage);
void setPWMPeriod(int period);
int readDecoder(handles *h);
int readLimitSwitches(handles *h, int num);

#endif
