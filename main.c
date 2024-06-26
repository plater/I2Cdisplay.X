/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F47K40
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#include "buffers.h"
#include "display.h"
#include "xpms.h"
/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

#ifndef __DEBUG
    WDTCON0bits.SEN = 1;
#endif
    ClrWdt();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
 //   INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
 //   INTERRUPT_PeripheralInterruptDisable();
    Reset_Alldisp();
    DSP_rd1_init();
    DSP_rd2_init();
    DSP_rd3_init();
    DSP_rd4_init();
/*    Set_Display(0);
    Set_Display(1);
    Set_Display(2);
    Set_Display(3);*/
    Graphic_test();
    gsm_init(0);
    Get_mms();
    Write_Qrcode(1);
    Write_Qrcode(2);
    Write_Qrcode(3);
    Write_Qrcode(4);
 //   Store_XPM(qrcode1_xpm, qrstat1_xpm);
    while(SERVICE_GetValue())
    {
        ClrWdt();
    }
    while(!SERVICE_GetValue());
    Graphic_Clear();
    Write_Qrcode(1);
    while(SERVICE_GetValue())
    {
        ClrWdt();
    }
    while(!SERVICE_GetValue());
//    RD3_SetDigitalOutput();
//    RD3_Toggle();

    while (1)
    {
        Graphic_test();
        while(SERVICE_GetValue())
        {
            ClrWdt();
        }
        while(!SERVICE_GetValue());
        Graphic_Clear();
        Write_Qrcode(qrcode1_xpm);
        while(SERVICE_GetValue())
        {
            ClrWdt();
        }
        while(!SERVICE_GetValue());
        Graphic_Clear();
    }
}
/**
 End of File
*/