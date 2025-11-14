#ifndef WIC64LIB_H
#define WIC64LIB_H

#include <stdint.h>

/* CIA2 addresses (decimal):
   $DD00=56576, $DD01=56577, $DD02=56578, $DD03=56579, $DD0D=56589 */
#define PRA     (*(volatile uint8_t*)56576)
#define PRB     (*(volatile uint8_t*)56577)
#define DDRA    (*(volatile uint8_t*)56578)
#define DDRB    (*(volatile uint8_t*)56579)
#define ICR     (*(volatile uint8_t*)56589)

/* Assembly routines */
uint8_t __fastcall__ setbyte(uint8_t value);
uint8_t readbyte(void);
void wic_port_send_setup(void);
void wic_port_recv_setup(void);
void wic_irq_clear(void);
void wic_cli(void);

/* Helpers */
uint8_t lowhighbyte(uint8_t lorh, uint16_t value);

/* Memory helpers (visible to other modules) */
uint8_t peek(uint16_t addr);
void poke(uint16_t addr, uint8_t v);
uint16_t deek(uint16_t addr);

/* Main command function */
uint16_t wic_com(uint8_t com,
                 uint16_t parastart, uint16_t paralength,
                 uint16_t datastart, uint16_t datalength,
                 uint16_t target);

#endif

