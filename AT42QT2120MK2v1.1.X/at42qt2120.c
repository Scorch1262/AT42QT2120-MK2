#define FCY 16000000UL

#include "xc.h"
#include <assert.h>
#include <stdbool.h>
#include <libpic30.h>
#include <stdint.h>
#include "mcc_generated_files/system.h"
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

#define AT42QT2120_ADDR         0x1C

#define Chip_ID                 0
#define Firmware_Version        1
#define Detection_Status        2
#define Key_Status_MSB          3
#define Slider_Position         5
#define Calibrate               6
#define Reset                   7
#define LP                      8
#define TTD                     9
#define ATD                     10
#define DI                      11
#define TRD                     12
#define DHT                     13
#define Slider_Options          14
#define Charge_Time             15
#define Key_0_Detect_Threshold  16
#define Key_1_Detect_Threshold  17
#define Kev_2_Detect_Threshold  18
#define Key_3_Detect_Threshold  19
#define Key_4_Detect_Threshold  20
#define Key_5_Detect_Threshold  21
#define Key_6_Detect_Threshold  22
#define Key_7_Detect_Threshold  23
#define Key_8_Detect_Threshold  24
#define Key_9_Detect_Threshold  25
#define Key_10_Detect_Threshold 26
#define Key_11_Detect_Threshold 27
#define Kev_O_Control           28
#define Key_1_Control           29
#define Kev_2_Control           30
#define Key_3_Control           31
#define Key_4_Contral           32
#define Key_5_Control           33
#define Key_6_Control           34
#define Key_7_Control           35
#define Key_8_Control           36
#define Key_9_Control           37
#define Key_10_Control          38
#define Key_11_Control          39
#define Key_0_Pulse_Scale       40
#define Key_1_Pulse_Scale       41
#define Key_2_Pulse_Scale       42
#define Key_3_Pulse_Scale       43
#define Key_4_Pulse_Scale       44
#define Key_5_Pulse_Scale       45
#define Key_6_Pulse_Scale       46
#define Key_7_Pulse_Scale       47
#define Key_8_Pulse_Scale       48
#define Key_9_Pulse_Scale       49
#define Key_10_Pulse_Scale      50
#define Key_11_Pulse_Scale      51
#define Key_Signal_0_MSB        52
#define Key_Signal_1_MSB        54
#define Key_Signal_2_MSB        56
#define Kev_Signal_3_MSB        58
#define Key_Signal_4_MSB        60
#define Key_Signal_5_MSB        62
#define Key_Signal_6_MSB        64
#define Key_Signal_7_MSB        66
#define Key_Signal_8_MSB        68
#define Key_Signal_9_MSB        70
#define Key_Signal_10_MSB       72
#define Key_Signal_11_MSB       74
#define Reference_Data_0_MSB    76
#define Reference_Data_1_MSB    78
#define Reference_Data_2_MSB    80
#define Reference_Data_3_MSB    82
#define Reference_Data_4_MSB    84
#define Reference_Data_5_MSB    86
#define Reference_Data_6_MSB    88
#define Reference_Data_7_MSB    90
#define Reference_Data_8_MSB    92
#define Reference_Data_9_MSB    94
#define Reference_Data_10_MSB   96
#define Reference_Data_11_MSB   98

I2C1_MESSAGE_STATUS status;                                             // 

uint8_t Slave_Address;                                                  // definiert "Slave_Address" 

uint8_t  writeBuffer[3] = {0x00, 0x00, 0x00};                           // definiert "writeBuffer"
uint8_t  readBuffer[10] = {0x00, 0x00, 0x00};                           // definiert "readBuffer" 
uint16_t retryTimeOut1;                                                 // definiert "retryTimeOut1" 
uint16_t retryTimeOut2;                                                 // definiert "retryTimeOut2" 

void AT42QT2120_Init(void){                                             // "AT42QT2120_Init"
    AT42QT2120_enableSlider();                                          // ruft "AT42QT2120_enableSlider" auf
}                                                                       // 

void AT42QT2120_enableSlider(void){                                     // "AT42QT2120_enableSlider"
    Slave_Address = AT42QT2120_ADDR;                                    // schreibt "AT42QT2120_ADDR" in "Slave_Address"   
    
    writeBuffer[0] = Slider_Options;                                    // schreibt "Slider_Options" in "writeBuffer[0]"
    writeBuffer[1] = 0x80;                                              // schreibt "0x80" in "writeBuffer[0]"
    I2C1_MasterWrite(&writeBuffer[0], 2, Slave_Address, &status);       // schreibt 2 Byte (writeBuffer[0]) an I2C1
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
}                                                                       // 

