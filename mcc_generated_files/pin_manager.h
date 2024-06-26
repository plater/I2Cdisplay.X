/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.4
        Device            :  PIC18F47K40
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.20 and above
        MPLAB 	          :  MPLAB X 5.40	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SERVICE aliases
#define SERVICE_TRIS                 TRISAbits.TRISA0
#define SERVICE_LAT                  LATAbits.LATA0
#define SERVICE_PORT                 PORTAbits.RA0
#define SERVICE_WPU                  WPUAbits.WPUA0
#define SERVICE_OD                   ODCONAbits.ODCA0
#define SERVICE_ANS                  ANSELAbits.ANSELA0
#define SERVICE_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define SERVICE_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define SERVICE_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define SERVICE_GetValue()           PORTAbits.RA0
#define SERVICE_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define SERVICE_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define SERVICE_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define SERVICE_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define SERVICE_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define SERVICE_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define SERVICE_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define SERVICE_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set STOCK1 aliases
#define STOCK1_TRIS                 TRISAbits.TRISA1
#define STOCK1_LAT                  LATAbits.LATA1
#define STOCK1_PORT                 PORTAbits.RA1
#define STOCK1_WPU                  WPUAbits.WPUA1
#define STOCK1_OD                   ODCONAbits.ODCA1
#define STOCK1_ANS                  ANSELAbits.ANSELA1
#define STOCK1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define STOCK1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define STOCK1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define STOCK1_GetValue()           PORTAbits.RA1
#define STOCK1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define STOCK1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define STOCK1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define STOCK1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define STOCK1_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define STOCK1_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define STOCK1_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define STOCK1_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set STOCK2 aliases
#define STOCK2_TRIS                 TRISAbits.TRISA2
#define STOCK2_LAT                  LATAbits.LATA2
#define STOCK2_PORT                 PORTAbits.RA2
#define STOCK2_WPU                  WPUAbits.WPUA2
#define STOCK2_OD                   ODCONAbits.ODCA2
#define STOCK2_ANS                  ANSELAbits.ANSELA2
#define STOCK2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define STOCK2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define STOCK2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define STOCK2_GetValue()           PORTAbits.RA2
#define STOCK2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define STOCK2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define STOCK2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define STOCK2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define STOCK2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define STOCK2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define STOCK2_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define STOCK2_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set STOCK3 aliases
#define STOCK3_TRIS                 TRISAbits.TRISA3
#define STOCK3_LAT                  LATAbits.LATA3
#define STOCK3_PORT                 PORTAbits.RA3
#define STOCK3_WPU                  WPUAbits.WPUA3
#define STOCK3_OD                   ODCONAbits.ODCA3
#define STOCK3_ANS                  ANSELAbits.ANSELA3
#define STOCK3_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define STOCK3_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define STOCK3_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define STOCK3_GetValue()           PORTAbits.RA3
#define STOCK3_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define STOCK3_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define STOCK3_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define STOCK3_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define STOCK3_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define STOCK3_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define STOCK3_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define STOCK3_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set STOCK4 aliases
#define STOCK4_TRIS                 TRISAbits.TRISA4
#define STOCK4_LAT                  LATAbits.LATA4
#define STOCK4_PORT                 PORTAbits.RA4
#define STOCK4_WPU                  WPUAbits.WPUA4
#define STOCK4_OD                   ODCONAbits.ODCA4
#define STOCK4_ANS                  ANSELAbits.ANSELA4
#define STOCK4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define STOCK4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define STOCK4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define STOCK4_GetValue()           PORTAbits.RA4
#define STOCK4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define STOCK4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define STOCK4_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define STOCK4_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define STOCK4_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define STOCK4_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define STOCK4_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define STOCK4_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set GLED aliases
#define GLED_TRIS                 TRISAbits.TRISA6
#define GLED_LAT                  LATAbits.LATA6
#define GLED_PORT                 PORTAbits.RA6
#define GLED_WPU                  WPUAbits.WPUA6
#define GLED_OD                   ODCONAbits.ODCA6
#define GLED_ANS                  ANSELAbits.ANSELA6
#define GLED_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define GLED_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define GLED_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define GLED_GetValue()           PORTAbits.RA6
#define GLED_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define GLED_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define GLED_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define GLED_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define GLED_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define GLED_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define GLED_SetAnalogMode()      do { ANSELAbits.ANSELA6 = 1; } while(0)
#define GLED_SetDigitalMode()     do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set RLED aliases
#define RLED_TRIS                 TRISAbits.TRISA7
#define RLED_LAT                  LATAbits.LATA7
#define RLED_PORT                 PORTAbits.RA7
#define RLED_WPU                  WPUAbits.WPUA7
#define RLED_OD                   ODCONAbits.ODCA7
#define RLED_ANS                  ANSELAbits.ANSELA7
#define RLED_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define RLED_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define RLED_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define RLED_GetValue()           PORTAbits.RA7
#define RLED_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define RLED_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define RLED_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define RLED_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define RLED_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define RLED_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define RLED_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define RLED_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set VEND1 aliases
#define VEND1_TRIS                 TRISBbits.TRISB0
#define VEND1_LAT                  LATBbits.LATB0
#define VEND1_PORT                 PORTBbits.RB0
#define VEND1_WPU                  WPUBbits.WPUB0
#define VEND1_OD                   ODCONBbits.ODCB0
#define VEND1_ANS                  ANSELBbits.ANSELB0
#define VEND1_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define VEND1_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define VEND1_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define VEND1_GetValue()           PORTBbits.RB0
#define VEND1_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define VEND1_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define VEND1_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define VEND1_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define VEND1_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define VEND1_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define VEND1_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define VEND1_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set VEND2 aliases
#define VEND2_TRIS                 TRISBbits.TRISB1
#define VEND2_LAT                  LATBbits.LATB1
#define VEND2_PORT                 PORTBbits.RB1
#define VEND2_WPU                  WPUBbits.WPUB1
#define VEND2_OD                   ODCONBbits.ODCB1
#define VEND2_ANS                  ANSELBbits.ANSELB1
#define VEND2_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define VEND2_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define VEND2_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define VEND2_GetValue()           PORTBbits.RB1
#define VEND2_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define VEND2_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define VEND2_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define VEND2_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define VEND2_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define VEND2_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define VEND2_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define VEND2_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set VEND3 aliases
#define VEND3_TRIS                 TRISBbits.TRISB2
#define VEND3_LAT                  LATBbits.LATB2
#define VEND3_PORT                 PORTBbits.RB2
#define VEND3_WPU                  WPUBbits.WPUB2
#define VEND3_OD                   ODCONBbits.ODCB2
#define VEND3_ANS                  ANSELBbits.ANSELB2
#define VEND3_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define VEND3_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define VEND3_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define VEND3_GetValue()           PORTBbits.RB2
#define VEND3_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define VEND3_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define VEND3_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define VEND3_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define VEND3_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define VEND3_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define VEND3_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define VEND3_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set VEND4 aliases
#define VEND4_TRIS                 TRISBbits.TRISB3
#define VEND4_LAT                  LATBbits.LATB3
#define VEND4_PORT                 PORTBbits.RB3
#define VEND4_WPU                  WPUBbits.WPUB3
#define VEND4_OD                   ODCONBbits.ODCB3
#define VEND4_ANS                  ANSELBbits.ANSELB3
#define VEND4_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define VEND4_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define VEND4_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define VEND4_GetValue()           PORTBbits.RB3
#define VEND4_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define VEND4_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define VEND4_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define VEND4_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define VEND4_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define VEND4_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define VEND4_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define VEND4_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set PWR aliases
#define PWR_TRIS                 TRISCbits.TRISC3
#define PWR_LAT                  LATCbits.LATC3
#define PWR_PORT                 PORTCbits.RC3
#define PWR_WPU                  WPUCbits.WPUC3
#define PWR_OD                   ODCONCbits.ODCC3
#define PWR_ANS                  ANSELCbits.ANSELC3
#define PWR_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define PWR_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define PWR_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define PWR_GetValue()           PORTCbits.RC3
#define PWR_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define PWR_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define PWR_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define PWR_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define PWR_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define PWR_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define PWR_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define PWR_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSELC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSELC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RD0 procedures
#define RD0_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define RD0_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define RD0_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define RD0_GetValue()              PORTDbits.RD0
#define RD0_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define RD0_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define RD0_SetPullup()             do { WPUDbits.WPUD0 = 1; } while(0)
#define RD0_ResetPullup()           do { WPUDbits.WPUD0 = 0; } while(0)
#define RD0_SetAnalogMode()         do { ANSELDbits.ANSELD0 = 1; } while(0)
#define RD0_SetDigitalMode()        do { ANSELDbits.ANSELD0 = 0; } while(0)

