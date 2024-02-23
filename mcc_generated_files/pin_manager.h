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

// get/set LED1 aliases
#define LED1_TRIS                 TRISAbits.TRISA1
#define LED1_LAT                  LATAbits.LATA1
#define LED1_PORT                 PORTAbits.RA1
#define LED1_WPU                  WPUAbits.WPUA1
#define LED1_OD                   ODCONAbits.ODCA1
#define LED1_ANS                  ANSELAbits.ANSELA1
#define LED1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define LED1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define LED1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define LED1_GetValue()           PORTAbits.RA1
#define LED1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define LED1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define LED1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define LED1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define LED1_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define LED1_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define LED1_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define LED1_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set LED2 aliases
#define LED2_TRIS                 TRISAbits.TRISA2
#define LED2_LAT                  LATAbits.LATA2
#define LED2_PORT                 PORTAbits.RA2
#define LED2_WPU                  WPUAbits.WPUA2
#define LED2_OD                   ODCONAbits.ODCA2
#define LED2_ANS                  ANSELAbits.ANSELA2
#define LED2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LED2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LED2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define LED2_GetValue()           PORTAbits.RA2
#define LED2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LED2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define LED2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define LED2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define LED2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define LED2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define LED2_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define LED2_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set LED3 aliases
#define LED3_TRIS                 TRISAbits.TRISA3
#define LED3_LAT                  LATAbits.LATA3
#define LED3_PORT                 PORTAbits.RA3
#define LED3_WPU                  WPUAbits.WPUA3
#define LED3_OD                   ODCONAbits.ODCA3
#define LED3_ANS                  ANSELAbits.ANSELA3
#define LED3_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define LED3_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define LED3_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define LED3_GetValue()           PORTAbits.RA3
#define LED3_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define LED3_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define LED3_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define LED3_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define LED3_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define LED3_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define LED3_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define LED3_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set LED4 aliases
#define LED4_TRIS                 TRISAbits.TRISA4
#define LED4_LAT                  LATAbits.LATA4
#define LED4_PORT                 PORTAbits.RA4
#define LED4_WPU                  WPUAbits.WPUA4
#define LED4_OD                   ODCONAbits.ODCA4
#define LED4_ANS                  ANSELAbits.ANSELA4
#define LED4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define LED4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define LED4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define LED4_GetValue()           PORTAbits.RA4
#define LED4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define LED4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define LED4_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define LED4_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define LED4_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define LED4_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define LED4_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define LED4_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set STOCK1a aliases
#define STOCK1a_TRIS                 TRISAbits.TRISA5
#define STOCK1a_LAT                  LATAbits.LATA5
#define STOCK1a_PORT                 PORTAbits.RA5
#define STOCK1a_WPU                  WPUAbits.WPUA5
#define STOCK1a_OD                   ODCONAbits.ODCA5
#define STOCK1a_ANS                  ANSELAbits.ANSELA5
#define STOCK1a_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define STOCK1a_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define STOCK1a_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define STOCK1a_GetValue()           PORTAbits.RA5
#define STOCK1a_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define STOCK1a_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define STOCK1a_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define STOCK1a_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define STOCK1a_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define STOCK1a_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define STOCK1a_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define STOCK1a_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

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

