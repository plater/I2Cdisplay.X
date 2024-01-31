/*Copyright Dave Plater 24 February 2020
 display.c interface with 64x128 monochrome graphics display
 * The display has 128 columns by 8 x 8 bit pages (64)
 * ie column 0 to 0x7F and page 0 to 7, MSB is at top and
 * LSB is at the bottom
*/
//#include "gsm.h"
#include "buffers.h"
#include "display.h"
#include "dispfont.h"
#include "qrcodegen.h"

//Lower and upper 4 bit column addresses added to 0x01 for upper and 0x0 for lower
//Sets the starting point on one of eight lines
//Numbered from 0 to 136 with 8 x 8 bytes per font including spaces
uint8_t column[2];
uint16_t counter, timeOut, slaveTimeOut;
uint8_t gsdate[10];
uint8_t gstime[10];
uint8_t i2csend_data[10];
//uint8_t qrbuffer[1733];

void Set_Column(uint8_t col)
{
    uint8_t i = col & 0x0F;
    column[0] = i;
    column[1] = (col >> 4) & 0x0F | 0x10;
    SS_A0_SetLow();
    SPI_write8bit(column[1]);
    SPI_write8bit(column[0]);
    SS_A0_SetHigh();
}

//One page = one of 8 lines
void Set_Page(uint8_t gpage)
{
    gpage = (gpage & 0x0F);
    gpage = (gpage | 0xB0);
    SS_A0_SetLow();
    SPI_write8bit(gpage);
    SS_A0_SetHigh();
    
}
//Start from the beginning of "line"
void Set_Line(uint8_t line)
{
    SS_A0_SetLow();
    //Send 0x40 Display start line 0
    SPI_write8bit( 0x40 );
    Set_Column(0);
    Set_Page(line);
}

void Clr_Line(void)
{
     for(uint8_t x = 0; x < 137; x++)
     {
         Write_Font(0);
     }
}

void Write_String(uint8_t *lcdstring, uint8_t lcdline)
{
    LATDbits.LATD3 = 0; //Select display
    //Send 0x40 Display start line 0
    SS_A0_SetLow();
    SPI_write8bit( 0x40 );
    Set_Line(lcdline);
    Clr_Line();
    Set_Line(lcdline);
    ypos = 0;
    uint8_t x = 0;
    uint8_t i = lcdstring[x];
    while((ypos < 137) && (i != 0))
    {
        i = lcdstring[x++];
        Write_Font(i);
    }
    LATDbits.LATD3 = 1; //Deselect display
}
//Write where Write_String left off
void Continue_String(uint8_t *clcdstring)
{
    LATDbits.LATD3 = 0; //Select display
    uint8_t x = 0;
    uint8_t i = clcdstring[x];
    while((ypos < 137) && (i != 0))
    {
        i = clcdstring[x++];
        Write_Font(i);
    }
    LATDbits.LATD3 = 1; //Deselect display    
}
//static int ypos and static int pagepos
//Write 5 font data bytes to display
void Write_Font(uint8_t _font)
{
    fontpos = _font * 6;
    SS_A0_SetHigh();
    for(int i = 0; i < 6; i++ )
    {
        SPI_write8bit(font_fixed_8px_data[fontpos+i]);
    }
    SPI_write8bit(0); //Empty space after font
    ypos = ypos + 8; // 0 t0 17 characters = 18, ypos end =136
}

void Graphic_test(void)
{
    Graphic_Clear();
    uint8_t x = 0;
    ypos = 0;
    fontpos = 0;
    pagepos = 0;
    uint8_t character = 0x2F;
    LATDbits.LATD3 = 0; //Select display
    SS_A0_SetLow(); //LATDbit 5
    SPI_write8bit(dsp_start_line); //set start line to 0
    while(pagepos <= 7)
    {
        Set_Page(pagepos++);
        Set_Column(ypos);
        while(ypos < 137) //The last character ends at 136
        {
            if (character >= 0x80)
            {
                character = 0x2F;
            }
            Write_Font(character++);
            fontpos = fontpos + 6; //3 = 0x132
        }
        ypos = 0;
    }
//    Graphic_Clear();
//    Write_String(clocktime, 1);
//    Write_String(clockdate, 6);
    
    CS1_SetHigh(); //Deselect display
    __asm__("NOP");
}

void disp_clock(void)
{
    Graphic_Clear();
 //   gsm_gettime();
    Write_String((uint8_t*)clockdate, 2);
    Continue_String(gsdate);
    Write_String((uint8_t*)clocktime, 3);
    Continue_String(gstime);
}