// get/set RD1 aliases
#define RD1_TRIS                 TRISDbits.TRISD1
#define RD1_LAT                  LATDbits.LATD1
#define RD1_PORT                 PORTDbits.RD1
#define RD1_WPU                  WPUDbits.WPUD1
#define RD1_OD                   ODCONDbits.ODCD1
#define RD1_ANS                  ANSELDbits.ANSELD1
#define RD1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define RD1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define RD1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define RD1_GetValue()           PORTDbits.RD1
#define RD1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define RD1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define RD1_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define RD1_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define RD1_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define RD1_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define RD1_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define RD1_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set RD2 aliases
#define RD2_TRIS                 TRISDbits.TRISD2
#define RD2_LAT                  LATDbits.LATD2
#define RD2_PORT                 PORTDbits.RD2
#define RD2_WPU                  WPUDbits.WPUD2
#define RD2_OD                   ODCONDbits.ODCD2
#define RD2_ANS                  ANSELDbits.ANSELD2
#define RD2_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define RD2_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define RD2_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define RD2_GetValue()           PORTDbits.RD2
#define RD2_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define RD2_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define RD2_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define RD2_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define RD2_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define RD2_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define RD2_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define RD2_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set RD3 aliases
#define RD3_TRIS                 TRISDbits.TRISD3
#define RD3_LAT                  LATDbits.LATD3
#define RD3_PORT                 PORTDbits.RD3
#define RD3_WPU                  WPUDbits.WPUD3
#define RD3_OD                   ODCONDbits.ODCD3
#define RD3_ANS                  ANSELDbits.ANSELD3
#define RD3_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define RD3_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define RD3_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define RD3_GetValue()           PORTDbits.RD3
#define RD3_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define RD3_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define RD3_SetPullup()          do { WPUDbits.WPUD3 = 1; } while(0)
#define RD3_ResetPullup()        do { WPUDbits.WPUD3 = 0; } while(0)
#define RD3_SetPushPull()        do { ODCONDbits.ODCD3 = 0; } while(0)
#define RD3_SetOpenDrain()       do { ODCONDbits.ODCD3 = 1; } while(0)
#define RD3_SetAnalogMode()      do { ANSELDbits.ANSELD3 = 1; } while(0)
#define RD3_SetDigitalMode()     do { ANSELDbits.ANSELD3 = 0; } while(0)