// get/set STOCK4 aliases
#define STOCK4_TRIS                 TRISBbits.TRISB4
#define STOCK4_LAT                  LATBbits.LATB4
#define STOCK4_PORT                 PORTBbits.RB4
#define STOCK4_WPU                  WPUBbits.WPUB4
#define STOCK4_OD                   ODCONBbits.ODCB4
#define STOCK4_ANS                  ANSELBbits.ANSELB4
#define STOCK4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define STOCK4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define STOCK4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define STOCK4_GetValue()           PORTBbits.RB4
#define STOCK4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define STOCK4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define STOCK4_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define STOCK4_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define STOCK4_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define STOCK4_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define STOCK4_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define STOCK4_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set STOCK3 aliases
#define STOCK3_TRIS                 TRISBbits.TRISB5
#define STOCK3_LAT                  LATBbits.LATB5
#define STOCK3_PORT                 PORTBbits.RB5
#define STOCK3_WPU                  WPUBbits.WPUB5
#define STOCK3_OD                   ODCONBbits.ODCB5
#define STOCK3_ANS                  ANSELBbits.ANSELB5
#define STOCK3_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define STOCK3_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define STOCK3_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define STOCK3_GetValue()           PORTBbits.RB5
#define STOCK3_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define STOCK3_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define STOCK3_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define STOCK3_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define STOCK3_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define STOCK3_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define STOCK3_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define STOCK3_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set GALED aliases
#define GALED_TRIS                 TRISCbits.TRISC0
#define GALED_LAT                  LATCbits.LATC0
#define GALED_PORT                 PORTCbits.RC0
#define GALED_WPU                  WPUCbits.WPUC0
#define GALED_OD                   ODCONCbits.ODCC0
#define GALED_ANS                  ANSELCbits.ANSELC0
#define GALED_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define GALED_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define GALED_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define GALED_GetValue()           PORTCbits.RC0
#define GALED_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define GALED_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define GALED_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define GALED_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define GALED_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define GALED_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define GALED_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define GALED_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

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

// get/set STOCK1 aliases
#define STOCK1_TRIS                 TRISCbits.TRISC6
#define STOCK1_LAT                  LATCbits.LATC6
#define STOCK1_PORT                 PORTCbits.RC6
#define STOCK1_WPU                  WPUCbits.WPUC6
#define STOCK1_OD                   ODCONCbits.ODCC6
#define STOCK1_ANS                  ANSELCbits.ANSELC6
#define STOCK1_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define STOCK1_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define STOCK1_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define STOCK1_GetValue()           PORTCbits.RC6
#define STOCK1_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define STOCK1_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define STOCK1_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define STOCK1_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define STOCK1_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define STOCK1_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define STOCK1_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define STOCK1_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set STOCK2 aliases
#define STOCK2_TRIS                 TRISCbits.TRISC7
#define STOCK2_LAT                  LATCbits.LATC7
#define STOCK2_PORT                 PORTCbits.RC7
#define STOCK2_WPU                  WPUCbits.WPUC7
#define STOCK2_OD                   ODCONCbits.ODCC7
#define STOCK2_ANS                  ANSELCbits.ANSELC7
#define STOCK2_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define STOCK2_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define STOCK2_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define STOCK2_GetValue()           PORTCbits.RC7
#define STOCK2_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define STOCK2_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define STOCK2_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define STOCK2_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define STOCK2_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define STOCK2_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define STOCK2_SetAnalogMode()      do { ANSELCbits.ANSELC7 = 1; } while(0)
#define STOCK2_SetDigitalMode()     do { ANSELCbits.ANSELC7 = 0; } while(0)

// get/set RD0 aliases
#define RD0_TRIS                 TRISDbits.TRISD0
#define RD0_LAT                  LATDbits.LATD0
#define RD0_PORT                 PORTDbits.RD0
#define RD0_WPU                  WPUDbits.WPUD0
#define RD0_OD                   ODCONDbits.ODCD0
#define RD0_ANS                  ANSELDbits.ANSELD0
#define RD0_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define RD0_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define RD0_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define RD0_GetValue()           PORTDbits.RD0
#define RD0_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define RD0_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define RD0_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define RD0_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define RD0_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define RD0_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define RD0_SetAnalogMode()      do { ANSELDbits.ANSELD0 = 1; } while(0)
#define RD0_SetDigitalMode()     do { ANSELDbits.ANSELD0 = 0; } while(0)

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

// get/set RD2 procedures
#define RD2_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define RD2_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define RD2_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define RD2_GetValue()              PORTDbits.RD2
#define RD2_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define RD2_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define RD2_SetPullup()             do { WPUDbits.WPUD2 = 1; } while(0)
#define RD2_ResetPullup()           do { WPUDbits.WPUD2 = 0; } while(0)
#define RD2_SetAnalogMode()         do { ANSELDbits.ANSELD2 = 1; } while(0)
#define RD2_SetDigitalMode()        do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set RD3 procedures
#define RD3_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define RD3_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define RD3_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define RD3_GetValue()              PORTDbits.RD3
#define RD3_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define RD3_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define RD3_SetPullup()             do { WPUDbits.WPUD3 = 1; } while(0)
#define RD3_ResetPullup()           do { WPUDbits.WPUD3 = 0; } while(0)
#define RD3_SetAnalogMode()         do { ANSELDbits.ANSELD3 = 1; } while(0)
#define RD3_SetDigitalMode()        do { ANSELDbits.ANSELD3 = 0; } while(0)