/*
{
    signed char i = 0;
    uint8_t value[16];
    uint32_t hexnumsave = prval;
    translngth = sprintf(value, "   Price R%d.00", prval);
    Write_String((uint8_t*)value, 0);
    translngth = sprintf(qprice, "%d00", prval);
}

//Convert native hex to display decimal
void displ_hex(uint32_t hexnum)
{
    signed char i = 0;
    uint8_t value[8];
    uint32_t hexnumsave = hexnum;
    while(hexnum > 0)
    {
        value[i++] = hexnum % 10;
        hexnum /= 10;
    }
    
    while(i > 0)
    {
        i--;
        Write_Font(value[i] | 0x30);
    }
    //In case hexnum is zero
    if(hexnumsave == 0)
    {
       Write_Font(0x30);
    }
}
*/
/*
void Graphic_test(void)
{
    SS_A0_SetLow(); //Set A0 to COMMAND
    SPI_write8bit(dsp_start_line); //set start line to 0
    uint8_t character = 0x30;
        while(character < 0x80)
    {
        Write_Font(character);
        character = character+ 1;
    }
}
*/
#ifdef SPI_COMS
void Graphic_init(void)
{
    SS_RES_SetHigh(); //Out of reset
    //This bit is confusing in MCC
    SPI1CONbits.DISSDO = 0;
    if(SPI1CONbits.ON == 0)
    {
        SPI1CONbits.ON = 1;
    }
    SS_A0_SetLow(); //Set A0 to COMMAND
    CS1_SetLow();   //Select display
    //Send 0x40 Display start line 0
    SPI_write8bit( 0x40 );
    //Set ADC reverse = 0xA1
    SPI_write8bit( 0xA1 );
    //Common output mode set - Normal Com0 Com63 = 0xC0
    SPI_write8bit( 0xC0 );
    //Display normal/reverse - Normal = 0xA6
//    SPI_write8bit( 0xA6 );
    //LCD bias set - 1/9 (Duty 1/65) = 0xA2
    SPI_write8bit( 0xA2 );
    //Power control set - Booster and Follower on = 0x2F
    SPI_write8bit( 0x2F );
    //Booster ratio - internal to 4x = 0xF8 0x00
    SPI_write8bit( 0xF8 );
    SPI_write8bit( 0x00 );
    //V0 voltage regulator set contrast = 0x27
    SPI_write8bit( 0x27 );
    //Electronic volume mode set contrast = 0x81 0x10
    SPI_write8bit( 0x81 );
    SPI_write8bit( 0x10 );
    //Static indicator - No indicator = 0xAC 0x00, Indicator = 0x01
    SPI_write8bit( 0xAC );
    //Display on/off - display on = 0x00 0xAF
    SPI_write8bit( 0x00 );
    SPI_write8bit( 0xAF );
    //Display all points A5 Normal A4
    SPI_write8bit( 0xA5 );
    for(int y = 0; y < 2; y++){}
    SPI_write8bit( 0xA4 );
//#else
    //init(uint8_t contrast = 60, uint8_t bias = 0x03, uint8_t tempCoeff = 0x02)
    //Power up, extended instructions and horizontal addressing
    SPI_write8bit( 0x21 );
    //Set LCD Vop (Contrast)
    SPI_write8bit( 0xB0 );
    //Temperature coefficient set to recommended 0x02
    SPI_write8bit( 0x04 );
    //Set bias control to recommended 0x03
    SPI_write8bit( 0x13 );
    //Display control = D & E 10 for normal display
    SPI_write8bit( 0x20 ); //Set to normal instructions first
    SPI_write8bit( 0x0C );
    //Here ends configuration
    
    
//    Graphic_Clear();
    CS1_SetHigh(); //Deselect display
    SS_A0_SetHigh(); //Set A0 to DATA
    __asm__("NOP");
}
#else



void Graphic_init(void)
{
    uint8_t         *pData;
    uint8_t         *DData;
    uint16_t        nCount;
    uint32_t        y, x;
    uint8_t         z, i, msize ;
//    pD = INIT_SSD1306;
    y = sizeof(INIT_SSD1306) + INIT_SSD1306; //Don't go further than the end of INIT_SSD1306
    //y--;
    pData = INIT_SSD1306;
    i = 0;
    x = 0;
    while(y > pData)
    {
        msize = *pData; //Load size of command string
        pData++; //Next command
        
        while(msize > x)
        {
            i = *pData;
            SPI_write8bit(i);
            x++;
            pData++;
        }
    } //end while(i <= x)
    y = y + z;
}

