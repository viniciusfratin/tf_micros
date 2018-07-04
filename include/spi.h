#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

void pabort(const char *s);
int spi_init();
int spi_finalize();
void transfer(int fd, uint8_t *tx, uint8_t *rx);
void spi_transfer(uint8_t *tx, uint8_t *rx);
void spi_stat();

#endif
