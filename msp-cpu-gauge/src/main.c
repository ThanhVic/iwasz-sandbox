#include <msp430.h>
//#include <gpio.h>
#include <driverlib.h>
#include <stdlib.h>
#include <ucs.h>

#define PERIOD 0xfff
#define STEPS 512
#define CLK_FREQ 10000000

const int SINE[] = {
                0,50,100,151,201,251,301,351,401,451,501,551,601,651,700,750,799,848,897,946,
                995,1044,1092,1141,1189,1237,1285,1332,1380,1427,1474,1521,1567,1613,1659,1705,1751,1796,1841,1886,
                1930,1975,2018,2062,2105,2148,2191,2233,2275,2317,2358,2399,2439,2480,2519,2559,2598,2636,2675,2713,
                2750,2787,2824,2860,2896,2931,2966,3000,3034,3068,3101,3133,3165,3197,3228,3259,3289,3319,3348,3377,
                3405,3433,3460,3486,3512,3538,3563,3588,3611,3635,3658,3680,3702,3723,3744,3764,3783,3802,3821,3838,
                3856,3872,3888,3904,3919,3933,3947,3960,3972,3984,3996,4006,4016,4026,4035,4043,4051,4058,4064,4070,
                4075,4080,4084,4087,4090,4092,4094,4095,4095,4095,4094,4092,4090,4087,4084,4080,4075,4070,4064,4058,
                4051,4043,4035,4026,4016,4006,3996,3984,3972,3960,3947,3933,3919,3904,3888,3872,3856,3838,3821,3802,
                3783,3764,3744,3723,3702,3680,3658,3635,3611,3588,3563,3538,3512,3486,3460,3433,3405,3377,3348,3319,
                3289,3259,3228,3197,3165,3133,3101,3068,3034,3000,2966,2931,2896,2860,2824,2787,2750,2713,2675,2636,
                2598,2559,2519,2480,2439,2399,2358,2317,2275,2233,2191,2148,2105,2062,2018,1975,1930,1886,1841,1796,
                1751,1705,1659,1613,1567,1521,1474,1427,1380,1332,1285,1237,1189,1141,1092,1044,995,946,897,848,
                799,750,700,651,601,551,501,451,401,351,301,251,201,151,100,50,0,-50,-100,-151,
                -201,-251,-301,-351,-401,-451,-501,-551,-601,-651,-700,-750,-799,-848,-897,-946,-995,-1044,-1092,-1141,
                -1189,-1237,-1285,-1332,-1380,-1427,-1474,-1521,-1567,-1613,-1659,-1705,-1751,-1796,-1841,-1886,-1930,-1975,-2018,-2062,
                -2105,-2148,-2191,-2233,-2275,-2317,-2358,-2399,-2439,-2480,-2519,-2559,-2598,-2636,-2675,-2713,-2750,-2787,-2824,-2860,
                -2896,-2931,-2966,-3000,-3034,-3068,-3101,-3133,-3165,-3197,-3228,-3259,-3289,-3319,-3348,-3377,-3405,-3433,-3460,-3486,
                -3512,-3538,-3563,-3588,-3611,-3635,-3658,-3680,-3702,-3723,-3744,-3764,-3783,-3802,-3821,-3838,-3856,-3872,-3888,-3904,
                -3919,-3933,-3947,-3960,-3972,-3984,-3996,-4006,-4016,-4026,-4035,-4043,-4051,-4058,-4064,-4070,-4075,-4080,-4084,-4087,
                -4090,-4092,-4094,-4095,-4095,-4095,-4094,-4092,-4090,-4087,-4084,-4080,-4075,-4070,-4064,-4058,-4051,-4043,-4035,-4026,
                -4016,-4006,-3996,-3984,-3972,-3960,-3947,-3933,-3919,-3904,-3888,-3872,-3856,-3838,-3821,-3802,-3783,-3764,-3744,-3723,
                -3702,-3680,-3658,-3635,-3611,-3588,-3563,-3538,-3512,-3486,-3460,-3433,-3405,-3377,-3348,-3319,-3289,-3259,-3228,-3197,
                -3165,-3133,-3101,-3068,-3034,-3000,-2966,-2931,-2896,-2860,-2824,-2787,-2750,-2713,-2675,-2636,-2598,-2559,-2519,-2480,
                -2439,-2399,-2358,-2317,-2275,-2233,-2191,-2148,-2105,-2062,-2018,-1975,-1930,-1886,-1841,-1796,-1751,-1705,-1659,-1613,
                -1567,-1521,-1474,-1427,-1380,-1332,-1285,-1237,-1189,-1141,-1092,-1044,-995,-946,-897,-848,-799,-750,-700,-651,
                -601,-551,-501,-451,-401,-351,-301,-251,-201,-151,-100,-50
};