#endif
/*void I2C2_MasterWrite(uint8_t *pdata, uint8_t length, uint16_t address, I2C2_MESSAGE_STATUS *pstatus);*/

/* Starting test for 0.96 inch OLED display with I2C interface
 * SCL = RD5, SDA = RD3  Alt SCL = RPG8/SDO2, SDA =  RPG7/SDI2
 * Bit 1 or SA0 determines the device address
 * SSD1306 has to recognize the slave address before transmitting or receiving any information by the
 * I2C-bus. The device will respond to the slave address following by the slave address bit (?SA0? bit)
 * and the read/write select bit (?R/W#? bit) with the following byte format,
 * b7 b6 b5 b4 b3 b2 b1  b0
 * 0  1  1  1  1  0  SA0 R/W# 0x78 but Adafruit say it's 0x3C
 * ?R/W#? bit is used to determine the operation mode of the I2C-bus interface. R/W#=1, it is in read
 * mode. R/W#=0, it is in write mode. */
/*
I2C2_MESSAGE_STATUS I2C_Write_Address(uint8_t mlength)
{
    I2C2_MasterWrite(gsmusm, mlength, I2CAdd, i2cstatus );//void I2C2_MasterWrite(uint8_t *pdata, uint8_t length, uint16_t address, I2C2_MESSAGE_STATUS *i2c2status)
}

I2C2_MESSAGE_STATUS I2C_Write_Command(uint8_t mlength)
{
    I2C2_MasterWrite(gsmusm, mlength, I2CAdd, i2cstatus );
}

I2C2_MESSAGE_STATUS I2C_Write_Data(uint8_t mlength)
{
    
}
*/
/**
 * void I2C2_MasterWrite(uint8_t *pdata, uint8_t length, uint16_t address, I2C2_MESSAGE_STATUS *i2c2status);
 */
//SPI1STAT bit SPIBUSY 11=1 = busy, bit SPITUR 8=1 = tx underrun, bit SRMT 7=1 Shift register empty, 
//bit SPITBE 3=1 Transmit buffer empty, bit SPITBF 1=1 Transmit not started.
//Before writing to SPI1BUF ensure SPI1STAT.SPITBE is 1 after SPI1STAT.SPITBF must = 0
#ifdef SPI_COMS
void SPI_write8bit(uint8_t data)
{
    while( SPI1STATbits.SPITBF == true )
    {

    }

    SPI1BUF = data;
    if (SPI1STATbits.SPIRBE == false)
    {
        data = SPI1BUF;
    }
        
    while( SPI1STATbits.SRMT == false )
    {

    }

}
#else //SPI_COMS
void SPI_write8bit(uint8_t data)
{
    uint8_t command;
    if(LATDbits.LATD5)
    {
        command = 0x40; //Write graphic data
    }
    else
    {
        command = 0; //Write command
    }
    ssh1106_write(data, 1, command);
}

#endif //SPI_COMS
/*
 bool qrcodegen_encodeText(const char *text, size_t textLen, uint8_t tempBuffer[], uint8_t qrcode[],
	enum qrcodegen_Ecc ecl, int minVersion, int maxVersion, enum qrcodegen_Mask mask, bool boostEcl);
*/
#if 0
void Graphic_qrcode(uint32_t amount, uint8_t id)
{
    repeatcode:;
    uint8_t text[64] = "https://pos.snapscan.io/qr/CMMCyv0i?id=01&amount=";                // User-supplied text
	uint8_t x = 39;
    uint8_t z = 0;
    uint32_t csize = sprintf(text, "https://pos.snapscan.io/qr/CMMCyv0i?id=Chan%d&amount=%d00", id, amount);
	uint8_t y = sizeof text - sizeof amount;
//	enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_MEDIUM;  // Error correction level
    uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
	// Make and print the QR Code symbol
	uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
    //uint8_t qrcode[138];
	//uint8_t tempBuffer[138];
bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode, qrcodegen_Ecc_MEDIUM,	qrcodegen_VERSION_MIN,
        qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
	if (ok)
    {
        printQr(qrcode);
    }
    else
    {
        goto repeatcode;
    }

}
#endif
void QRDisplay(uint8_t * xpmname)
{
    
}