// get/set VEND5 aliases
#define VEND5_TRIS                 TRISDbits.TRISD4
#define VEND5_LAT                  LATDbits.LATD4
#define VEND5_PORT                 PORTDbits.RD4
#define VEND5_WPU                  WPUDbits.WPUD4
#define VEND5_OD                   ODCONDbits.ODCD4
#define VEND5_ANS                  ANSELDbits.ANSELD4
#define VEND5_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define VEND5_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define VEND5_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define VEND5_GetValue()           PORTDbits.RD4
#define VEND5_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define VEND5_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define VEND5_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define VEND5_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define VEND5_SetPushPull()        do { ODCONDbits.ODCD4 = 0; } while(0)
#define VEND5_SetOpenDrain()       do { ODCONDbits.ODCD4 = 1; } while(0)
#define VEND5_SetAnalogMode()      do { ANSELDbits.ANSELD4 = 1; } while(0)
#define VEND5_SetDigitalMode()     do { ANSELDbits.ANSELD4 = 0; } while(0)

// get/set VEND6 aliases
#define VEND6_TRIS                 TRISDbits.TRISD5
#define VEND6_LAT                  LATDbits.LATD5
#define VEND6_PORT                 PORTDbits.RD5
#define VEND6_WPU                  WPUDbits.WPUD5
#define VEND6_OD                   ODCONDbits.ODCD5
#define VEND6_ANS                  ANSELDbits.ANSELD5
#define VEND6_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define VEND6_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define VEND6_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define VEND6_GetValue()           PORTDbits.RD5
#define VEND6_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define VEND6_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define VEND6_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define VEND6_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define VEND6_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define VEND6_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define VEND6_SetAnalogMode()      do { ANSELDbits.ANSELD5 = 1; } while(0)
#define VEND6_SetDigitalMode()     do { ANSELDbits.ANSELD5 = 0; } while(0)

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

// get/set GDLED aliases
#define GDLED_TRIS                 TRISEbits.TRISE1
#define GDLED_LAT                  LATEbits.LATE1
#define GDLED_PORT                 PORTEbits.RE1
#define GDLED_WPU                  WPUEbits.WPUE1
#define GDLED_OD                   ODCONEbits.ODCE1
#define GDLED_ANS                  ANSELEbits.ANSELE1
#define GDLED_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define GDLED_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define GDLED_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define GDLED_GetValue()           PORTEbits.RE1
#define GDLED_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define GDLED_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define GDLED_SetPullup()          do { WPUEbits.WPUE1 = 1; } while(0)
#define GDLED_ResetPullup()        do { WPUEbits.WPUE1 = 0; } while(0)
#define GDLED_SetPushPull()        do { ODCONEbits.ODCE1 = 0; } while(0)
#define GDLED_SetOpenDrain()       do { ODCONEbits.ODCE1 = 1; } while(0)
#define GDLED_SetAnalogMode()      do { ANSELEbits.ANSELE1 = 1; } while(0)
#define GDLED_SetDigitalMode()     do { ANSELEbits.ANSELE1 = 0; } while(0)

// get/set RDLED aliases
#define RDLED_TRIS                 TRISEbits.TRISE2
#define RDLED_LAT                  LATEbits.LATE2
#define RDLED_PORT                 PORTEbits.RE2
#define RDLED_WPU                  WPUEbits.WPUE2
#define RDLED_OD                   ODCONEbits.ODCE2
#define RDLED_ANS                  ANSELEbits.ANSELE2
#define RDLED_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define RDLED_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define RDLED_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define RDLED_GetValue()           PORTEbits.RE2
#define RDLED_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define RDLED_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define RDLED_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define RDLED_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define RDLED_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define RDLED_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define RDLED_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define RDLED_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)

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