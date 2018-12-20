#include <msp430.h> 

unsigned volatile int noteplayed = 0;

void main(void)
 {
    WDTCTL = WDTPW + WDTHOLD;           //stop watchdog timer

    volatile unsigned int i;

    // Note Pin Input
    P6DIR &= ~BIT5; //A0
    P1DIR &= ~BIT6; //A#0
    P6DIR &= ~BIT6; //B0
    P2DIR &= ~BIT7; //C0
    P6DIR &= ~BIT0; //C#0
    P6DIR &= ~BIT1; //D0
    P6DIR &= ~BIT2; //D#0
    P6DIR &= ~BIT3; //E0
    P6DIR &= ~BIT4; //F0
    P7DIR &= ~BIT0; //F#0
    P2DIR &= ~BIT5; //G0
    P2DIR &= ~BIT4; //G#0
    P1DIR &= ~BIT5; //A1
    P1DIR &= ~BIT4; //A#1
    P1DIR &= ~BIT3; //B1
    P1DIR &= ~BIT2; //C1
    P4DIR &= ~BIT3; //C#1
    P4DIR &= ~BIT0; //D1
    P3DIR &= ~BIT7; //D#1
    P8DIR &= ~BIT2; //E1
    P2DIR &= ~BIT0; //F1
    P2DIR &= ~BIT2; //F#1
    P7DIR &= ~BIT4; //G1
    P2DIR &= ~BIT6; //G#1
    P2DIR &= ~BIT3; //A2

    //Configure UART
    P3SEL |= BIT3 + BIT4;                     // Board to Board Select Bits
    P4SEL |= BIT4 + BIT5;                     // Computer to Board Select Bits
    UCA1CTL1 = UCSWRST;                       // initialize USCI
    UCA1CTL1 |= UCSSEL_1;                     // set to use ACLK (UCSSEL_21
    UCA1BR0 = 3;                              // Baud Rate is 9600, should be 104 when running normal SMCLK
    UCA1BR1 = 0;                              // set to 0
    UCA1MCTL |= UCBRS_3 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
    UCA1CTL1 &= ~UCSWRST;                     // initialize USCI
    UCA1IE |= UCRXIE;                         // enable USCI_A1 RX interrupt

    while(1)
    {
        //__bis_SR_register(GIE);                 // Test Setup

        // Configure pins to read if key is pressed and pass the key value of UART
         if((P2IN & BIT3) == BIT3)   //A2
         {
             noteplayed = 25;
         }

         else if((P2IN & BIT6) == BIT6)   //G#1
         {
             noteplayed = 24;
         }
         else if((P7IN & BIT4) == BIT4)   //G1
         {
             noteplayed = 23;
         }
         else if((P2IN & BIT2) == BIT2)   //F#1
         {
             noteplayed = 22;
         }
         else if((P2IN & BIT0) == BIT0)   //F1
         {
             noteplayed = 21;
         }
         else if((P8IN & BIT2) == BIT2)   //E1
         {
             noteplayed = 20;
         }
         else if((P3IN & BIT7) == BIT7)   //D#1
         {
             noteplayed = 19;
         }
         else if((P4IN & BIT0) == BIT0)   //D1
         {
             noteplayed = 18;
         }
         else if((P4IN & BIT3) == BIT3)   //C#1
         {
             noteplayed = 17;
         }
         else if((P1IN & BIT2) == BIT2)   //C1
         {
             noteplayed = 16;
         }
         else if((P1IN & BIT3) == BIT3)   //B1
         {
             noteplayed = 15;
         }
         else if((P1IN & BIT4) == BIT4)   //A#1
         {
             noteplayed = 14;
         }
         else if((P1IN & BIT5) == BIT5)   //A1
         {
             noteplayed = 13;
         }
         else if((P2IN & BIT4) == BIT4)   //G#0
         {
             noteplayed = 12;
         }
         else if((P2IN & BIT5) == BIT5)   //G0
         {
             noteplayed = 11;
         }
         else if((P7IN & BIT0) == BIT0)   //F#0
         {
             noteplayed = 10;
         }
         else if((P6IN & BIT4) == BIT4)   //F0
         {
             noteplayed = 9;
         }
         else if((P6IN & BIT3) == BIT3)   //E0
         {
             noteplayed = 8;
         }
         else if((P6IN & BIT2) == BIT2)   //D#0
         {
             noteplayed = 7;
         }
         else if((P6IN & BIT1) == BIT1)   //D0
         {
             noteplayed = 6;
         }
         else if((P6IN & BIT0) == BIT0)   //C#0
         {
             noteplayed = 5;
         }
         else if((P2IN & BIT7) == BIT7)   //C0
         {
             noteplayed = 4;
         }
         else if((P6IN & BIT6) == BIT6)   //B0
         {
             noteplayed = 3;
         }
         else if((P1IN & BIT6) == BIT6)   //A#0
         {
             noteplayed = 2;
         }
         else if((P6IN & BIT5) == BIT5)   //A0
         {
             noteplayed = 1;
         }

        else //no key is being pressed
        {
            noteplayed = 0;
        }

        UCA1TXBUF = noteplayed; //put the noteplayed on the TXBUF to be sent to the output/filter board
    }
}
