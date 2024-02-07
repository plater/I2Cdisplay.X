/* ************************************************************************** */
/** Descriptive File Name

  @Company
 Dave Plater

  @File Name
    sh1106.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** *
 * Copied and modified for PIC81F47K40 from https://www.electronicwings.com/pic/pic18f4550-i2c
 * ************************************************************************** */

#include "display.h"
#include "mcc_generated_files/mcc.h"

/*Start I2C communication

    Send start pulse to the slave device by setting a bit in SEN in the SSP2CON2 register.
    Wait for SEN bit to clear.
    Also, check S bit in SSP2STAT register which indicates the start bit is detected or not.
    And then send the device slave address along with write operation and check for acknowledgment signal.
*/
char I2C_Start(char slave_write_address)
{   
    SSP2CON2bits.SEN=1;		/* Send start pulse */
    while(SSP2CON2bits.SEN);	/* Wait for completion of start pulse */
    SSP2IF=0;
    if(!SSP2STATbits.S)		/* Check whether START detected last */
    return 0;			/* Return 0 to indicate start failed */   
    return (I2C_Write(slave_write_address));	/* Write slave device address
						with write to communicate */
}
 

/*Write/Transmit Data

We have to monitor BF flag or SSPIF which will set when transmission/reception of a byte is complete.

I2C Bus Ready

Check the BF flag and R/W bit in the SSPSTAT register for finding the I2C bus is ready or not.
*/
#if 0
 void I2C_Ready()
{
    while(BCL2IF);	/* Wait if bit collision interrupt flag is set*/

    /* Wait for Buffer full and read write flag*/
    while(SSP2STATbits.BF || (SSP2STATbits.R_nW));
    PIR3bits.SSP2IF=0;  		/* Clear PIR3bits.SSP2IF interrupt flag*/
}
#endif
 
/*
Also SSPIF flag can be used to poll the complete byte transmit/receive status. Also, it is necessary to clear the SSPIF interrupt flag through software.
*/
void I2C_Ready(void)
{
    while(!PIR3bits.SSP2IF);	/* Wait for operation complete */
    PIR3bits.SSP2IF=0;		/* Clear SSPIF interrupt flag*/
}

 

/*Copy/write data to the SSPBUF register for transmission and wait for the completion of the transmission.
*/
bool I2C_Write(uint8_t data)
{
      SSP2BUF=data;	/* Write data to SSP2BUF*/
      while(!PIR3bits.SSP2IF);	/* Wait for operation complete */
      PIR3bits.SSP2IF=0;		/* Clear SSPIF interrupt flag*/
      return(SSP2CON2bits.ACKSTAT);	/* Check for acknowledge bit = 0 is acknowledge*/
}

 

/*After write if we want to Stop I2C communication,

Set the PEN bit in SSP2CON2 register and wait for the PEN bit to clear.

Also, check P bit in the SSP2STAT register which indicates the stop bit is detected.
*/
bool I2C_Stop(void)
{
    I2C_Ready();
    SSP2CON2bits.PEN=1;		/* Stop communication*/
    while(SSP2CON2bits.PEN);		/* Wait for end of stop pulse*/
    PIR3bits.SSP2IF = 0;
    return(SSP2STATbits.P); /* Check whether STOP is detected last 1 = success */
}

 

/*Read/Receive Data

    Enable receive mode by setting bit RCEN in SSP2CON2.
    Then wait for the Buffer flag to set which is set when a complete byte is received.
    Read the buffer immediately.
    After reading one byte, send an acknowledge signal if we want to read the next data else send negative acknowledge which tells we don?t want to read the next data.
    To do this, ACKDT =1 or 0 and ACKEN should be enabled.

/* Read data from location and send ack or nack depending upon parameter*/

uint8_t I2C_Read(uint8_t flag)
{
        int buffer=0;
        SSP2CON2bits.RCEN=1;			/* Enable receive */

	/* Wait for buffer full flag which when complete byte received */
        while(!SSP2STATbits.BF);
        buffer=SSP2BUF;		/* Copy SSP2BUF to buffer */

	/* Send acknowledgment or negative acknowledgment after read to 
	continue or stop reading */
        if(flag==0)
            I2C_Ack();
        else
            I2C_Nack();
        I2C_Ready();
        return(buffer);
}

 

/*Acknowledgment*/

void I2C_Ack(void)
{
    SSP2CON2bits.ACKDT=0;		/* Acknowledge data 1:NACK,0:ACK */
    SSP2CON2bits.ACKEN=1;		/* Enable ACK to send */
    while(SSP2CON2bits.ACKEN);
 }

 

//Negative acknowledgment

void I2C_Nack(void)
{
    SSP2CON2bits.ACKDT=1;		/* Acknowledge data 1:NACK,0:ACK */
    SSP2CON2bits.ACKEN=1;		/* Enable ACK to send */
    while(SSP2CON2bits.ACKEN);
}

/* *****************************************************************************
 End of File
 */
