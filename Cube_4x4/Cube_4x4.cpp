//
//  4x4_cube.cpp
//  Cube Test
//
//  Created by Ethan Dahlke on 6/13/14.
//  Copyright (c) 2014 Ethan Dahlke. All rights reserved.
//

#include "Cube_4x4.h"

Cube_Effect::Cube_Effect()
{
    char i,j,k;
    Cube_pixels[0][0][0]=0x1;
    Cube_pixels[0][0][1]=0x2;
    Cube_pixels[0][0][2]=0x4;
    Cube_pixels[0][0][3]=0x8;
    
    Cube_pixels[0][1][0]=0x10;
    Cube_pixels[0][1][1]=0x20;
    Cube_pixels[0][1][2]=0x40;
    Cube_pixels[0][1][3]=0x80;
    
    Cube_pixels[0][2][0]=0x100;
    Cube_pixels[0][2][1]=0x200;
    Cube_pixels[0][2][2]=0x400;
    Cube_pixels[0][2][3]=0x800;
    
    Cube_pixels[0][3][0]=0x1000;
    Cube_pixels[0][3][1]=0x2000;
    Cube_pixels[0][3][2]=0x4000;
    Cube_pixels[0][3][3]=0x8000;
    
    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
            for(k=0; k<4; k++)
                Cube_pixels[i][j][k] |= (0x10000<<i);
}

void Cube_Effect::Snake(Cube_4x4 *data, Micrel *a){
    char i,j,k;
//    for
}

void blah(int *x, int *y, int *z)
{
    
}

void Cube_Effect::single_scan(Cube_4x4 *data, Micrel *a)
{
//    cli();
    int i,j;
    a->Clear(&(data->a));
    String_36 string;
    Layer *layer_ptr = &(data->a);
    string.High = 0x0;
    for(j=0; j<CUBE; j++)
    {
        for(i=0; i<16; i++){
            cli();
            string.Low = 0x3 << i;
            string.Low &= 0x0000ffff;
            a->layer_split(&string, layer_ptr);
            sei();
            delay(100);
        }
        layer_ptr->d = 0;
        layer_ptr++;
    }
//    sei();
}

void Cube_Effect::Box(Cube_4x4 *data)
{
    cli();
    data->a.a = 0xf;
    data->a.b = 0x9;
    data->a.c = 0x9;
    data->a.d = 0xf;
    data->b.a = 0x9;
    data->b.b = 0x0;
    data->b.c = 0x0;
    data->b.d = 0x9;
    data->c.a = 0x9;
    data->c.b = 0x0;
    data->c.c = 0x0;
    data->c.d = 0x9;
    data->d.a = 0xf;
    data->d.b = 0x9;
    data->d.c = 0x9;
    data->d.d = 0xf;
    sei();
    
}

void Cube_Effect::Full(Cube_4x4 *data)
{
    cli();
    data->a.a = 0xf;
    data->a.b = 0xf;
    data->a.c = 0xf;
    data->a.d = 0xf;
    data->b.a = 0xf;
    data->b.b = 0xf;
    data->b.c = 0xf;
    data->b.d = 0xf;
    data->c.a = 0xf;
    data->c.b = 0xf;
    data->c.c = 0xf;
    data->c.d = 0xf;
    data->d.a = 0xf;
    data->d.b = 0xf;
    data->d.c = 0xf;
    data->d.d = 0xf;
    sei();
}
