#include  <msp430g2553.h>

volatile unsigned int i = 0;                         

void wait(unsigned int iter)
{
  for (i = 0; i < iter; i++)
    asm("nop");
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

char* morseChar[] = 
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
  "-.-", // K
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
  "--..", // Z  
  "-----", //0
  ".----", //1
  "..---", //2
  "...--", //3
  "....-", //4
  ".....", //5
  "-....", //6
  "--...", //7
  "---..", //8
  "----.", //9
  ".-.-.-" //.
};

void getMChar(char c)
{
  int idx = 0;
  int val = (int)c; 
  char* mChar;
  if (c >= '0' && c <= '9')
  {
    val -= 48;
    idx = (val + 26);
    mChar = morseChar[idx];
  }
  else
  {
    idx = val - 65;
    mChar = morseChar[idx];  
  }
  if (c == '.')
    mChar = morseChar[36];
  char temp = ' ';
  int a = 0;
  while(temp != '\0')
  {
    temp = mChar[a];
    switch(temp)
    {
      case '.': 
        dot();
        break;
      case '-':
        dash();
        break;
    }
    a++;
  }
  wait(50000);
}

void morseStrOut(const char* str)
{
  char c = ' ';
  int a = 0;
  c = str[a];
  while (c != '\0')
  {
    getMChar(c);
    a++;
    c = str[a];
  }
}

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                //Stop watchdog timer 
  P1DIR = BIT0;                            //Set the direction of P1.0 (LED1)
  P1OUT = 0;                               //Set the P1OUT register to a known state
  const char* str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.";
  morseStrOut(str);
  P1DIR = BIT6;                            //Turn on the green LED (P1.6) just for debug purposes
  P1OUT = BIT6;
  for(;;);
}
