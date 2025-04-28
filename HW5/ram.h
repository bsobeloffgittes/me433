#ifndef RAM_H_
#define RAM_H_

#include <math.h>
#include "spi.h"

#define READ_RAM        0x03
#define WRITE_RAM       0x02
#define READ_RAM_SR     0x05
#define WRITE_RAM_SR    0x01
#define RAM_BYTE_INIT   0x00
#define RAM_SEQ_INIT    0x40

void spi_ram_init(void);

void pack_sin_wave(void);

void begin_ram_write(uint16_t addr);
void read_ram_bytes(uint16_t addr, uint8_t len, uint8_t* dst_buf);

void pack_addr_buf(uint16_t addr, uint8_t* buf);

#endif