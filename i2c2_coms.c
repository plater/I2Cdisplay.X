/* ************************************************************************** */
/** Descriptive File Name

  @Company
 Dave Plater

  @File Name
    i2c2_coms.c

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

/*Start I2C communication*/
void ssh1106_write(uint8_t data, uint8_t msize, uint8_t command)
{
//    uint8_t DData[8]; //I2C send/receive buffer
    uint8_t *idata;
    uint8_t  z, x, i ;
    uint16_t nCount, y, slaveTimeOut;
/*    PIE3bits.SSP2IE = 1;
    PIR3bits.SSP2IF = 0;
    PIR3bits.BCL2IF = 0;*/
    DData[0] = command; //command is 0x00 and data is 0x40
    DData[1] = data;
    DData[2] = 0;
    msize++; //Allow for command byte
    I2C2_WriteNBytes((i2c2_address_t)I2CAdd, DData, (size_t) msize);
    i = 0;
/*    while(msize > 0)
    {
        x = pD[i++];
        while(I2C_Write(x));
        msize--;
    }
    
    if(I2C_Stop())
    {
        NOP();//success
    }
    else
    {
        NOP();//failure
    }*/
}
/**
  */

void I2C2_WriteNBytes(i2c2_address_t address, uint8_t* data, size_t len)
{
    while(!I2C2_Open(address)); // sit here until we get the bus..
    I2C2_SetBuffer(data,len);
    I2C2_SetAddressNackCallback(NULL,NULL); //NACK polling?
    I2C2_MasterWrite();
    while(I2C2_BUSY == I2C2_Close()); // sit here until finished.
}


#if 0
void I2C2_WriteNBytes(i2c2_address_t address, uint8_t* data, size_t len)
{
 //   I2C2_Open(I2CAdd);
    uint8_t c = 0;
    if(I2C_Start(I2CAdd))
    {
        while(len > 0)
        {
            I2C_Write(data[c]);
            c++;
            len--;
        }
        I2C_Stop();
        NOP();
    }
}
#endif

#if 0

    while(!I2C2_Open(address)); // sit here until we get the bus..
    I2C2_SetBuffer(data,len);
    I2C2_SetAddressNackCallback(NULL,NULL); //NACK polling?
    I2C2_MasterWrite();
    bussy:
    if(!I2C2_Status.busy)
    {
        I2C2_Status.inUse = 0;
        I2C2_Status.address = 0xff;
        PIR3bits.SSP2IF = 0;
        PIE3bits.SSP2IE = 0;
        SSP2CON1bits.SSPEN = 0;
    }
    else
    {
        goto bussy;
    }
#define SLAVE_I2C_GENERIC_DEVICE_TIMEOUT 65535

ssd1306_write(uint8_t *pdata, uint8_t msize, uint8_t command)
{
//    uint8_t *pdata;
    uint8_t pD[8]; //I2C send/receive buffer
    uint8_t *idata;
    uint8_t  z, x, i ;
    uint16_t nCount, y, slaveTimeOut;
    uint8_t  slaveDeviceAddress = 0x3C;
 //   pdata = pD;
    //    pD = INIT_SSD1306;
    pD[0] = command; //command is 0x00 and data is 0x40
    idata = pD;
    idata++;
    nCount = memcpy(idata, pdata, msize);
    msize++;
    I2C2_MasterWrite(pD, msize, slaveDeviceAddress, &status );
    while(status == I2C2_MESSAGE_PENDING)
    {
                // timeout checking
                // check for max retry and skip this byte
        if (slaveTimeOut == SLAVE_I2C_GENERIC_DEVICE_TIMEOUT)
        {
            break;
        }
        else
        {
            slaveTimeOut++;
        } 
        if(status == I2C2_MESSAGE_COMPLETE)
        {
            break;
        }
            // if status is  I2C2_MESSAGE_ADDRESS_NO_ACK,
            //               or I2C2_DATA_NO_ACK,
            // The device may be busy and needs more time for the last
            // write so we can retry writing the data, this is why we
            // use a while loop here
    } //end status == I2C2_MESSAGE_PENDING
    I2C2CONbits.ON = 0; //Idle bus

    return status;
}

void PIC_i2c_write(uint8_t sdata, uint8_t msize, uint8_t command)
{
    i2c2_error_t status;
    status = I2C2_Open((i2c2_address_t) I2CAdd);
    if(status == I2C2_FAIL)
    {
        while(1);
    }
    while(status == I2C2_BUSY)
    {
        status = I2C2_Open((i2c2_address_t) I2CAdd);//something wrong?
    }
    
}
#endif



        
        

