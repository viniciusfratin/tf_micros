#include <fcntl.h>
#include <unistd.h>
#include <spislave.h>

/*
  Use IO10 as #SS
	gpio10 = #SS
	gpio26=1
	gpio27=1
	gpio74=0
*/

SsSlave::SsSlave(void)
{
	fd=open("/sys/class/gpio/gpio10/value",O_RDONLY);
}

SsSlave::~SsSlave(void)
{
	close(fd);
}

int SsSlave::selected(void)
{
	char ss_;

	lseek(fd,0,SEEK_SET);
	read(fd,&ss_,sizeof(ss_));

	return (ss_ == '0');
}

/*
  Use IO13 as SCLK
	gpio7 = SCLK (input)
	gpio30=1 (IO13 is input)
	gpio31=0 (pull-down)
*/

SclkSlave::SclkSlave(void)
{
	fd=open("/sys/class/gpio/gpio7/value",O_RDONLY);
}

SclkSlave::~SclkSlave(void)
{
	close(fd);
}

void SclkSlave::waitRise(void)
{
	char sclk;

	do
	{
		lseek(fd,0,SEEK_SET);
		read(fd,&sclk,sizeof(sclk));
	} while(sclk != '0');

	do
	{
		lseek(fd,0,SEEK_SET);
		read(fd,&sclk,sizeof(sclk));
	} while(sclk == '0');
}

/*
  Use IO11 as MOSI
	gpio5 = MOSI (input)
	gpio24=1 (IO11 is input)
	gpio25=1 (pull-up)
	gpio44=0 (IO11 is GPIO)
*/

MosiSlave::MosiSlave(void)
{
	fd=open("/sys/class/gpio/gpio5/value",O_RDWR);
}

MosiSlave::~MosiSlave(void)
{
	close(fd);
}

int MosiSlave::sample(void)
{
	char mosi;

	lseek(fd,0,SEEK_SET);
	read(fd,&mosi,sizeof(mosi));

	return (mosi != '0');
}

/*
  Use IO12 as MISO
	gpio15 = MISO (output)
	gpio42=0 (IO12 is output)
	gpio43=1  
*/

MisoSlave::MisoSlave(void)
{
	fd=open("/sys/class/gpio/gpio15/value",O_RDWR);
}

MisoSlave::~MisoSlave(void)
{
	close(fd);
}

int MisoSlave::sample(void)
{
	char mosi;

	lseek(fd,0,SEEK_SET);
	read(fd,&miso,sizeof(miso));

	return (miso != '0');
}
