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
#include "xpms.h"
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

void Write_String(const uint8_t *lcdstring, uint8_t lcdline)
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
#if 0
void disp_clock(void)
{
    Graphic_Clear();
 //   gsm_gettime();
    Write_String((uint8_t*)clockdate, 2);
    Continue_String(gsdate);
    Write_String((uint8_t*)clocktime, 3);
    Continue_String(gstime);
}
#endif
void Graphic_init(void)
{
    uint8_t         *pData;
    uint16_t        nCount;
    uint32_t        y, x;
    uint8_t         z, i, msize, c = 0 ;
//    pD = INIT_SSD1306;
    //y--;
    pData = memcpy(gsmmsg, INIT_SSD1306, 49);
    i = 0;
    while(c < 18)
    {
        msize = *pData; //Load size of command string
        pData++;
        x = 0;
        DData[x++] = 0; //Command
        while(x <= msize)
        {
            DData[x] =  *pData; //Load data
            pData++;
            x++;
        }
        msize++;
        myI2C2_WriteNBytes((i2c2_address_t)I2CAdd, DData, (size_t) msize);
        c++;
    } //end while(i <= x)
    y = y + z;
}
void SPI_write8bit(uint8_t data)
{
    uint8_t command;
    if(SS_A0_LAT)
    {
        command = 0x40; //Write graphic data
    }
    else
    {
        command = 0; //Write command
    }
    DData[0] = command;
    DData[1] = data;
    DData[2] = 0;
    
 myI2C2_WriteNBytes((i2c2_address_t)I2CAdd, DData, (size_t) 2);
}

void QRDisplay(uint8_t * xpmname)
{
    
}

/*void printQr(uint8_t qrcode[])
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
}*/
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
void Store_XPM(uint8_t *xpmname, uint8_t* xpmstat)
{
    uint8_t* srchst;
    uint8_t* srcstat;
    uint16_t v, w; //v = number of char and w = number of rows
    uint16_t x, y, z;
    srcstat = xpmstat;
    v = atoi(qrstat1_xpm); //Characters per line or width
    srchst = strchr(qrstat1_xpm, ' ');
    w = atoi(++srchst); //Number of lines or hight
    srchst = gsmmsg;
    while(w > 0)
    {
        memcpy(srchst, xpmname, v);
        srchst = (srchst + v);
        srchst[0] = 'E';
        srchst++;
        xpmname = xpmname + v + 1;
        w--;
    }
}

void Load_Qrcode(const uint8_t xpmname[])
{
    uint8_t *x = memcpy(qrbuffer, xpmname, sizeof(xpmname));
    Write_Qrcode(xpmname);
}

void Qr_Text(const uint8_t xpmname[], uint8_t xpos, uint8_t ypost)
{
    ypos = xpos;
    pagepos = ypost;
    Set_Column(ypos);
    Set_Page(pagepos);
    Continue_String(xpmname);
}

