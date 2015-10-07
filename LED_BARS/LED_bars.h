/*
 * LED_bars.h
 *
 *  Created on: Jan 20, 2014
 *      Author: Ethan Dahlke
 */

#ifndef LED_BARS_H_
#define LED_BARS_H_

#include "Arduino.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <math.h>
//#include <string.h>
//#include <kiss_fft.h>
//#include <_kiss_fft_guts.h>

//Define our pins
//#define DATA BIT2 // DS -> 1.2
//#define CLOCK BIT5 // SH_CP -> 1.5
//#define ENABLE BIT0 // OE -> 1.0

#define MAX_DATA 0x3fffffff
#define MAX_DATA_2 0x2fffffffffffffffff
#define MAX_BIT 0x20000000
#define MAX_BAR_DATA 0x3ff
#define MAX_BAR_BIT 0x200
#define BAR_SEG 10
#define NFFT 64

#define NUM_0 0x0
#define NUM_1 0x1
#define NUM_2 0x3
#define NUM_3 0x7
#define NUM_4 0xf
#define NUM_5 0x1f
#define NUM_6 0x3f
#define NUM_7 0x7f
#define NUM_8 0xff
#define NUM_9 0x1ff
#define NUM_10 0x3ff

#define BAR0 0x0;
#define BAR1 0x1;
#define BAR2 0x2;
#define BAR3 0x4;
#define BAR4 0x8;
#define BAR5 0x10;
#define BAR6 0x20;
#define BAR7 0x40;
#define BAR8 0x80;
#define BAR9 0x100;
#define BAR10 0x200;
#define BAR11 0x400;
#define BAR12 0x800;
#define BAR13 0x1000;
#define BAR14 0x2000;
#define BAR15 0x4000;
#define BAR16 0x8000;
#define BAR17 0x10000;
#define BAR18 0x20000;
#define BAR19 0x40000;
#define BAR20 0x80000;
#define BAR21 0x100000;
#define BAR22 0x200000;
#define BAR23 0x400000;
#define BAR24 0x800000;
#define BAR25 0x1000000;
#define BAR26 0x2000000;
#define BAR27 0x4000000;
#define BAR28 0x8000000;
#define BAR29 0x10000000;
#define BAR30 0x20000000;
#define BAR31 0x40000000;
#define BAR32 0x80000000;
#define BAR33 0x100000000;
#define BAR34 0x200000000;
#define BAR35 0x400000000;

/************************************************************
 * STANDARD BITS
 ************************************************************/

#define BIT0                   (0x0001)
#define BIT1                   (0x0002)
#define BIT2                   (0x0004)
#define BIT3                   (0x0008)
#define BIT4                   (0x0010)
#define BIT5                   (0x0020)
#define BIT6                   (0x0040)
#define BIT7                   (0x0080)
#define BIT8                   (0x0100)
#define BIT9                   (0x0200)
#define BITA                   (0x0400)
#define BITB                   (0x0800)
#define BITC                   (0x1000)
#define BITD                   (0x2000)
#define BITE                   (0x4000)
#define BITF                   (0x8000)

#define FFT_size 4;

typedef struct Data{
	unsigned short int a;
	unsigned short int b;
	unsigned short int c;
	unsigned short int d;
	unsigned short int e;
    unsigned short int f;
} Data;

#define DATA 2
#define CLK 3
#define ENABLE 4

class Micrel
{
public:
    Micrel();
    void shiftOut(volatile Data *data);
    void pulseClock();
    void enable();
    void disable();
    void pinWrite(unsigned int, unsigned short int);
    void shiftOut_mult(volatile Data *data, int sel);
    void Clear();
    void DELAY(unsigned long ms);
};

class Effects
{
public:
    Effects();
    void scan(volatile Data *data, int speed, Micrel *a);
    void ping_pong(volatile Data *data, int speed, Micrel *a);
    void scan_spread(volatile Data *data, int speed, Micrel *a);
    void horz_fill(volatile Data *data, int speed, Micrel *a);
    void ping_pong_inv(volatile Data *data, int speed, Micrel *a);
    void DELAY(unsigned long ms);
};

class PID
{
public:
    PID();
    void shift(volatile Data *over_time);
};
//void ADC10(Data *data,kiss_fft_cpx*, kiss_fft_cpx*);
//void pulseClock ( void );
//void shiftOut (Data *val);
//void enable ( void );
//void disable ( void );
//void shiftOut_long(long long int *val);
//void scan(Data *data);
//void ping_pong(Data *data);
//void pinWrite( unsigned int bit, unsigned short int val );
//void scan_spread(Data *data);
//void horz_fill(Data *data);
//void clear(Data *data);
//void delay(unsigned int);
//void FFT(int nfft, kiss_fft_cpx *fft_in, kiss_fft_cpx *fft_out, Data *data);
//void bounce(Data *data);
//int map(int *value, int value_max, int value_min, int max, int min);
int level(int value);


#endif /* LED_BARS_H_ */