// get/set RD4 aliases
#define RD4_TRIS                 TRISDbits.TRISD4
#define RD4_LAT                  LATDbits.LATD4
#define RD4_PORT                 PORTDbits.RD4
#define RD4_WPU                  WPUDbits.WPUD4
#define RD4_OD                   ODCONDbits.ODCD4
#define RD4_ANS                  ANSELDbits.ANSELD4
#define RD4_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define RD4_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define RD4_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define RD4_GetValue()           PORTDbits.RD4
#define RD4_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define RD4_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define RD4_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define RD4_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define RD4_SetPushPull()        do { ODCONDbits.ODCD4 = 0; } while(0)
#define RD4_SetOpenDrain()       do { ODCONDbits.ODCD4 = 1; } while(0)
#define RD4_SetAnalogMode()      do { ANSELDbits.ANSELD4 = 1; } while(0)
#define RD4_SetDigitalMode()     do { ANSELDbits.ANSELD4 = 0; } while(0)

// get/set RD5 aliases
#define RD5_TRIS                 TRISDbits.TRISD5
#define RD5_LAT                  LATDbits.LATD5
#define RD5_PORT                 PORTDbits.RD5
#define RD5_WPU                  WPUDbits.WPUD5
#define RD5_OD                   ODCONDbits.ODCD5
#define RD5_ANS                  ANSELDbits.ANSELD5
#define RD5_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define RD5_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define RD5_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define RD5_GetValue()           PORTDbits.RD5
#define RD5_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define RD5_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define RD5_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define RD5_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define RD5_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define RD5_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define RD5_SetAnalogMode()      do { ANSELDbits.ANSELD5 = 1; } while(0)
#define RD5_SetDigitalMode()     do { ANSELDbits.ANSELD5 = 0; } while(0)

// get/set CS1 aliases
#define CS1_TRIS                 TRISDbits.TRISD6
#define CS1_LAT                  LATDbits.LATD6
#define CS1_PORT                 PORTDbits.RD6
#define CS1_WPU                  WPUDbits.WPUD6
#define CS1_OD                   ODCONDbits.ODCD6
#define CS1_ANS                  ANSELDbits.ANSELD6
#define CS1_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define CS1_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define CS1_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define CS1_GetValue()           PORTDbits.RD6
#define CS1_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define CS1_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define CS1_SetPullup()          do { WPUDbits.WPUD6 = 1; } while(0)
#define CS1_ResetPullup()        do { WPUDbits.WPUD6 = 0; } while(0)
#define CS1_SetPushPull()        do { ODCONDbits.ODCD6 = 0; } while(0)
#define CS1_SetOpenDrain()       do { ODCONDbits.ODCD6 = 1; } while(0)
#define CS1_SetAnalogMode()      do { ANSELDbits.ANSELD6 = 1; } while(0)
#define CS1_SetDigitalMode()     do { ANSELDbits.ANSELD6 = 0; } while(0)

// get/set SS_A0 aliases
#define SS_A0_TRIS                 TRISDbits.TRISD7
#define SS_A0_LAT                  LATDbits.LATD7
#define SS_A0_PORT                 PORTDbits.RD7
#define SS_A0_WPU                  WPUDbits.WPUD7
#define SS_A0_OD                   ODCONDbits.ODCD7
#define SS_A0_ANS                  ANSELDbits.ANSELD7
#define SS_A0_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define SS_A0_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define SS_A0_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define SS_A0_GetValue()           PORTDbits.RD7
#define SS_A0_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define SS_A0_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define SS_A0_SetPullup()          do { WPUDbits.WPUD7 = 1; } while(0)
#define SS_A0_ResetPullup()        do { WPUDbits.WPUD7 = 0; } while(0)
#define SS_A0_SetPushPull()        do { ODCONDbits.ODCD7 = 0; } while(0)
#define SS_A0_SetOpenDrain()       do { ODCONDbits.ODCD7 = 1; } while(0)
#define SS_A0_SetAnalogMode()      do { ANSELDbits.ANSELD7 = 1; } while(0)
#define SS_A0_SetDigitalMode()     do { ANSELDbits.ANSELD7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/