const int COSINE[] = {
                4095,4095,4094,4092,4090,4087,4084,4080,4075,4070,4064,4058,4051,4043,4035,4026,4016,4006,3996,3984,
                3972,3960,3947,3933,3919,3904,3888,3872,3856,3838,3821,3802,3783,3764,3744,3723,3702,3680,3658,3635,
                3611,3588,3563,3538,3512,3486,3460,3433,3405,3377,3348,3319,3289,3259,3228,3197,3165,3133,3101,3068,
                3034,3000,2966,2931,2896,2860,2824,2787,2750,2713,2675,2636,2598,2559,2519,2480,2439,2399,2358,2317,
                2275,2233,2191,2148,2105,2062,2018,1975,1930,1886,1841,1796,1751,1705,1659,1613,1567,1521,1474,1427,
                1380,1332,1285,1237,1189,1141,1092,1044,995,946,897,848,799,750,700,651,601,551,501,451,
                401,351,301,251,201,151,100,50,0,-50,-100,-151,-201,-251,-301,-351,-401,-451,-501,-551,
                -601,-651,-700,-750,-799,-848,-897,-946,-995,-1044,-1092,-1141,-1189,-1237,-1285,-1332,-1380,-1427,-1474,-1521,
                -1567,-1613,-1659,-1705,-1751,-1796,-1841,-1886,-1930,-1975,-2018,-2062,-2105,-2148,-2191,-2233,-2275,-2317,-2358,-2399,
                -2439,-2480,-2519,-2559,-2598,-2636,-2675,-2713,-2750,-2787,-2824,-2860,-2896,-2931,-2966,-3000,-3034,-3068,-3101,-3133,
                -3165,-3197,-3228,-3259,-3289,-3319,-3348,-3377,-3405,-3433,-3460,-3486,-3512,-3538,-3563,-3588,-3611,-3635,-3658,-3680,
                -3702,-3723,-3744,-3764,-3783,-3802,-3821,-3838,-3856,-3872,-3888,-3904,-3919,-3933,-3947,-3960,-3972,-3984,-3996,-4006,
                -4016,-4026,-4035,-4043,-4051,-4058,-4064,-4070,-4075,-4080,-4084,-4087,-4090,-4092,-4094,-4095,-4095,-4095,-4094,-4092,
                -4090,-4087,-4084,-4080,-4075,-4070,-4064,-4058,-4051,-4043,-4035,-4026,-4016,-4006,-3996,-3984,-3972,-3960,-3947,-3933,
                -3919,-3904,-3888,-3872,-3856,-3838,-3821,-3802,-3783,-3764,-3744,-3723,-3702,-3680,-3658,-3635,-3611,-3588,-3563,-3538,
                -3512,-3486,-3460,-3433,-3405,-3377,-3348,-3319,-3289,-3259,-3228,-3197,-3165,-3133,-3101,-3068,-3034,-3000,-2966,-2931,
                -2896,-2860,-2824,-2787,-2750,-2713,-2675,-2636,-2598,-2559,-2519,-2480,-2439,-2399,-2358,-2317,-2275,-2233,-2191,-2148,
                -2105,-2062,-2018,-1975,-1930,-1886,-1841,-1796,-1751,-1705,-1659,-1613,-1567,-1521,-1474,-1427,-1380,-1332,-1285,-1237,
                -1189,-1141,-1092,-1044,-995,-946,-897,-848,-799,-750,-700,-651,-601,-551,-501,-451,-401,-351,-301,-251,
                -201,-151,-100,-50,0,50,100,151,201,251,301,351,401,451,501,551,601,651,700,750,
                799,848,897,946,995,1044,1092,1141,1189,1237,1285,1332,1380,1427,1474,1521,1567,1613,1659,1705,
                1751,1796,1841,1886,1930,1975,2018,2062,2105,2148,2191,2233,2275,2317,2358,2399,2439,2480,2519,2559,
                2598,2636,2675,2713,2750,2787,2824,2860,2896,2931,2966,3000,3034,3068,3101,3133,3165,3197,3228,3259,
                3289,3319,3348,3377,3405,3433,3460,3486,3512,3538,3563,3588,3611,3635,3658,3680,3702,3723,3744,3764,
                3783,3802,3821,3838,3856,3872,3888,3904,3919,3933,3947,3960,3972,3984,3996,4006,4016,4026,4035,4043,
                4051,4058,4064,4070,4075,4080,4084,4087,4090,4092,4094,4095
};

