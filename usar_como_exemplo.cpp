/*
  spi_slave_rx.c: Receives a string using an SPI bus implemented in software.

*/

#include <iostream>

#include <spislave.h>

int main(int argc,char *argv[])
{
	SclkSlave sclk;
	MosiSlave mosi;
	SsSlave ss;

#ifdef DEBUG
	std::cerr << "Waiting to be selected...";
	std::cerr.flush();
#endif

	while(!ss.selected());

#ifdef DEBUG
	std::cerr << "selected." << std::endl;
#endif

	while(ss.selected())
	{
		char c=0;
		for(int i=0;i < 8;i++)
		{
#ifdef DEBUG
			std::cerr << "Waiting clock rise...";
			std::cerr.flush();
#endif
			sclk.waitRise();
#ifdef DEBUG
			std::cerr << "rose...";
			std::cerr.flush();
#endif

			c=(c << 1) | mosi.sample(); // Assume MSBit first

#ifdef DEBUG
			std::cerr << "sampled." << std::endl;
#endif

			if(!ss.selected()) break;
		}
		std::cout << c;
		std::cout.flush();
	}

#ifdef DEBUG
	std::cerr << "Deselected." << std::endl;
#endif

	return 0;
}
