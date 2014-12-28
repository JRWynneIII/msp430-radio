#include  <msp430g2553.h>

volatile unsigned int i = 0;                         

void wait(unsigned int iter)
{
  for (i = 0; i < iter; i++);
}

void dot()
{
  P1OUT ^= BIT0;
  wait(10000);
  P1OUT ^= BIT0;
  wait(30000);
}

void dash()
{
  P1OUT ^= BIT0;
  wait(30000);
  P1OUT ^= BIT0;
  wait(30000);
}

void getMChar(char c)
{
  char* morse_table[] = 
  { 
    ".-" , // A
    "-...", // B
    "-.-.", // C
    "-..", // D
    ".", // E
    "..-.", // F
    "--." , // G
    "....", // H
    ".."  , // I
    ".---", // J
    ".-.-", // K
    ".-..", // L
    "--", // M
    "-.", // N
    "---", // O
    ".--.", // P
    "--.-", // Q
    ".-.", // R
    "...", // S
    "-", // T
    "..-", // U
    "...-", // V
    ".--", // W
    "-..-", // X
    "-.--", // Y
    "--.." // Z  
  };
  int val = (int)c;
  int idx = val - 65;
  char* mChar = morse_table[idx];  
  char temp = ' ';
  int a = 0;
  while(temp != '\0')
  {
    temp = mChar[a];
    if (temp == '.')
      dot();
    else if (temp == '-')
      dash();
    a++;
  }
}

void morseStrOut(char* str)
{
  char c = ' ';
  int a = 0;
  while (c != '\0')
  {
    c = str[a];
    getMChar(c);
    a++;
  }
}

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                //Stop watchdog timer 
  P1DIR = BIT0;                            //Set the direction of P1.0 (LED1)
  P1OUT = 0;                               //Set the P1OUT register to a known state
  morseStrOut("Jake");
  P1DIR = BIT6;                            //Turn on the green LED (P1.6) just for debug purposes
  P1OUT = BIT6;
  for(;;);
}