void printQr(uint8_t qrcode[])
{
    for(int i = 0; i < 1734; i++)
    {
        qrbuffer[i] = 0;
    }
	int size = qrcodegen_getSize(qrcode);
	int border = 4;
	int blackb = 0;//
	for (int y = -border; y < size + border; y++) {
		for (int x = -border; x < size + border; x++) {
			qrbuffer[blackb++] = qrcodegen_getModule(qrcode, x, y) ? 'F' : 'B';
		}
		qrbuffer[blackb++] = 'E'; //Pad an extra 4 Bs either side of the E
	}
    qrbuffer[++blackb] = 0;
    Write_Qrcode(qrbuffer);
}
/*/* XPM */
//static const char *const chan1_xpm[] = {
/* width height ncolors chars_per_pixel */
//"37 37 2 1",
/* colors */
//"F c #000000",
//"B c #ffffff",
/* pixels */
//"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
//*/
void Store_XPM(uint8_t *xpmname)
{
    uint8_t x, y, z; //x = number of char and y = number of rows
    x = atoi(xpmname);
    y = atoi(xpmname + 3);
    xpmname = strstr(xpmname, "BBBB");
    z = xpmname[0];
}

void Load_Qrcode(const uint8_t xpmname[])
{
    uint8_t *x = memcpy(qrbuffer, xpmname, sizeof(xpmname));
    Write_Qrcode(xpmname);
}


//Position page 2 to 7 column 43
//Display qrcode on screen.
void Write_Qrcode(const uint8_t xpmname[])
{
	CS1_SetLow();
	ypos = 43;
	pagepos = 2;
	static uint16_t z, xpmlng, scrat, noline;
    z = 0;
    uint16_t x;
	uint8_t qrbyte;
	uint8_t linecount = 0;
	uint16_t qrcount = 0;
    uint16_t l, zbu;
    uint8_t *e;
    zbu=0;
    qrbyte = 0; // holds xpm pixel value
    xpmlng = strlen(xpmname);
    e = memchr(xpmname, 'E', 64); //find the line length
    l = e - xpmname;              //store it's value in l
    l++;
    noline = xpmlng / l;
	SS_A0_SetHigh();
	Set_Column(ypos);
	Set_Page(pagepos);
	readcode:;
	uint8_t qbyte = 0; //qbyte holds raw graphic page value (page = 8 y bits)
	for(x=0; x < 8; x++)
	{
        if(z >= xpmlng)
        {
            scrat = z - xpmlng;
        }
		qbyte = qbyte >> 1;
		qrbyte = xpmname[z]; //z contains position from start of line
        if(qrbyte == 0) // NULL string end
        {
            goto exitqr;
        }
		if(qrbyte == 'E')//End of line
		{
			Set_Column(43);
			Set_Page(++pagepos);
			if(qrcount == 0)
			{
				qrcount = z + 1;
			}
			linecount = linecount + 8;
			zbu = (linecount * qrcount); //go to next 8 rows +330
			z = zbu;
			goto readcode;
		}
		if(qrbyte == 'B')// B is black  F is white and E is end of line
		{
			qbyte = qbyte | 0x80;
		}
		else
		{
			qbyte = qbyte & 0x7F;
		}

		z = z + l;

	}
	SPI_write8bit(qbyte);
	z = ++zbu;
    if(z >= xpmlng)
    {
        scrat = z - xpmlng;
    }
	goto readcode;


	exitqr:;
}


