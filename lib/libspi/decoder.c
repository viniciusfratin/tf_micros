#include <string.h>
#include <spi.h>

#include <decoder.h>

void decoder_init()
{
	char wr_data[2] = { WRITE_MDR0, QUADRX1 };
	char rd_data[2];
	spi_transfer((uint8_t*)wr_data, (uint8_t*)rd_data);
}

void decoder_read_counter(char* buf)
{
	char wr_data[1] = { READ_CNTR };
	char rd_data[4];
	spi_transfer((uint8_t*)wr_data, (uint8_t*)rd_data);
	
	memcpy(buf, rd_data, sizeof rd_data);
}

void decoder_clear_counter()
{
	char wr_data[1] = { CLR_CNTR };
	char rd_data[1];
	spi_transfer((uint8_t*)wr_data, (uint8_t*)rd_data);
}
