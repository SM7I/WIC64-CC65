#include "wic64lib.h"
#include <conio.h>
#include <stdio.h>

/* Helpers */
uint8_t lowhighbyte(uint8_t lorh, uint16_t value) {
    uint8_t high = (uint8_t)(value >> 8);
    uint8_t low  = (uint8_t)(value & 0xFF);
    if (lorh == 1) return low;
    if (lorh == 2) return high;
    return 0;
}

/* Memory helpers */
uint8_t peek(uint16_t addr) {
    return *(volatile uint8_t*)addr;
}
void poke(uint16_t addr, uint8_t v) {
    *(volatile uint8_t*)addr = v;
}
uint16_t deek(uint16_t addr) {
    uint8_t lo = peek(addr);
    uint8_t hi = peek((uint16_t)(addr+1));
    return ((uint16_t)hi << 8) | lo;
}

/* Core command exchange */
uint16_t wic_com(uint8_t com,
                 uint16_t parastart, uint16_t paralength,
                 uint16_t datastart, uint16_t datalength,
                 uint16_t target)
{
    uint8_t b, low, high;
    uint16_t sum, sumDMI, lop1;

    wic_port_send_setup();

    setbyte(82);
    setbyte(com);
    setbyte(lowhighbyte(1, paralength));
    setbyte(lowhighbyte(2, paralength));

    parastart++;
    if (paralength > 0) {
        uint8_t sign;
        do {
            sign = peek(parastart);
            if (sign >= 65 && sign <= 90)  sign = (uint8_t)(sign + 32);
            if (sign >= 193 && sign <= 218) sign = (uint8_t)(sign - 128);
            setbyte(sign);
            paralength--;
            parastart++;
        } while (paralength != 0);
    }

    if (datalength > 0 && com == 40) {
        wic_port_recv_setup();
        b = readbyte(); b = readbyte(); b = readbyte();
        wic_port_send_setup();
        setbyte(82);
        setbyte(43);
        setbyte(lowhighbyte(1, datalength));
        setbyte(lowhighbyte(2, datalength));
        while (datalength != 0) {
            setbyte(peek(datastart));
            datastart++;
            datalength--;
        }
    }

    wic_port_recv_setup();
    if (com == 40) wic_irq_clear();

    b = readbyte(); b = readbyte();
    low  = readbyte();
    high = readbyte();
    sum = ((uint16_t)high << 8) | low;
    lop1 = 0;

    if (target == (uint16_t)0) {
        poke((uint16_t)43, readbyte());
        poke((uint16_t)44, readbyte());
        target = deek((uint16_t)43);
        lop1 = (uint16_t)2;
    }

    if (target != (uint16_t)0xFFFF) {
        while (lop1 != sum) {
            while ((ICR & (uint8_t)16) == 0) { }
            poke(target, PRB);
            target++;
            lop1++;
        }
    } else {
        while (sum > (uint16_t)0) {
            poke((uint16_t)829, readbyte());
            poke((uint16_t)828, readbyte());
            target = deek((uint16_t)828);

            poke((uint16_t)829, readbyte());
            poke((uint16_t)828, readbyte());
            sumDMI = deek((uint16_t)828);
            sum -= (uint16_t)4;

            for (lop1 = (uint16_t)1; lop1 <= sumDMI; ++lop1) {
                poke(target, readbyte());
                target++;
            }
            sum -= sumDMI;
        }
        sum = (uint16_t)1;
    }

    wic_cli();
    return sum;
}

