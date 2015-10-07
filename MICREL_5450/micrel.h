//
//  micrel.h
//  
//
//  Created by Ethan Dahlke on 5/16/14.
//
//

#ifndef ____micrel__
#define ____micrel__

#include "Arduino.h"
#include <stdint.h>

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

#define DATA 2
#define CLK 3
#define ENABLE 4

#define CUBE 4

typedef struct Layer {
    char a;
    char b;
    char c;
    char d;
//    char e;
//    char f;
//    char g;
//    char h;
} Layer;

typedef struct Cube_4x4{
    Layer a;
    Layer b;
    Layer c;
    Layer d;
}Cube_4x4;

//Cube_4x4 Box_4x4;

typedef struct Cube_8x8{
    Layer a;
    Layer b;
    Layer c;
    Layer d;
    Layer e;
    Layer f;
    Layer g;
    Layer h;
}Cube_8x8;

typedef struct String_36{
    unsigned long Low;
    uint8_t High;
}String_36;

class Micrel
{
public:
    Micrel();
    void shiftOut(Cube_4x4 *data);
    void pulseClock();
    void enable();
    void disable();
    void pinWrite(unsigned int, unsigned short int);
    void shiftOut_mult(Cube_4x4 *data, int sel);
    void Clear(Layer *layer_ptr);
    void DELAY(unsigned long ms);
    String_36 layer_combine(Layer *layer);
    void layer_split(String_36 *string, Layer *layer);
};

class Display_Comm
{
    char buffer;
    char *pixel_ptr;
    char pixel;
private:
//    int address;
//    char status;
    
public:
    Display_Comm();
    char *Read(Cube_4x4 *data);
    void Display(char *pixel);
};



#endif /* defined(____micrel__) */
