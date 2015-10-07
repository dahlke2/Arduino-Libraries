//
//  LED_BARS.cpp
//  
//
//  Created by Ethan Dahlke on 1/31/14.
//
//

#include "LED_BARS.h"

PID::PID()
{
    
}

void PID::shift(volatile Data *over_time)
{
    int i;
    for(i=19; i>0; i--)
    {
        over_time[i].a=over_time[i-1].a;
        over_time[i].b=over_time[i-1].b;
        over_time[i].c=over_time[i-1].c;
        over_time[i].d=over_time[i-1].d;
        over_time[i].e=over_time[i-1].e;
        over_time[i].f=over_time[i-1].f;
    }
}

Micrel::Micrel()
{
    pinMode(DATA, OUTPUT);
    pinMode(CLK, OUTPUT);
    pinMode(ENABLE, OUTPUT);
}

void Micrel::pulseClock()
{
    digitalWrite(CLK,HIGH);
//    delay(1);
//    delayMicroseconds(10);
    DELAY(10);
    digitalWrite(CLK,LOW);
}

void Micrel::enable()
{
    digitalWrite(ENABLE,LOW);
}

void Micrel::disable()
{
    digitalWrite(ENABLE,HIGH);
}

void Micrel::pinWrite(unsigned int bit, unsigned short int val)
{
    if(val)
        digitalWrite(bit,HIGH);
    else
        digitalWrite(bit,LOW);
}

void Micrel::shiftOut(volatile Data *data)
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

void Micrel::shiftOut_mult(volatile Data *data, int sel)
{
    char i;
    enable();
    pinWrite(DATA,1);
    pulseClock();
    
    if(sel==0x1){
        for(i=0; i<BAR_SEG; i++)
        {
            pinWrite(DATA, data->a & (1<<i));
            pulseClock();
        }
        for(i; (9-i)>0;i++)
            pulseClock();
        for(i=0; i<BAR_SEG; i++)
        {
            pinWrite(DATA, data->b & (1<<i));
            pulseClock();
        }
        for(i; (9-i)>0;i++)
            pulseClock();
        for(i=0; i<BAR_SEG; i++)
        {
            pinWrite(DATA, data->c & (1<<i));
            pulseClock();
        }
        for(i; (9-i)>0;i++)
            pulseClock();
    }
    if(sel==0x2){
        for(i=0; i<BAR_SEG; i++)
        {
            pinWrite(DATA, data->d & (1<<i));
            pulseClock();
        }
        for(i; (9-i)>0;i++)
            pulseClock();
        for(i=0; i<BAR_SEG; i++)
        {
            pinWrite(DATA, data->e & (1<<i));
            pulseClock();
        }
        for(i; (9-i)>0;i++)
            pulseClock();
        for(i=0; i<BAR_SEG; i++)
        {
            pinWrite(DATA, data->f & (1<<i));
            pulseClock();
        }
        for(i; (9-i)>0;i++)
            pulseClock();
    }
    for(i=0; i<(35-BAR_SEG*3); i++)
    {
        pinWrite(DATA, sel & (1<<i));
        pulseClock();
    }
    disable();
}

