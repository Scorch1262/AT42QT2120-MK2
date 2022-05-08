#define FCY 16000000UL 
#include <assert.h>
#include <stdbool.h>
#include "mcc_generated_files/system.h"
#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include <xc.h>
#include <string.h>
#include "mcc_generated_files/i2c1.h"
#include "at42qt2120.h"

#if defined(__dsPIC33E__)
	#include <p33exxxx.h>
#elif defined(__dsPIC33F__)
	#include <p33fxxxx.h>
#elif defined(__dsPIC30F__)
	#include <p30fxxxx.h>
#elif defined(__PIC24E__)
	#include <p24exxxx.h>
#elif defined(__PIC24H__)
	#include <p24hxxxx.h>
#elif defined(__PIC24F__) || defined(__PIC24FK__)
	#include <p24fxxxx.h>
#endif

uint8_t Slider_pos;                                     // definiert "Slider_pos"
    
/*
                         Main application
 */
int main(void){                                         // "main"
    SYSTEM_Initialize();                                // ruft "SYSTEM_Initialize" auf
    __delay_ms(500);                                    // warte 500ms
    AT42QT2120_Init();                                  // ruft "AT42QT2120_Init" auf
    
    while(1){                                           // Endloschleife
        Slider_pos = AT42QT2120_sliderPosition();       // schreibt "AT42QT2120_sliderPosition" in "Slider_pos"
        printf("Slider = %d\r\n",Slider_pos);           // schreibt den Inhalt von ""Slider = %d\r\n" an UART
        __delay_ms(500);                                // warte 500ms
    }                                                   // 
}                                                       // 
    
