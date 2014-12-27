#include  <msp430g2553.h>

volatile int i = 0;                         

void dot(int num = 1)
{
  for(int a = 0; a < num; a++)
  {
    P1OUT ^= 0x01;
    for(i=0; i< 10000; i++); 
    P1OUT ^= 0x01;
    for(i=0; i< 10000; i++); 
  }
  for(i=0; i< 30000; i++); 
}

void dash(int num = 1)
{
  for(int a = 0; a < num; a++)
  {
    P1OUT ^= 0x01;
    for(i=0; i< 20000; i++); 
    P1OUT ^= 0x01;
    for(i=0; i< 20000; i++); 
  }
  for(i=0; i< 30000; i++); 
}

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                //Stop watchdog timer 
  P1DIR = 0x01;
  P1OUT = 0;
  dot(3);
  dash(3);
  dot(3);
  for(;;);
}