void Micrel::Clear()
{
    int i;
    enable();
    pinWrite(DATA, 1);
    pulseClock();
    for(i=0; i<35; i++)
    {
        pinWrite(DATA, 0);
        pulseClock();
    }
    disable();
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

Effects::Effects()
{

}

void Effects::scan(volatile Data *data, int speed, Micrel *a)
{
    long long int LED_data;
//    Micrel a;
    for(LED_data = 0x0; LED_data <= MAX_BAR_DATA; LED_data = (2*LED_data+1)){
        cli();
        data->a = LED_data;
        data->b = LED_data;
		data->c = LED_data;
        data->d = LED_data;
        data->e = LED_data;
        data->f = LED_data;
        sei();
        delay(speed);
    }
    for(LED_data = MAX_BAR_DATA; LED_data>=0x1; LED_data=(LED_data/2)){
		cli();
        data->a = LED_data;
		data->b = LED_data;
		data->c = LED_data;
        data->d = LED_data;
        data->e = LED_data;
        data->f = LED_data;
        
        sei();
        delay(speed);
    }
}

void Effects::ping_pong(volatile Data *data, int speed, Micrel *a)
{
    long long int LED_data;
	for(LED_data = 0x1; LED_data<=MAX_BAR_BIT; LED_data=2*LED_data){
        cli();
		data->a = LED_data;
		data->b = LED_data;
		data->c = LED_data;
        data->d = LED_data;
        data->e = LED_data;
        data->f = LED_data;
        sei();
        delay(speed);
    }
    delay(5);
	for(LED_data = MAX_BAR_BIT; LED_data>=0x1; LED_data=(LED_data/2)){
        cli();
		data->a = LED_data;
		data->b = LED_data;
		data->c = LED_data;
        data->d = LED_data;
        data->e = LED_data;
        data->f = LED_data;
        sei();
        delay(speed);
    }
    delay(5);
}
void Effects::ping_pong_inv(volatile Data *data, int speed, Micrel *a)
{
    long long int LED_data;
	for(LED_data = 0x1; LED_data<=MAX_BAR_BIT; LED_data=2*LED_data){
        cli();
		data->a = ~LED_data;
		data->b = ~LED_data;
		data->c = ~LED_data;
        data->d = ~LED_data;
        data->e = ~LED_data;
        data->f = ~LED_data;
        sei();
        delay(speed);
    }
    delay(5);
	for(LED_data = MAX_BAR_BIT; LED_data>=0x1; LED_data=(LED_data/2)){
        cli();
		data->a = ~LED_data;
		data->b = ~LED_data;
		data->c = ~LED_data;
        data->d = ~LED_data;
        data->e = ~LED_data;
        data->f = ~LED_data;
        sei();
        delay(speed);
    }
    delay(5);
}

void Effects::scan_spread(volatile Data *data, int speed, Micrel *a)
{
    long long int LED_data;
	for(LED_data = 0x0; LED_data<=MAX_DATA; LED_data=(2*LED_data+1)){
        cli();
		data->a = LED_data & (MAX_BAR_DATA);
		data->b = (LED_data >> 10) & MAX_BAR_DATA;
		data->c = (LED_data >> 20) & MAX_BAR_DATA;
        data->d = (LED_data) & 0x0;
        data->e = LED_data & 0x0;
        data->f = LED_data & 0x0;
        sei();
        delay(speed);
    }
    for(LED_data = 0x0; LED_data<=MAX_DATA; LED_data=(2*LED_data+1)){
        cli();
//		data->a = LED_data & (MAX_BAR_DATA);
//		data->b = (LED_data >> 10) & MAX_BAR_DATA;
//		data->c = (LED_data >> 20) & MAX_BAR_DATA;
        data->d = (LED_data) & MAX_BAR_DATA;
        data->e = (LED_data >> 10) & MAX_BAR_DATA;
        data->f = (LED_data >> 20) & MAX_BAR_DATA;
        sei();
        delay(speed);
    }
    
    for(LED_data = 0x1; LED_data<=MAX_DATA; LED_data=(2*LED_data+1)){
        cli();
        data->a = ~LED_data & (MAX_BAR_DATA);
		data->b = ~(LED_data >> 10) & MAX_BAR_DATA;
		data->c = ~(LED_data >> 20) & MAX_BAR_DATA;
        data->d = ~(LED_data & 0x0);
        data->e = ~(LED_data & 0x0);
        data->f = ~(LED_data & 0x0);
        sei();
        delay(speed);
    }
    for(LED_data = 0x1; LED_data<=MAX_DATA; LED_data=(2*LED_data+1)){
        cli();
//        data->a = ~LED_data & (MA;_BAR_DATA);
//        data->b = ~(LED_data >> 10) & MAX_BAR_DATA;
//        data->c = ~(LED_data >> 20) & MAX_BAR_DATA;
        data->d = ~(LED_data) & MAX_BAR_DATA;
        data->e = ~(LED_data >> 10) & MAX_BAR_DATA;
        data->f = ~(LED_data >> 20) & MAX_BAR_DATA;
        sei();
        delay(speed);
    }
}

void Effects::horz_fill(volatile Data *data, int speed, Micrel *a)
{
    int i;
	a->Clear();
	for(i=0; i<BAR_SEG; i++){
        
//        cli();
		data->a |= (1<<i);
//        sei();
        delay(speed);
        
//        cli();
		data->b |= (1<<i);
//        sei();
        delay(speed);
		
//        cli();
        data->c |= (1<<i);
//        sei();
        delay(speed);
        
//        cli();
        data->d |= (1<<i);
//        sei();
        delay(speed);
        
//        cli();
        data->e |= (1<<i);
//        sei();
        delay(speed);
        
//        cli();
        data->f |= (1<<i);
//        sei();
        delay(speed);
	}
}

void Effects::DELAY(unsigned long ms)
{
    unsigned long i = millis();
//    digitalWrite(6, HIGH);
//    while((millis()-i) < ms);
//    while(i<100000)
        i++;
//    digitalWrite(6, HIGH);
//    delay(1);
    delayMicroseconds(1000*ms);
}

int level(int value)
{
	switch(value)
	{
        case 0: return NUM_0;
        case 1: return NUM_1;
        case 2: return NUM_2;
        case 3: return NUM_3;
        case 4: return NUM_4;
        case 5: return NUM_5;
        case 6: return NUM_6;
        case 7: return NUM_7;
        case 8: return NUM_8;
        case 9: return NUM_9;
        case 10: return NUM_10;
        default: return NUM_0;
	}
}