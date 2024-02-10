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
        I2C2_WriteNBytes((i2c2_address_t)I2CAdd, DData, (size_t) msize);
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
    
 I2C2_WriteNBytes((i2c2_address_t)I2CAdd, DData, (size_t) 2);
}

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
void Store_XPM(uint8_t xpmname[], uint8_t xpmstat[])
{
    uint8_t* srchst;
    uint16_t v, w; //v = number of char and w = number of rows
    uint16_t x, y, z;
    v = atoi(xpmstat); //Characters per line or width
    srchst = strchr(xpmstat, ' ');
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

Qr_Text(const uint8_t xpmname[], uint8_t xpos, uint8_t ypost)
{
    ypos = xpos;
    pagepos = ypost;
    Set_Column(ypos);
    Set_Page(pagepos);
    Continue_String(xpmname);
}

//Position page 2 to 7 column 43
//Display qrcode on screen.
void Write_Qrcode(const uint8_t xpmname[])
{
	CS1_SetLow();
    Qr_Text(chan1a_txt, 35, 0);
    Qr_Text(chan1a_ptic, 24, 1);
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
/*XPM storage routines*/



