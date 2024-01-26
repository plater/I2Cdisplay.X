/* 
 * File:   buffers.h
 * Author: Dave Plater
 * 
 *
 * Created on 20 October 2020, 1:46 PM
 */


#ifndef __BUFFERS_H    /* Guard against multiple inclusion */
#define __BUFFERS_H
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include "xpms.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* All the buffers used across files  include this to use                                                 */
/* ************************************************************************** */
/* ************************************************************************** */

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
//Fits on 40 pin DIP PIC18F47Q83
static char *searchbuf;
#define TRANS 0
#define LCD_WIDTH   136// Note: x-coordinates go wide
#define LCD_HEIGHT  64 // Note: y-coordinates go high
#define WHITE       0  // For drawing pixels. A 0 draws white.
#define BLACK       1  // A 1 draws black.
//For I2C

#if 0
struct bufflags
{
	unsigned retransmit : 1;
	unsigned meerror : 1;
	unsigned mtn : 1;
	unsigned msgavl : 1;
	unsigned abrtmsg : 1;
	unsigned eomsg : 1;
	unsigned msggod : 1;
	unsigned sigtest : 1;
} ;

#endif
// __attribute__ ;
//__attribute__ ((externally_visible))
/** tcp.h imports 
struct gsmflags; 
struct vendflags;*/
//Gsm related memory
extern uint8_t gsmbyte;
//moble network code 01 = Vodacom, 10 or 12 = Mtn
extern uint8_t mncbyte;
//gsm scratch pad
extern uint8_t pD[8]; //I2C send/receive buffer
extern uint8_t gsmmsg[512];// __attribute__((section("tcpsection"),address(0xA0001000)));
extern uint8_t gsmusd[128];
extern uint8_t gsmusm[24];
extern uint8_t gsmtim[23];
extern uint8_t gsdate[10];
extern uint8_t gstime[10];
extern uint8_t phnumb[11];
extern uint8_t noofline;
extern uint8_t slaveDeviceAddress;
extern uint8_t gstime[10];

static uint8_t qprice[8] = "1000";

extern uint8_t transid[24];// __attribute__((section("tcpsection")));// = "\"id\":";//"id":999999,
extern uint32_t cntlength ;//__attribute__((section("tcpsection")));
static uint8_t __attribute__((externally_visible)) qrbuffer[1733]; ;
//I2C section
//const uint16_t I2CAdd = 0x78;

extern uint8_t qchan[2];
//uint8_t qprice[4];
extern uint32_t translngth;

extern uint8_t * searchbufa;

//uint8_t headerbuf[1460];

extern uint32_t price;

/*Fixed messages 18 characters max*/
static const uint8_t merrefstr[] = "\"merchantReference\":\""; //21 characters ref at 22
static const uint8_t lengthstr[] = "Content-Length: ";//15 characters Length at 16
static const uint8_t pricemsg[] = " Price R";
static const uint8_t scanmsg[] = " Scan qr to vend";//16 characters
static const uint8_t aprovemsg[] = "Amount Approved";
static const uint8_t declinemsg[] = "Amount Declined";
static const uint8_t clockdate[] = "  Date:";
static const uint8_t clocktime[] = "  Time:";

void Start_TMR4(void);

void Start_TMR1(void);
    
void Delay_60mil(void);

void Write_Font(uint8_t _font);

void Set_Page(uint8_t gpage);

void Set_Column(uint8_t col);

void Set_Line(uint8_t line);//Start from line

void Clr_Line(void);//Clear the current line

void Write_String(uint8_t *lcdstring, uint8_t lcdline);

void Continue_String(uint8_t *clcdstring);

void Graphic_Clear(void);

void Graphic_qrcode(uint32_t amount, uint8_t id);

void Write_Qrcode(void);

void Store_XPM(uint8_t *xpmname);

void printQr(uint8_t qrcode[]);

void Graphic_test(void);

void Convert_price(uint32_t prval);

void displ_hex(uint32_t hexnum);

void Graphic_init(void);

void Load_Qrcode(const uint8_t xpmname[]);

void SPI_write8bit(uint8_t data);

void Delay_abit();

void Sample_code(void);

I2C2_MESSAGE_STATUS ssd1306_write(uint8_t *pdata, uint8_t msize, uint8_t command);

I2C2_MESSAGE_STATUS I2C_Write_Command(uint8_t mlength);

I2C2_MESSAGE_STATUS I2C_Write_Data(uint8_t mlength);

I2C2_MESSAGE_STATUS I2C_Write_Address(uint8_t mlength);

void I2c_write_block(uint8_t *sourceData, uint8_t length, I2C2_MESSAGE_STATUS stat);
//void disp_clock(uint8_t* tgsdate, uint8_t* tgstime);

void gsm_zerobuff(uint8_t* gsmsgbuf, uint16_t count );

void gsm_waitx(void);

void gsm_waitr(void);

void gsm_transmit(uint8_t txbyte);

void gsm_gettime(void);

void get_radio(void);

void sig_strength(void);

void check_num(void);

void parse_sms(void);

void gsm_numack(void);

void gsm_getbalance(void);

void gsm_setime(void);

void parse_date_time(void);

uint8_t gsm_unsolic(void);

void clock_display(void);

void start_sms(void);

void sms_report(void);

void delay_second(uint8_t stime);

void delay_milli(uint8_t mtime);

uint8_t write_sms(uint8_t i, uint8_t *msgpnt);

uint8_t* convert_hex(uint32_t hexnum);

void gsm_receive(uint8_t noofline, uint8_t *messagebuf);

void gsm_msg(uint8_t *msgadd);

void gsm_init(void);

void gsm_txAT(void);

void gsm_on(void);

uint8_t gsm_Read(void);

void gsm_off(void);

void gsm_netwait(void);

uint8_t EUSARTG_Read(void);

/** Prototypes from tcpip.h */
void tcp_httpget(uint8_t httpurl[128], bool sslflag);

void http_receive(uint8_t noofline, uint8_t *messagebuf);

uint32_t ascnumtohex(uint8_t *numberbuf);

int tls_get_payment(void);

void tls_getseed(void);

int OpenConnection(void);

#ifdef __unix
int sock_read(void *ctx, unsigned char *buf, size_t len);

int sock_write(void *ctx, const unsigned char *buf, size_t len);
#endif //__unix

void tgsm_msg(uint8_t *msgadd);

void tgsm_receive(uint8_t noofline, uint8_t *messagebuf);

/** Unix serial prototypes */

void set_blocking(int fds, int should_block);

int set_interface_attribs(int fd, uint32_t speed, int parity);

bool gsm_waitstart(void);

void ntp_connect(void);

bool tcp_getip(void);

void tcp_getsnapscan(bool getpayment);

void tcp_gethead(void);

void tcp_close(void);

void get_snaprecord(void);

uint8_t tcp_getid(void);

void tcp_connect(void);

void tcp_ping(void);

void tcp_httpget(uint8_t httpurl[128], bool sslflag);

void http_receive(uint8_t noofline, uint8_t *messagebuf);

uint32_t ascnumtohex(uint8_t *numberbuf);

void tgsm_msg(uint8_t *msgadd);

void tgsm_receive(uint8_t noofline, uint8_t *messagebuf);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
