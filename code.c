
#ifndef F_CPU
#define F_CPU 800000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
void adc_init()
{
     
    ADMUX = (1<<REFS0); //ADC's reference being set 
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Pre-scaler 
}

uint16_t adc_read(uint8_t ch) //Get the ADC value to be read
{
    
    ch &= 0b00000111;  //Select channel
    ADMUX = (ADMUX & 0xF8)|ch;    //'1' to ADSC 
    ADCSRA |= (1<<ADSC); //'0' to ADSC
    while(ADCSRA & (1<<ADSC)); 
    return (ADC);
}
int main(void)
{
    DDRB=(1<<PINB5);
    uint16_t adc_result0;
    int temp; //Initialising the variable which will be storing our temperature value 
    adc_init(); //We are initializing ADC
    adc_result0 = adc_read(0); // Reading the ADC values 
        

    while(1) //Running a while loop here infinitely
    {
        temp=adc_result0/2.0;   //Calculating the temperature 
      
        if (temp>15)  //Checks for the numerical value to be lower than 15
       {                     
           PORTB=(1<<PINB5);
            _delay_ms(3000);
            PORTB=(0<<PINB5);     /*If condition is true, this portion of code runs 
                                   * and makes the LED and Buzzer turn on and off at intervals which 
                                    results in flashing*/
            _delay_ms(3000);        
            PORTB=(1<<PINB5);
            _delay_ms(3000);
            PORTB=(0<<PINB5);
            _delay_ms(3000);
        }
        else //If condition is not true, the LED and Buzzer both remaining OFF
        {
            PORTB=(0<<PINB5); 
        }
        
    }
  
}
