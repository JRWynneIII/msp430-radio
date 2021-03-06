#include <msp430g2553.h>

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

void initADCTemp()
{
  ADC10CTL0=SREF_1 + REFON + ADC10ON + ADC10SHT_3;  //1.5V reference, ref on, 64 clocks per sample
  ADC10CTL1=INCH_10 + ADC10DIV_3;                   //temp sensor is at 10 and clock/4
}

int getTemp()
{
  int t=0;
  __delay_cycles(1000);                             //wait for ref to settle
  ADC10CTL0 |= ENC + ADC10SC;                       //enable and start conversion
  while(ADC10CTL0 & BUSY);                          //Wait while busy
  t=ADC10MEM;                                       //store temp in t
  ADC10CTL0 &= ~ENC;                                //And it with NOT Enc to disable adc conversion
  return (int)((t*27069L - 18169625L) >> 16);       //Convert value 
}

char* itoa(int value, char* str, int radix) 
{
    static char dig[] =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz";
    int n = 0, neg = 0;
    unsigned int v;
    char* p, *q;
    char c;
    if (radix == 10 && value < 0) 
    {
        value = -value;
        neg = 1;
    }
    v = value;
    do 
    {
        str[n++] = dig[v%radix];
        v /= radix;
    } while (v);
    if (neg)
        str[n++] = '-';
    str[n] = '\0';
    for (p = str, q = p + n/2; p != q; ++p, --q)
        c = *p, *p = *q, *q = c;
    return str;
}

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                //Stop watchdog timer 
  P1DIR = BIT0;                            //Set the direction of P1.0 (LED1)
  P1OUT = 0;                               //Set the P1OUT register to a known state
  volatile int temp = 0;
  initADCTemp();
  char* str;
  while(1)
  {
    __delay_cycles(500);
    temp = getTemp();
    itoa(temp,str,10);
    __delay_cycles(500);
    morseStrOut(str);
  }
}
