#include "cross_compiler.h"

#ifdef UART

// Method for transmitting value using serial bit banging
#define MYONE 1
#define MYZERO 0
void uart_tx_bit_bang(unsigned char val) {
    unsigned char i;
    UART_OUT_PIN = MYZERO;                         // Start bit
    Delay_100_us();
    for ( i = 8 ; i != 0 ; --i )
    {
        if (val & 0x01)
        {
            UART_OUT_PIN = MYONE;   // Begin with LSB
        }
        else
        {
            UART_OUT_PIN = MYZERO;
        }
        val >>= 1;
        Delay_100_us();
    }
    UART_OUT_PIN = MYONE;                         // Stop bit
    Delay_100_us();
    Delay_100_us();//  add some extra delays after the stop bit
}

//  posstr is:   
//  the thousands digit is the row.  range is 0-6.  for some displays divide it by 2
//  to get the correct row.
//  the 3 ls digits is the column
void uart_wr_str(char str[], char length)
{
   for (char i = 0; i < length; i++)
   { // write string
      if (str[i] == 0)
      {
         break;
      }
      uart_tx_bit_bang(str[i]);
    }
}



void uart_wr_str_ln(char str[], char length)
{
   uart_wr_str(str, length);  
   uart_tx_bit_bang(0x0d);  // send a CR
   uart_tx_bit_bang(0x0a);  // send a LF
}

#endif