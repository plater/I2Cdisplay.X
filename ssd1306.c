

#include "display.h"
#include "mcc_generated_files/mcc.h"
#define SLAVE_I2C_GENERIC_DEVICE_TIMEOUT 65535

I2C2_MESSAGE_STATUS ssd1306_write(uint8_t *pdata, uint8_t msize, uint8_t command)
{
//    uint8_t *pdata;
    uint8_t pD[8]; //I2C send/receive buffer
    uint8_t *idata;
    uint8_t  z, x, i ;
    uint16_t nCount, y, slaveTimeOut;
    uint8_t  slaveDeviceAddress = 0x3C;
 //   pdata = pD;
    I2C2CONbits.ON = 1; 
    slaveTimeOut = 0;
    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING;
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