void Graphic_Clear(void)
{
    uint8_t x = 0;
    uint8_t y = 0;
    CS1_SetLow(); //Select display
    SS_A0_SetHigh();
    while(x <= 7)
    {
        Set_Page(x++);
        Set_Column(y);
        while(y < 137)
        {
            SPI_write8bit(0);
            y++;
        }
        y = 0;
    }
    //Send 0x40 Display start line 0
    SS_A0_SetLow();
    SPI_write8bit( 0x40 );
    LATDbits.LATD3 = 1; //Deselect display
   
}
#if 0
void Sample_code(void)
{
    // initialize the module
//    I2C2_Initialize();
//    delay_milli(100);
    // write to an EEPROM Device
// 0111100
    uint16_t dataAddress;
    uint8_t sourceData[16] = {  0x00, 0xA4, 0x00, 0xA6, 
                                0xA4, 0xA5, 0xA6, 0xA7, 
                                0xA8, 0xA9, 0xAA, 0xAB, 
                                0xAC, 0xAD, 0xAE, 0xAF }; 
    uint8_t         *pData;
    uint16_t        nCount;
    
    uint8_t         writeBuffer[3];
    uint8_t         *pD;
    

    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING;

    slaveDeviceAddress = I2CAdd;
    dataAddress = 0x10;             // starting EEPROM address 
    pD = sourceData;                // initialize the source of the data
    nCount = 1;                    // number of bytes to write

    for (counter = 0; counter < nCount; counter++)
    {

        // build the write buffer first
        // starting address of the EEPROM memory
        writeBuffer[0] = (dataAddress >> 8);                // high address
        writeBuffer[1] = (uint8_t)(dataAddress);            // low low address

        // data to be written
        writeBuffer[2] = *pD++;

        // Now it is possible that the slave device will be slow.
        // As a work around on these slaves, the application can
        // retry sending the transaction
        timeOut = 0;
        slaveTimeOut = 0;
        
        while(status != I2C2_MESSAGE_FAIL)
        {
            // write one byte to EEPROM (3 is the number of bytes to write)
            /*
             * void I2C2_MasterWrite(uint8_t *pdata, uint8_t length, uint16_t address, I2C2_MESSAGE_STATUS *pstatus)
             */
            I2C2_MasterWrite( sourceData, 4, slaveDeviceAddress, &status);

            // wait for the message to be sent or status has changed.
            while(status == I2C2_MESSAGE_PENDING)
            {
                // add some delay here

                // timeout checking
                // check for max retry and skip this byte
                if (slaveTimeOut == SLAVE_I2C_GENERIC_DEVICE_TIMEOUT)
                    break;
                else
                    slaveTimeOut++;
            } 
            if(status == I2C2_MESSAGE_COMPLETE)
            {
                break;
            }
            if ((slaveTimeOut == SLAVE_I2C_GENERIC_DEVICE_TIMEOUT) || 
                (status == I2C2_MESSAGE_COMPLETE))
                break;

            // if status is  I2C2_MESSAGE_ADDRESS_NO_ACK,
            //               or I2C2_DATA_NO_ACK,
            // The device may be busy and needs more time for the last
            // write so we can retry writing the data, this is why we
            // use a while loop here

            // check for max retry and skip this byte
            if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
                break;
            else
                timeOut++;
        }

        if (status == I2C2_MESSAGE_FAIL)
        {
            break;
        }
        dataAddress++;
    
    }
}

void I2c_write_block(uint8_t *sourceData, uint8_t length, I2C2_MESSAGE_STATUS stat)
{
    slaveDeviceAddress = SSD1306_ADDRESS;
    while(stat != I2C2_MESSAGE_FAIL)
    {
        I2C2_MasterWrite(  sourceData, length, slaveDeviceAddress, &stat);

        // wait for the message to be sent or status has changed.
        while(stat == I2C2_MESSAGE_PENDING)
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
            if(stat == I2C2_MESSAGE_COMPLETE)
            {
                break;
            }
            if ((slaveTimeOut == SLAVE_I2C_GENERIC_DEVICE_TIMEOUT) || 
                (stat == I2C2_MESSAGE_COMPLETE))
                break;

            // if status is  I2C2_MESSAGE_ADDRESS_NO_ACK,
            //               or I2C2_DATA_NO_ACK,
            // The device may be busy and needs more time for the last
            // write so we can retry writing the data, this is why we
            // use a while loop here

            // check for max retry and skip this byte
            if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            {
                break;
            }
            else
            {
                timeOut++;
            }
        }
        if(!I2C2CONbits.PEN)         // I2C STOP control bit.
        {
            I2C2CONbits.PEN = 1;
        }
    }

        
}
#endif

/* MCLKSEL PBCLK; DISSDO enabled; SRXISEL Last Word is Read; CKP Idle:High, Active:Low; FRMEN disabled; FRMSYPW One-Clock;
  SSEN disabled; FRMCNT 32; MSSEN disabled; MSTEN Master; MODE16 disabled; FRMPOL disabled; SMP End; SIDL disabled;
  FRMSYNC disabled; CKE Active to Idle; MODE32 disabled; SPIFE Frame Sync pulse precedes; STXISEL Buffer is completely empty;
  DISSDI enabled; ON enabled; ENHBUF enabled; 
  24   20   16   12    8    4   0
0101 0000 0001 1010 0011 0111 0100
SPI1CON = 0x5019374;
 */
void  Delay_abit()
{
    
    for(int y = 0; y < 8; y++)
    {
    }
}