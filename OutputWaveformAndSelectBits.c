#include <msp430.h> 
#include <math.h>

volatile unsigned int counter = 0;
volatile unsigned int noteplayed = 1;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // stop watchdog timer

    // Speed up SMCLK for 8-Bit Sawtooth
    UCSCTL3 |= SELREF__REFOCLK;             // Set DCO FLL reference = REFO
    UCSCTL4 |=  XT1OFF | XT2OFF;            // Set ACLK = REFO
    __bis_SR_register(SCG0);                // Disable the FLL control loop
    UCSCTL0 = 0x0000;                       // Set lowest possible DCOx, MODx
    UCSCTL1 = DCORSEL_7;                    // Select DCO range 24MHz operation
    UCSCTL2 = 762u;                         // Set DCO Multiplier for 16MHz
                                                   // (N + 1) * FLLRef = Fdco
                                                   // (488 + 1) * 32768 = 16.023552MHz
                                                   // Set FLL Div = fDCOCLK/2
    UCSCTL4 = SELA__REFOCLK | SELS__DCOCLK | SELM__DCOCLK;

    //Configure UART
    P3SEL |= BIT3 + BIT4;                   // Board to Board Select Bits
    P4SEL |= BIT4 + BIT5;                   // Computer to Board Select Bits
    UCA1CTL1 = UCSWRST;                     // initialize USCI
    UCA1CTL1 |= UCSSEL_1;                   // set to use ACLK (UCSSEL_21
    UCA1BR0 = 3;                            // Baud Rate is 9600, should be 104 when running normal SMCLK
    UCA1BR1 = 0;                            // set to 0
    UCA1MCTL |= UCBRS_3 + UCBRF_0;          // Modulation UCBRSx=1, UCBRFx=0
    UCA1CTL1 &= ~UCSWRST;                   // initialize USCI
    UCA1IE |= UCRXIE;                       // enable USCI_A1 RX interrupt

    __bis_SR_register(SCG0);                // Enable the FLL control loop

    // Initialize Outputs   // DAC Input:
    P1DIR |= BIT2;          // 1
    P1DIR |= BIT3;          // 2
    P1DIR |= BIT4;          // 3
    P1DIR |= BIT5;          // 4
    P2DIR |= BIT4;          // 5
    P2DIR |= BIT5;          // 6
    P2DIR |= BIT2;          // 7
    P2DIR |= BIT0;          // 8

    // Initialize Select Bits
    P6DIR |= BIT5;          //RS0
    P1DIR |= BIT6;          //RS1
    P6DIR |= BIT6;          //RS2
    P2DIR |= BIT7;          //RE0
    P6DIR |= BIT0;          //RE1
    P6DIR |= BIT1;          //LS0
    P6DIR |= BIT2;          //LS1
    P6DIR |= BIT3;          //LE0
    P6DIR |= BIT4;          //CS0
    P7DIR |= BIT0;          //CS1
    P4DIR |= BIT3;          //CS2
    P4DIR |= BIT0;          //CE0
    P7DIR |= BIT4;          //CE1
    P8DIR |= BIT2;          //CE2

    TB0CTL = TBSSEL_2 + MC_1 + ID_0;    // Timer is in continuous mode, uses SMCLK and divide by 4
    TB0CCR0 = 0;                        // Initialize CCR0
    TB0CCTL0 = CCIE;                    // enable interrupt for the clock

    while(1)
    {
        __bis_SR_register(GIE);                 // Test Setup
        switch(noteplayed)
        {
            case 1: TB0CCR0 = 1797;// A0
                    P6OUT &= ~BIT5;         //RS0
                    P1OUT &= ~BIT6;         //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT &= ~BIT1;         //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT &= ~BIT4;         //CS0
                    P7OUT &= ~BIT0;         //CS1
                    P4OUT &= ~BIT3;         //CS2
                    P4OUT &= ~BIT0;         //CE0
                    P7OUT |= BIT4;          //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 2: TB0CCR0 = 1696;// A#0
                    P6OUT |= BIT5;          //RS0
                    P1OUT &= ~BIT6;         //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT &= ~BIT1;         //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT |= BIT4;          //CS0
                    P7OUT &= ~BIT0;         //CS1
                    P4OUT &= ~BIT3;         //CS2
                    P4OUT &= ~BIT0;         //CE0
                    P7OUT |= BIT4;          //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 3: TB0CCR0 = 1601;// B0
                    P6OUT |= BIT5;          //RS0
                    P1OUT &= ~BIT6;         //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT &= ~BIT1;         //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT &= ~BIT4;         //CS0
                    P7OUT |= BIT0;          //CS1
                    P4OUT &= ~BIT3;         //CS2
                    P4OUT &= ~BIT0;         //CE0
                    P7OUT |= BIT4;          //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 4: TB0CCR0 = 1511;// C1
                    P6OUT &= ~BIT5;         //RS0
                    P1OUT |= BIT6;          //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT &= ~BIT1;         //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT |= BIT4;          //CS0
                    P7OUT |= BIT0;          //CS1
                    P4OUT &= ~BIT3;         //CS2
                    P4OUT &= ~BIT0;         //CE0
                    P7OUT |= BIT4;          //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 5: TB0CCR0 = 1426;// C#1
                    P6OUT &= ~BIT5;         //RS0
                    P1OUT &= ~BIT6;         //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT |= BIT1;          //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT &= ~BIT4;         //CS0
                    P7OUT |= BIT0;          //CS1
                    P4OUT &= ~BIT3;         //CS2
                    P4OUT &= ~BIT0;         //CE0
                    P7OUT |= BIT4;          //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 6: TB0CCR0 = 1346;// D1
                    P6OUT |= BIT5;          //RS0
                    P1OUT &= ~BIT6;         //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT |= BIT1;          //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT |= BIT4;          //CS0
                    P7OUT |= BIT0;          //CS1
                    P4OUT &= ~BIT3;         //CS2
                    P4OUT &= ~BIT0;         //CE0
                    P7OUT |= BIT4;          //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 7: TB0CCR0 = 1271;// D#1
                    P6OUT &= ~BIT5;         //RS0
                    P1OUT &= ~BIT6;         //RS1
                    P6OUT |= BIT6;          //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT |= BIT1;          //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT |= BIT4;          //CS0
                    P7OUT |= BIT0;          //CS1
                    P4OUT |= BIT3;          //CS2
                    P4OUT &= ~BIT0;         //CE0
                    P7OUT |= BIT4;          //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 8: TB0CCR0 = 1199;// E1
                    P6OUT &= ~BIT5;         //RS0
                    P1OUT &= ~BIT6;         //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT &= ~BIT1;         //LS0
                    P6OUT |= BIT2;          //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT &= ~BIT4;         //CS0
                    P7OUT &= ~BIT0;         //CS1
                    P4OUT |= BIT3;          //CS2
                    P4OUT &= ~BIT0;         //CE0
                    P7OUT |= BIT4;          //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 9: TB0CCR0 = 1132;// F1
                    P6OUT |= BIT5;          //RS0
                    P1OUT |= BIT6;          //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT |= BIT1;          //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT |= BIT4;          //CS0
                    P7OUT |= BIT0;          //CS1
                    P4OUT |= BIT3;          //CS2
                    P4OUT &= ~BIT0;         //CE0
                    P7OUT |= BIT4;          //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 10:TB0CCR0 = 1059;// F#1
                    P6OUT |= BIT5;          //RS0
                    P1OUT &= ~BIT6;         //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT &= ~BIT1;         //LS0
                    P6OUT |= BIT2;          //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT &= ~BIT4;         //CS0
                    P7OUT |= BIT0;          //CS1
                    P4OUT |= BIT3;          //CS2
                    P4OUT &= ~BIT0;         //CE0
                    P7OUT |= BIT4;          //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 11:TB0CCR0 = 1008;// G1
                    P6OUT &= ~BIT5;         //RS0
                    P1OUT &= ~BIT6;         //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT |= BIT1;          //LS0
                    P6OUT |= BIT2;          //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT |= BIT4;          //CS0
                    P7OUT &= ~BIT0;         //CS1
                    P4OUT |= BIT3;          //CS2
                    P4OUT &= ~BIT0;         //CE0
                    P7OUT |= BIT4;          //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 12:TB0CCR0 = 952;// G#1
                    P6OUT &= ~BIT5;         //RS0
                    P1OUT |= BIT6;          //RS1
                    P6OUT |= BIT6;          //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT &= ~BIT1;         //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT &= ~BIT4;         //CS0
                    P7OUT &= ~BIT0;         //CS1
                    P4OUT &= ~BIT3;         //CS2
                    P4OUT |= BIT0;          //CE0
                    P7OUT &= ~BIT4;         //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 13:TB0CCR0 = 898;// A1
                    P6OUT |= BIT5;          //RS0
                    P1OUT |= BIT6;          //RS1
                    P6OUT |= BIT6;          //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT &= ~BIT1;         //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT |= BIT4;          //CS0
                    P7OUT &= ~BIT0;         //CS1
                    P4OUT &= ~BIT3;         //CS2
                    P4OUT |= BIT0;          //CE0
                    P7OUT &= ~BIT4;         //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 14:TB0CCR0 = 848;// A#1
                    P6OUT &= ~BIT5;         //RS0
                    P1OUT |= BIT6;          //RS1
                    P6OUT |= BIT6;          //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT |= BIT1;          //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT &= ~BIT4;         //CS0
                    P7OUT &= ~BIT0;         //CS1
                    P4OUT |= BIT3;          //CS2
                    P4OUT |= BIT0;          //CE0
                    P7OUT &= ~BIT4;         //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 15:TB0CCR0 = 800;// B1
                    P6OUT &= ~BIT5;         //RS0
                    P1OUT |= BIT6;          //RS1
                    P6OUT |= BIT6;          //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT |= BIT1;          //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT |= BIT4;          //CS0
                    P7OUT &= ~BIT0;         //CS1
                    P4OUT &= ~BIT3;         //CS2
                    P4OUT |= BIT0;          //CE0
                    P7OUT &= ~BIT4;         //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 16:TB0CCR0 = 767;// C2
                    P6OUT |= BIT5;          //RS0
                    P1OUT &= ~BIT6;         //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT |= BIT7;          //RE0
                    P6OUT &= ~BIT0;         //RE1
                    P6OUT &= ~BIT1;         //LS0
                    P6OUT &= BIT2;          //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT |= BIT4;          //CS0
                    P7OUT &= ~BIT0;         //CS1
                    P4OUT |= BIT3;          //CS2
                    P4OUT |= BIT0;          //CE0
                    P7OUT &= ~BIT4;         //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 17:TB0CCR0 = 713;// C#2
                    P6OUT &= ~BIT5;         //RS0
                    P1OUT &= ~BIT6;         //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT |= BIT7;          //RE0
                    P6OUT &= ~BIT0;         //RE1
                    P6OUT |= BIT1;          //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT &= ~BIT4;         //CS0
                    P7OUT &= ~BIT0;         //CS1
                    P4OUT |= BIT3;          //CS2
                    P4OUT |= BIT0;         //CE0
                    P7OUT &= ~BIT4;          //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 18:TB0CCR0 = 673;// D2
                    P6OUT &= ~BIT5;         //RS0
                    P1OUT &= ~BIT6;         //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT |= BIT7;          //RE0
                    P6OUT &= ~BIT0;         //RE1
                    P6OUT |= BIT1;          //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT |= BIT4;          //CS0
                    P7OUT &= ~BIT0;         //CS1
                    P4OUT |= BIT3;          //CS2
                    P4OUT |= BIT0;          //CE0
                    P7OUT &= ~BIT4;         //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 19:TB0CCR0 = 635;// D#2
                    P6OUT |= BIT5;          //RS0
                    P1OUT &= ~BIT6;         //RS1
                    P6OUT |= BIT6;          //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT |= BIT1;          //LS0
                    P6OUT |= BIT2;          //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT &= ~BIT4;         //CS0
                    P7OUT |= BIT0;          //CS1
                    P4OUT &= ~BIT3;         //CS2
                    P4OUT |= BIT0;          //CE0
                    P7OUT &= ~BIT4;         //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 20:TB0CCR0 = 599;// E2
                    P6OUT |= BIT5;          //RS0
                    P1OUT &= ~BIT6;         //RS1
                    P6OUT |= BIT6;          //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT |= BIT1;          //LS0
                    P6OUT |= BIT2;          //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT |= BIT4;          //CS0
                    P7OUT |= BIT0;          //CS1
                    P4OUT &= ~BIT3;         //CS2
                    P4OUT |= BIT0;          //CE0
                    P7OUT &= ~BIT4;         //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 21:TB0CCR0 = 566;// F2
                    P6OUT &= ~BIT5;         //RS0
                    P1OUT &= ~BIT6;         //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT |= BIT7;          //RE0
                    P6OUT &= ~BIT0;         //RE1
                    P6OUT &= ~BIT1;         //LS0
                    P6OUT |= BIT2;          //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT |= BIT4;          //CS0
                    P7OUT |= BIT0;          //CS1
                    P4OUT |= BIT3;          //CS2
                    P4OUT |= BIT0;          //CE0
                    P7OUT &= ~BIT4;         //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 22:TB0CCR0 = 534;// F#2
                    P6OUT &= ~BIT5;         //RS0
                    P1OUT |= BIT6;          //RS1
                    P6OUT |= BIT6;          //RS2
                    P2OUT &= ~BIT7;         //RE0
                    P6OUT |= BIT0;          //RE1
                    P6OUT |= BIT1;          //LS0
                    P6OUT |= BIT2;          //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT &= ~BIT4;         //CS0
                    P7OUT |= BIT0;          //CS1
                    P4OUT |= BIT3;          //CS2
                    P4OUT |= BIT0;          //CE0
                    P7OUT &= ~BIT4;         //CE1
                    P8OUT |= BIT2;          //CE2
                break;
            case 23:TB0CCR0 = 504;// G2
                    P6OUT &= ~BIT5;         //RS0
                    P1OUT |= BIT6;          //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT |= BIT7;          //RE0
                    P6OUT &= ~BIT0;         //RE1
                    P6OUT |= BIT1;          //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT &= ~BIT4;         //CS0
                    P7OUT &= ~BIT0;         //CS1
                    P4OUT &= ~BIT3;         //CS2
                    P4OUT |= BIT0;          //CE0
                    P7OUT |= BIT4;          //CE1
                    P8OUT &= ~BIT2;         //CE2
                break;
            case 24:TB0CCR0 = 476;// G#2
                    P6OUT &= ~BIT5;         //RS0
                    P1OUT |= BIT6;          //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT |= BIT7;          //RE0
                    P6OUT &= ~BIT0;         //RE1
                    P6OUT |= BIT1;          //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT |= BIT4;          //CS0
                    P7OUT &= ~BIT0;         //CS1
                    P4OUT &= ~BIT3;         //CS2
                    P4OUT |= BIT0;          //CE0
                    P7OUT |= BIT4;          //CE1
                    P8OUT &= ~BIT2;         //CE2
                break;
            case 25:TB0CCR0 = 449;// A2
                    P6OUT |= BIT5;          //RS0
                    P1OUT |= BIT6;          //RS1
                    P6OUT &= ~BIT6;         //RS2
                    P2OUT |= BIT7;          //RE0
                    P6OUT &= ~BIT0;         //RE1
                    P6OUT |= BIT1;          //LS0
                    P6OUT &= ~BIT2;         //LS1
                    P6OUT &= ~BIT3;         //LE0
                    P6OUT &= ~BIT4;         //CS0
                    P7OUT |= BIT0;          //CS1
                    P4OUT &= ~BIT3;         //CS2
                    P4OUT |= BIT0;          //CE0
                    P7OUT |= BIT4;          //CE1
                    P8OUT &= ~BIT2;         //CE2
                break;
            default: TB0CCR0 = 65354;       //default return 0
        }
    }
}

    //Sawtooth Timer Interrupt Vector (Goes into the DAC)
    #pragma vector = TIMER0_B0_VECTOR
    __interrupt void TIMERTEST(void)
    {
        if(noteplayed > 0)          // If there is a note being played
        {
            // Create an 8-Bit counter
            if(counter > 255)
                counter = 0;

            counter = counter + 1;

            // 1's Bit
            if(counter % 2 == 1)
                P1OUT |= BIT2;
            else
                P1OUT &= ~BIT2;

            // 2's Bit
            if(counter % 4 >= 2)
                P1OUT |= BIT3;
            else
                P1OUT &= ~BIT3;

            // 4's Bit
            if(counter % 8 >= 4)
                P1OUT |= BIT4;
            else
                P1OUT &= ~BIT4;

            // 8's Bit
            if(counter % 16 >= 8)
                P1OUT |= BIT5;
            else
                P1OUT &= ~BIT5;

            // 16's Bit
            if(counter % 32 >= 16)
                P2OUT |= BIT4;
            else
                P2OUT &= ~BIT4;

            // 32's Bit
            if(counter % 64 >= 32)
                P2OUT |= BIT5;
            else
                P2OUT &= ~BIT5;

            // 64's Bit
            if(counter % 128 >= 64)
                P2OUT |= BIT2;
            else
                P2OUT &= ~BIT2;

            // 128's Bit
            if(counter % 256 >= 128)
                P2OUT |= BIT0;
            else
                P2OUT &= ~BIT0;
        }

        else // if nothing is being played
        {
            // Turn off all pins
            P1OUT &= ~BIT2;
            P1OUT &= ~BIT3;
            P1OUT &= ~BIT4;
            P1OUT &= ~BIT5;
            P2OUT &= ~BIT4;
            P2OUT &= ~BIT5;
            P2OUT &= ~BIT0;
            P2OUT &= ~BIT2;
        }
    }

// Receiving UART Interrupt
#pragma vector=USCI_A1_VECTOR
__interrupt void Temp_control(void)
{
  switch(__even_in_range(UCA1IV,4))
  {
      case 0:break;                             // Vector 0 - no interrupt
      case 2:                                   // Vector 2 - RXIFG
          noteplayed = UCA1RXBUF;               // Store noteplayed into the RXBUF
          break;
      case 4:break;                             // Vector 4 - TXIFG
      default: break;
  }
}
