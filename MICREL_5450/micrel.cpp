//
//  micrel.cpp
//  
//
//  Created by Ethan Dahlke on 5/16/14.
//
//

#include "micrel.h"

#define REG

Display_Comm::Display_Comm(){
    
}

char * Display_Comm::Read(Cube_4x4 *data){
    while(Serial.available()){
        //        digitalWrite(13, HIGH);
        Serial.readBytes(&buffer,1);
        //    Serial.println(buffer,HEX);
        
        Layer *layer_ptr = &((*data).a);
        
        layer_ptr+=(buffer & 0x3);          //Select layer
        pixel_ptr = &layer_ptr->a;
        pixel_ptr+=(buffer>>2 & 0x3);       //Select row
//        pixel=(buffer>>4 & 0x3);            //Select pixel
    }
    return pixel_ptr;
}

void Display_Comm::  Display(char *pixel_ptr){
    pixel=(buffer>>4 & 0x3);            //Select pixel
    if(buffer>>5 & 0x1)
        *pixel_ptr |= (0x1<<pixel);       //Turn pixel on
    else
        *pixel_ptr &= ~(0x1<<pixel);      //Turn pixel off
}

Micrel::Micrel()
{
    pinMode(DATA, OUTPUT);
    pinMode(CLK, OUTPUT);
    pinMode(ENABLE, OUTPUT);
}

void Micrel::pulseClock()
{
#ifndef REG
    digitalWrite(CLK,HIGH);
#endif
#ifdef REG
    PORTD |= 0x8;
    //    delay(1);
        delayMicroseconds(5);
#endif
//    DELAY(10);
#ifndef REG
    digitalWrite(CLK,LOW);
#endif
#ifdef REG
    PORTD &= ~0x8;
#endif
}

void Micrel::enable()
{
#ifndef REG
    digitalWrite(ENABLE,LOW);
#endif
#ifdef REG
    PORTD &= ~0x10;
#endif
}

void Micrel::disable()
{
#ifndef REG
    digitalWrite(ENABLE,HIGH);
#endif
#ifdef REG
    PORTD |= 0x10;
#endif
}

void Micrel::pinWrite(unsigned int bit, unsigned short int val)
{
    if(val){
#ifndef REG
        digitalWrite(bit,HIGH);
#endif
#ifdef REG
        PORTD |= 0x4;
#endif
    }
    else
        
#ifndef REG
        digitalWrite(bit,LOW);
#endif
#ifdef REG
        PORTD &= ~0x4;
#endif

}

void Micrel::shiftOut(Cube_4x4 *data)
{
    shiftOut_mult(data, 0x1);
    //    char i;
    //    enable();
    //    pinWrite(DATA,1);
    //    pulseClock();
    //
    //    for(i=0; i<BAR_SEG; i++)
    //    {
    //        pinWrite(DATA, data->a & (1<<i));
    //        pulseClock();
    //    }
    //
    //    for(i=0; i<BAR_SEG; i++)
    //    {
    //        pinWrite(DATA, data->b & (1<<i));
    //        pulseClock();
    //    }
    //
    //    for(i=0; i<BAR_SEG; i++)
    //    {
    //        pinWrite(DATA, data->c & (1<<i));
    //        pulseClock();
    //    }
    //
    //    for(i=0; i<(35-BAR_SEG*3); i++)
    //    {
    //        pinWrite(DATA, 0);
    //        pulseClock();
    //    }
}

void Micrel::shiftOut_mult(Cube_4x4 *data, int sel)
{
//    cli();
    char i,j;
    String_36 string;
    Layer *layer_ptr= &(data->a);
    
        for(j=0; j<CUBE; j++){
            string = layer_combine(layer_ptr);
            switch(j){
                case 0:
                    string.Low |= 0x10000;
                    break;
                case 1:
                    string.Low |= 0x20000;
                    break;
                case 2:
                    string.Low |= 0x40000;
                    break;
                case 3:
                    string.Low |= 0x80000;
                    break;
            }
//            string.Low = 0x0;
//            string.Low |= 0x1f99f;
            string.High = 0x0;
//            cli();
            enable();
            pinWrite(DATA,1);
            pulseClock();
            
            for(i=0; i<32; i++)
            {
                pinWrite(DATA, ((string.Low>>i) & 0x1));
                pulseClock();
            }

            for(i=0; i<3; i++){
                pinWrite(DATA, ((string.High) & (0x1<<i)));
                pulseClock();
            }
            disable();
            enable();
            pinWrite(DATA, 1);
            pulseClock();
            for(i=0; i<35; i++)
            {
                pinWrite(DATA, 0);
                pulseClock();
            }
            disable();
            layer_ptr++;
        }
//    sei();
}

void Micrel::Clear(Layer *layer_ptr)
{
    int i;
    for (i=0; i<CUBE; i++){
        layer_ptr->a = 0x0;
        layer_ptr->b = 0x0;
        layer_ptr->c = 0x0;
        layer_ptr->d = 0x0;
        layer_ptr++;
    }
}

void Micrel::DELAY(unsigned long ms)
{
    unsigned long i = millis();
    //    digitalWrite(6, HIGH);
    //    while((millis()-i) < ms);
    //       while(i<100000)
    //    i++;
    //    digitalWrite(6, HIGH);
    //        delay(1);
    delayMicroseconds(ms);
}

String_36 Micrel::layer_combine(Layer *layer)
{
    String_36 string;
    string.Low = 0x0;
    string.High = 0x0;
    string.Low = (layer->a);
    string.Low |= (layer->b)<<CUBE;
    string.Low |= (layer->c)<<(CUBE*2);
    string.Low |= (layer->d)<<(CUBE*3);
    string.Low &= 0x0000ffff;
    return string;
}

void Micrel::layer_split(String_36 *string, Layer *layer)
{
    layer->a = (string->Low) & 0x000f;
    layer->b = (string->Low)>>4 & 0xf;
    layer->c = (string->Low)>>8 & 0xf;
    layer->d = (string->Low)>>12 & 0xf;
}