//Position page 2 to 7 column 43
//Display qrcode on screen.
void Write_Qrcode(uint8_t channeln)
{
    uint8_t dcache[16];//one line of characters = 16 characters
	static uint16_t z, xpmlng, scrat, noline;
    uint16_t x, xy;
	uint8_t qrbyte;
	uint8_t linecount = 0;
    uint16_t l, zbu, w;
    uint8_t *e;
    uint8_t over;
    Reset_Alldisp();
    Set_Display(channeln);
    xy = 1;
    xpmaddress = Chan01_xpm; // xpmaddress stores the channels storage address
    while(xy < channeln)
    {
        xpmaddress = xpmaddress + STORAGE_SIZE;
        xy++;
    }
    srchbuf0 = xpmaddress + BUF_SIZE;//Set xpm info address
    srchbuf1 = strstr(srchbuf0, "\nP");
    x = srchbuf1 - srchbuf0;
    memcpy(dcache, srchbuf0, x);
    dcache[x] = NULL;
    x = x * 8;//Calculate total columns
    xy = DISPLAY_COL - x;// used  to center the line
    xy = xy/2; //Calculate offset to center the line
	CS1_SetLow();
    Qr_Text(dcache, xy, 0);
    srchbuf1++;
    x = strlen(srchbuf1);
    x = x * 8;//Calculate total columns
    xy = DISPLAY_COL - x;
    xy = xy/2; //Calculate offset to center the line
    Qr_Text(srchbuf1, xy, 1);
	ypos = 46;
	pagepos = 3;
    z = 0;
    zbu=0;
    qrbyte = 0; // holds xpm pixel value
    xpmlng = strlen(xpmaddress);
    e = memchr(xpmaddress, 'E', 64); //find the line length
    l = e - xpmaddress;              //store it's value in l
    l++;
    noline = xpmlng / l;
    w = noline;
	SS_A0_SetHigh();
	Set_Column(ypos);
	Set_Page(pagepos);
    over = 0;
	readcode:;
	uint8_t qbyte = 0; //qbyte holds raw graphic page value (page = 8 y bits)
	for(x=0; x < 8; x++)
	{
		qbyte = qbyte >> 1;
		qrbyte = xpmaddress[z]; //z contains position from start of line
		if(qrbyte == 'E')//End of line
		{
			Set_Column(ypos);
			Set_Page(++pagepos);
			linecount = linecount + 8;
            if(linecount >= noline)
            {
                goto exitqr;
            }
			zbu = (linecount * l); //go to next 8 rows +330
            qrbyte = xpmaddress[++z];
            if(qrbyte == 0) // NULL string end
            {
                NOP();
                goto exitqr;
            }
			z = zbu;
            if(z >= xpmlng)
            {
                goto exitqr;
            }
			goto readcode;
		}
		if(qrbyte == 'F')// F is black  B is white and E is end of line
		{
			qbyte = qbyte & 0x7F;
		}
		else //qrbyte = F or any other value becomes black
		{
			qbyte = qbyte | 0x80;
		}

		z = z + l;

	}
	SPI_write8bit(qbyte);
	z = ++zbu;
    if(z >= xpmlng)
    {
        NOP();
        goto exitqr;
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

void Identify_D(uint8_t dispnum)
{
    switch(dispnum)
    {
        case 1 :
            Set_Display(0);
            Write_String(display1, 6);
        case 2 :
            Set_Display(1);
            Write_String(display2, 6);
        case 3 :
            Set_Display(2);
            Write_String(display3, 6);
        case 4 :
            Set_Display(3);
            Write_String(display4, 6);
    }
}
/** I2C Pin Initialization displays are:
 *  RD1 = SDA1 RD2 = SDA2 RD3 = SDA3 RD4 = SDA4 */

void Reset_Alldisp(void)
{
    RD1_SetHigh();
    RD2_SetHigh();
    RD3_SetHigh();
    RD4_SetHigh();
    RD1PPS = 0x0;
    RD2PPS = 0x0;
    RD3PPS = 0x0;
    RD4PPS = 0x0;
}

void Set_Alldisp(void)
{
    RD1PPS = 0x12;
    RD2PPS = 0x12;
    RD3PPS = 0x12;
    RD4PPS = 0x12;
}

void Reset_Display(uint8_t dispnum)
{
    dispnum = dispnum & 0x07;
    switch(dispnum)
    {
        case 1 :
            RD1_SetHigh();
            RD1PPS = 0x0;
            break;
        case 2 :
            RD2_SetHigh();
            RD2PPS = 0x0;
            break;
        case 3 :
            RD3_SetHigh();
            RD3PPS = 0x0;
            break;
        case 4 :
            RD4_SetHigh();
            RD4PPS = 0x0;
    }
   
}

void Set_Display(uint8_t dispnum)
{
    dispnum = dispnum & 0x07;
    switch(dispnum)
    {
        case 1 :
            SSP2DATPPS = 0x19;   //RD1->MSSP2:SDA2;
            RD1PPS = 0x12;
            break;
        case 2 :
            SSP2DATPPS = 0x1A;   //RD2->MSSP2:SDA2;
            RD2PPS = 0x12;
            break;
        case 3 :
            SSP2DATPPS = 0x1B;   //RD3->MSSP2:SDA2;
            RD3PPS = 0x12;
            break;
        case 4 :
            SSP2DATPPS = 0x1C;
            RD4PPS = 0x12;
    }
}
void DSP_rd1_init(void)
{
    SSP2DATPPS = 0x19;   //RD1->MSSP2:SDA2;    
    RD1PPS = 0x12;   //RD1->MSSP2:SDA2;    
    RD0PPS = 0x11;   //RD0->MSSP2:SCL2;    
    SSP2CLKPPS = 0x18;   //RD0->MSSP2:SCL2;
    Graphic_init();//init display one
    Graphic_Clear();
    Write_String(display1, 4);
    RD1_SetHigh();
    RD1PPS = 0x0;
}
void DSP_rd2_init(void)
{
    SSP2DATPPS = 0x1A;   //RD2->MSSP2:SDA2;    
    RD2PPS = 0x12;   //RD2->MSSP2:SDA2;    
    RD0PPS = 0x11;   //RD0->MSSP2:SCL2;    
    SSP2CLKPPS = 0x18;   //RD0->MSSP2:SCL2;
    Graphic_init();//init display one
    Graphic_Clear();
    Write_String(display2, 4);
    RD2_SetHigh();
    RD2PPS = 0x0;
}
void DSP_rd3_init(void)
{
    SSP2DATPPS = 0x1B;   //RD3->MSSP2:SDA2;    
    RD3PPS = 0x12;   //RD3->MSSP2:SDA2;    
    RD0PPS = 0x11;   //RD0->MSSP2:SCL2;    
    SSP2CLKPPS = 0x18;   //RD0->MSSP2:SCL2;    
    Graphic_init();//init display one
    Graphic_Clear();
    Write_String(display3, 4);
    RD3_SetHigh();
    RD3PPS = 0x0;
}
void DSP_rd4_init(void)
{
    SSP2DATPPS = 0x1C;   //RD4->MSSP2:SDA2;    
    RD4PPS = 0x12;   //RD4->MSSP2:SDA2;    
    RD0PPS = 0x11;   //RD0->MSSP2:SCL2;    
    SSP2CLKPPS = 0x18;   //RD0->MSSP2:SCL2;    
    Graphic_init();//init display one
    Graphic_Clear();
    Write_String(display4, 4);
    RD4_SetHigh();
    RD4PPS = 0x0;
}

#if 0
static void PPS_Initialize(void)
{
    /* PPS setting for using RD2 as SCL */
    SSP2CLKPPS = 0x09;
    RD2PPS = 0x0F;
    /* PPS setting for using RD3 as SDA */
    SSP2DATPPS = 0x0A;
    RD3PPS = 0x10;
    /*From pin_manager.c*/
    RD2PPS = 0x12;   //RD2->MSSP2:SDA2;    
    SSP2DATPPS = 0x1A;   //RD2->MSSP2:SDA2;    
    RD3PPS = 0x11;   //RD3->MSSP2:SCL2;    
    SSP2CLKPPS = 0x1B;   //RD3->MSSP2:SCL2;    
}

/*The PORT_Initialize function sets pins, RB1 and RB2, as digital pins with internal pull-up resistors and in
open-drain mode:*/
static void PORT_Initialize(void)
{
/* Set pins RD0 to RD4 as Digital for multiple I2C*/
//RD2_SetDigitalMode();
RD3_SetDigitalMode();
#if 0 //We don't need these on peripheral D
/* Set pull-up resistors for RB1 and RB2 */
WPUBbits.WPUB1 = 1;
WPUBbits.WPUB2 = 1;
/* Set open-drain mode for RB1 and RB2 */
ODCONBbits.ODCB1 = 1;
ODCONBbits.ODCB2 = 1;
#endif
}

#endif

/*XPM storage routines*/