/**
 * From 0 to PERIOD (including).
 */
void setWinding1 (int power)
{
        TA0CCR1 = PERIOD - abs (power);
//        TA0CCR1 = 0;

        if (power >= 0) {
                P6OUT &= ~GPIO_PIN2;
        }
        else {
                P6OUT |= GPIO_PIN2;
        }
}

void setWinding2 (int power)
{
        TA0CCR2 = PERIOD - abs (power);
//        TA0CCR2 = 0;

        if (power >= 0) {
                P6OUT &= ~GPIO_PIN3;
        }
        else {
                P6OUT |= GPIO_PIN3;
        }
}

/**
 * Uwaga - mylące nazwy :
 * TAxCTL - główny rejestr kontrolny.
 * TAxCCTL[0-6] - Timer_Ax Capture/Compare Control 0-6
 * TAxCCR[0-6] - Timer_Ax Capture/Compare 0-6. Mają podwójną funkcję. Kiedy pracują jako 'capture', współpracują z jakimś wejściem. Gdy
 *               na tym wejściu pojawi się zdarzenie, wartość z licznika TAxR jest kopiowana do rejestru.
 *               W trybie compare jest odwrotnie. Do rejestrów TAxCCR zapisujemy jakąś wartość, która jest porównywana z licznikiem TAxR.
 *               Gdy są równe, generowane jest zdarzenie (zazwyczaj zmiana stanu jakiegoś wyjścia i/lub przerwanie). W ten sposób generujemy
 *               PWM.
 */
