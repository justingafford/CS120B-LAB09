/*	Partner 1's Name & E-mail: Justin Gafford jgaff001@ucr.edu
*  Partner 2's Name & E-mail: Wang Sitao 934415487@qq.com
*	Lab Section: 022
*	Assignment: Lab #9 Exercise #3
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/

#include <avr/io.h>
#include "io.c"
#include <stdlib.h>
#define D1 2000
#define button1 (PINA & 0x01)
#define button2 (PINA & 0x02)
#define button3 (PINA & 0x04)
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
double note[] ={261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88,523.25};

enum state{start,stop}state;
void TimerOn(){
    TCCR1B = 0x0B;
    OCR1A = 125;
    TIMSK1 = 0x02;
    TCNT1 = 0;
    _avr_timer_cntcurr = _avr_timer_M;
    SREG |= 0x80;
}

void TimerOff(){
    TCCR1B = 0X00;
}

void TimerISR(){
    TimerFlag = 1;
}
ISR(TIMER1_COMPA_vect){
    _avr_timer_cntcurr--;
    if (_avr_timer_cntcurr == 0){
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

void TimerSet(unsigned long M){
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}
void set_PWM(double frequency) {
    static double current_frequency; // Keeps track of the currently set frequency
    // Will only update the registers when the frequency changes, otherwise allows
    // music to play uninterrupted.
    if (frequency != current_frequency) {
        if (!frequency) { TCCR0B &= 0x08; } //stops timer/counter
        else { TCCR0B |= 0x03; } // resumes/continues timer/counter
        
        // prevents OCR3A from overflowing, using prescaler 64
        // 0.954 is smallest frequency that will not result in overflow
        if (frequency < 0.954) { OCR0A = 0xFFFF; }
        
        // prevents OCR0A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
        else if (frequency > 31250) { OCR0A = 0x0000; }
        
        // set OCR3A based on desired frequency
        else { OCR0A = (short)(8000000 / (128 * frequency)) - 1; }

        TCNT0 = 0; // resets counter
        current_frequency = frequency; // Updates the current frequency
    }
}

void PWM_on() {
    TCCR0A = (1<<WGM02)|(1<<WGM00)|(1 << COM0A0);
    // COM3A0: Toggle PB3 on compare match between counter and OCR0A
    TCCR0B = (1 << WGM02) | (1 << CS01) | (1 << CS00);
    // WGM02: When counter (TCNT0) matches OCR0A, reset counter
    // CS01 & CS30: Set a prescaler of 64
    //set_PWM(0);
}

void PWM_off() {
    TCCR0A = 0x00;
    TCCR0B = 0x00;
}

void Tick(){
    while(!TimerFlag){}
    TimerFlag = 0;
}


    
void sm(){
    
    switch(state){
        case stop:
            if (!button1)
            {
                state = start;
            }
            break;
        case start:
            if (!button1)
            {
                state = stop;
            }            
            break;  
        default: 
            state = stop;
            
        
        
        
    }
    switch(state){
        case stop:
            Tick();
            PWM_off();
            Tick();
            break;
        case start:
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
        set_PWM(note[rand()%8]);
        Tick();
        PWM_on();
        Tick();
            break;
    }
}
int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    
    /* Replace with your application code */
    TimerSet(100);
    TimerOn();
    
    while (1) 
    {
        /*set_PWM(D1);
        Tick();
        PWM_on();
        Tick();
        Tick();*/
        state = start;
        sm();
        
        
        
           
    }
}