void AT42QT2120_enableWheel(void){                                      // "AT42QT2120_enableWheel"
    Slave_Address = AT42QT2120_ADDR;                                    // schreibt "AT42QT2120_ADDR" in "Slave_Address"   
    
    writeBuffer[0] = Slider_Options;                                    // schreibt "Slider_Options" in "writeBuffer[0]"
    writeBuffer[1] = 0xC0;                                              // schreibt "0xC0" in "writeBuffer[0]"
    I2C1_MasterWrite(&writeBuffer[0], 2, Slave_Address, &status);       // schreibt 2 Byte (writeBuffer[0]) an I2C1
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
}                                                                       // 

uint8_t AT42QT2120_sliderPosition(void){                                // "AT42QT2120_sliderPosition"
    Slave_Address = AT42QT2120_ADDR;                                    // schreibt "AT42QT2120_ADDR" in "Slave_Address"   
    
    writeBuffer[0] = Detection_Status;                                  // schreibt "Detection_Status" in "writeBuffer[0]"
    I2C1_MasterWrite(&writeBuffer[0], 1, Slave_Address, &status);       // schreibt 1 Byte (writeBuffer[0]) an I2C1
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf   
    I2C1_MasterRead(&readBuffer[0], 1, Slave_Address, &status);         // liest von I2C1 in 1 Byte (readBuffer[0]) 
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf
    
    if((readBuffer[0] & 0b00000001) == 0b00000001){                     // wenn "readBuffer[0]" maskiert mit "0b00000001" gleich "0b00000001" ist
        writeBuffer[0] = Slider_Position;                               // schreibt "Slider_Position" in "writeBuffer[0]"
        I2C1_MasterWrite(&writeBuffer[0], 1, Slave_Address, &status);   // schreibt 1 Byte (writeBuffer[0]) an I2C1
        i2c1_message_pending_100();                                     // ruft "i2c1_message_pending_100" auf   
        I2C1_MasterRead(&readBuffer[0], 1, Slave_Address, &status);     // liest von I2C1 in 1 Byte (readBuffer[0]) 
        i2c1_message_pending_100();                                     // ruft "i2c1_message_pending_100" auf

        return readBuffer[0];                                           // gibt "readBuffer[0]" zurück
    }                                                                   // 
}                                                                       // 

uint8_t AT42QT2120_wheelPosition(void){                                 // "AT42QT2120_wheelPosition"
    Slave_Address = AT42QT2120_ADDR;                                    // schreibt "AT42QT2120_ADDR" in "Slave_Address"   
    
    writeBuffer[0] = Detection_Status;                                  // schreibt "Detection_Status" in "writeBuffer[0]"
    I2C1_MasterWrite(&writeBuffer[0], 1, Slave_Address, &status);       // schreibt 1 Byte (writeBuffer[0]) an I2C1
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf   
    I2C1_MasterRead(&readBuffer[0], 1, Slave_Address, &status);         // liest von I2C1 in 1 Byte (readBuffer[0]) 
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf
    
    if((readBuffer[0] & 0b00000001) == 0b00000001){                     // wenn "readBuffer[0]" maskiert mit "0b00000001" gleich "0b00000001" ist
        writeBuffer[0] = Slider_Position;                               // schreibt "Slider_Position" in "writeBuffer[0]"
        I2C1_MasterWrite(&writeBuffer[0], 1, Slave_Address, &status);   // schreibt 1 Byte (writeBuffer[0]) an I2C1
        i2c1_message_pending_100();                                     // ruft "i2c1_message_pending_100" auf   
        I2C1_MasterRead(&readBuffer[0], 1, Slave_Address, &status);     // liest von I2C1 in 1 Byte (readBuffer[0]) 
        i2c1_message_pending_100();                                     // ruft "i2c1_message_pending_100" auf

        return readBuffer[0];                                           // gibt "readBuffer[0]" zurück
    }                                                                   // 
}                                                                       // 

void i2c1_message_pending_100(void){                                    // "i2c1_message_pending_100"
    retryTimeOut1 = 0;                                                  // setzt "retryTimeOut1" auf 0
    retryTimeOut2 = 0;                                                  // setzt "retryTimeOut2" auf 0
    while(status == I2C1_MESSAGE_PENDING){                              // solange "status" gleich "I2C1_MESSAGE_PENDING" ist
        if (retryTimeOut2 == 1000){                                      // wenn "retryTimeOut2" gleich 100 ist
            break;                                                      // Abbruch der Schleife
        }else{                                                          // sonst
            retryTimeOut2++;                                            // "retryTimeOut2" +1
        }                                                               // 
    }
    while(status != I2C1_MESSAGE_FAIL){                                 // solange "status" nicht gleich "I2C1_MESSAGE_FAIL" ist
        if (retryTimeOut1 == 1000){                                      // wenn "retryTimeOut1" gleich 100 ist
            break;                                                      // Abbruch der Schleife
        }else{                                                          // sonst
            retryTimeOut1++;                                            // "retryTimeOut1" +1
        }                                                               // 
    }                                                                   // 
}                                                                       // 