int main (void)
{
#if 0
        //Stop WDT
        WDT_A_hold(WDT_A_BASE);

        //P2.0 as PWM output
        GPIO_setAsPeripheralModuleFunctionOutputPin(
                GPIO_PORT_P2,
                GPIO_PIN0
                );

        //Generate PWM - Timer runs in Up-Down mode
        TIMER_A_generatePWM(TIMER_A1_BASE,
                            TIMER_A_CLOCKSOURCE_SMCLK,
                            TIMER_A_CLOCKSOURCE_DIVIDER_1,
                            TIMER_PERIOD,
                            TIMER_A_CAPTURECOMPARE_REGISTER_1,
                            TIMER_A_OUTPUTMODE_RESET_SET,
                            DUTY_CYCLE
                            );

        //Enter LPM0
        __bis_SR_register(LPM0_bits);

        //For debugger
        __no_operation();
#endif



        //Stop watchdog timer
        WDT_A_hold(WDT_A_BASE);

//        //Set P1.0 to output direction
//        GPIO_setAsOutputPin(
//                GPIO_PORT_P1,
//                GPIO_PIN0
//                );

        //Port select XT1
//        GPIO_setAsPeripheralModuleFunctionInputPin (GPIO_PORT_P5, GPIO_PIN2 | GPIO_PIN3);
//        GPIO_setAsPeripheralModuleFunctionInputPin (GPIO_PORT_P7, GPIO_PIN0 | GPIO_PIN1);

        //Initializes the XT1 crystal oscillator with no timeout
        //In case of failure, code hangs here.
        //For time-out instead of code hang use UCS_LFXT1StartWithTimeout()
//        UCS_LFXT1Start (UCS_XT1_DRIVE0, UCS_XCAP_3);

        UCS_clockSignalInit(
                 UCS_FLLREF,
                 UCS_REFOCLK_SELECT,
                 UCS_CLOCK_DIVIDER_1);

         UCS_clockSignalInit(
                 UCS_ACLK,
                 UCS_REFOCLK_SELECT,
                 UCS_CLOCK_DIVIDER_1);

         UCS_clockSignalInit(
                 UCS_SMCLK,
                 UCS_REFOCLK_SELECT,
                 UCS_CLOCK_DIVIDER_1);

         UCS_initFLLSettle(
                 CLK_FREQ / 1000,
                 CLK_FREQ / 32768);

        // Enable global oscillator fault flag
//        SFR_clearInterrupt (SFR_OSCILLATOR_FAULT_INTERRUPT);
//        SFR_enableInterrupt (SFR_OSCILLATOR_FAULT_INTERRUPT);

        // Enable global interrupt
//        __bis_SR_register (GIE);

//        //Enter LPM3 w/ interrupts
//        __bis_SR_register (LPM3_bits + GIE);
//







#if 1
        // Stop watchdog timer
        WDTCTL = WDTPW | WDTHOLD;
        GPIO_setAsPeripheralModuleFunctionOutputPin (GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3);
        GPIO_setAsOutputPin (GPIO_PORT_P6, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3);

        /*
         * Konfiguracja pierwszego timera typu A. Wybór źródła sygnału zegarowego za pomocą :
         * TASSEL_0 : TAxCLK sygnał zewnętrzny. ?
         * TASSEL_1 : ACLK sygnał wewnętrzny. Auxiliary clock.
         * TASSEL_2 : SMCLK sygnał wewnętrzny. Subsystem master clock.
         * TASSEL_3 : INCLK sygnał zewnętrzny. ?
         *
         */
        TA0CTL |= TASSEL_2 |

        /*
         * Pierwszy divider. Możliwe opcje to:
         * ID_0 : /1
         * ID_1 : /2
         * ID_2 : /4
         * ID_3 : /8
         */
        ID_0 |

        /*
         * Tryb działania
         * Timer mode control: 0 - Stop
         *
         * Timer mode control: 1 - Up to TAxCCR0 i znów od 0. W tym przypadku używany jest tylko TAxCCR0 (Timer_Ax Capture/Compare 0).
         *                         Kiedy timer dojdzie do wartości TAxCCR0, to ustawiany jest bit CCIFG w rejestrze TAxCCTL0. Natomiast
         *                         zaraz potem, kiedy  tylko timer się wyzeruje µC ustawia bit TAIFG w rejestrze TAxCTL (Timer_Ax Control).
         *                         Czyli te zdarzenia następują zaraz po sobie.
         *
         * Timer mode control: 2 - Continuous up, czyli liczy do 0xffff i znów od zera. Kiedy dojdzie do 0xffff, to ustawia TAIFG w TAxCTL
         *                         (Timer_Ax Control), tak samo jak w poprzednim wypadku.
         *
         * Timer mode control: 3 - Up/Down, cyzli od 0 do TAxCCR0 i potem do 0 i w kółko.
         *
         */
        MC_1;

        /*
         * Dalszy podział sygnału zegarowego. Możliwe wartości:
         * TAIDEX_0 : /1
         * TAIDEX_1 : /2
         * TAIDEX_2 : /3
         * TAIDEX_3 : /4
         * TAIDEX_4 : /5
         * TAIDEX_5 : /6
         * TAIDEX_6 : /7
         * TAIDEX_7 : /8
         */
        TA0EX0 = TAIDEX_0;

        // Można ustawić aktualny stan timera, ale nie trzeba.
        TA0R = 0;

        /*
         * Reset timera. Zawsze wykonać po ustawieniu dzielników sygnału zegarowego.
         */
        TA0CTL |= TACLR;


/*---------------------------------------------------------------------------*/

        TA0CCR0 = PERIOD;

        TA0CCR1 = (PERIOD / 2);
        TA0CCTL1 |= OUTMOD_3; // Toggle


        TA0CCR2 = (PERIOD / 2);
        TA0CCTL2 |= OUTMOD_3; // Toggle


//        //Enter LPM0
//        __bis_SR_register(LPM0_bits);
//
//        //For debugger
//        __no_operation();

//        GPIO_setAsOutputPin (GPIO_PORT_P1, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3);


        while (1) {

                for (int j = 0; j < STEPS; ++j) {

                        setWinding1 (COSINE[j]);
                        setWinding2 (SINE[j]);

                        // Delay
                        for (int i = 0; i < 128; ++i)
                                ;
                }
        }
//
//
//
////        P1DIR |= 0x01;                                  // Set P1.0 to output direction
////
////
////        for(;;) {
////                volatile unsigned int i;        // volatile to prevent optimization
////
////                P6OUT = GPIO_PIN0 | GPIO_PIN2 | GPIO_PIN3;
////                for (i = 0; i < 10000; ++i);
////                P6OUT = GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3;
////                for (i = 0; i < 10000; ++i);
////                P6OUT = GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3;
////                for (i = 0; i < 10000; ++i);
////                P6OUT =  GPIO_PIN2 | GPIO_PIN3;
////                for (i = 0; i < 10000; ++i);
////        }
//
//        return 0;
#endif
}


