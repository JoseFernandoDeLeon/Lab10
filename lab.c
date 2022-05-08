/*
 * Archivo: lab.c
 * Dispositivo: PIC16F887
 * Compilador:  XC8, MPLABX v5.40
 * Autor: José Fernando de León González
 * Programa: Comunicación serial EUSART, Reloj de 1 MHz y baud rate de 9600
 * Hardware: Valor recibido en el seríal (RCREG) se muestra en el PORTD
 * 
 * Creado: 2/05/22
 * Última modificación: 2/05/22
 */

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>



/*------------------------------------------------------------------------------
 * Constantes
------------------------------------------------------------------------------*/
#define _XTAL_FREQ 1000000


/*------------------------------------------------------------------------------
 * Variables
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 * Prototipos de funciones
------------------------------------------------------------------------------*/
void setup (void);
void Print (unsigned char *word);

/*------------------------------------------------------------------------------
 * Interrupciones
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * Ciclo principal
------------------------------------------------------------------------------*/
void main(void) {
    setup();
    while(1){
        __delay_us(1000);
        Print("Hola mundo");
    }      
    return;
}

/*------------------------------------------------------------------------------
 * Configuración
------------------------------------------------------------------------------*/
void setup (void){
    
    // Configuración de los puertos
    ANSEL = 0;                  //I/O digitales
    ANSELH = 0;
    
    
    TRISD = 0;                  // PORTD como salida 
    PORTD = 0;                  // Limpiamos PORTD
    
    // Configuración del oscilador
    OSCCONbits.IRCF = 0b0100;    // IRCF <2:0> -> 100 1 MHz
    OSCCONbits.SCS = 1;         // Oscilador interno
    
    // Configuraciones de comunicacion serial
    //SYNC = 0, BRGH = 1, BRG16 = 1, SPBRG=25 <- Valores de tabla 12-5
    TXSTAbits.SYNC = 0;         // Comunicación ascincrona (full-duplex)
    TXSTAbits.BRGH = 1;         // Baud rate de alta velocidad 
    BAUDCTLbits.BRG16 = 1;      // 16-bits para generar el baud rate
    
    SPBRG = 25;
    SPBRGH = 0;                 // Baud rate ~9600, error -> 0.16%
    
    RCSTAbits.SPEN = 1;         // Habilitamos comunicación
    TXSTAbits.TX9 = 0;          // Utilizamos solo 8 bits
    TXSTAbits.TXEN = 1;         // Habilitamos transmisor
    
    
    

    
    
   
}
/*------------------------------------------------------------------------------
 * Funciones
------------------------------------------------------------------------------*/

void Print (unsigned char *word)
{
while (*word != '\0')
{
    while (TXIF != 1);
    TXREG = *word;
    *word++;
}
return;    
}