/* 
 * File:   gsm.h
 * Author: Dave Plater
 *
 * Created on September 26, 2018, 3:14 PM
 */

#ifndef GSM_H
#define	GSM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <string.h>
//#include "vend.h"
#include "buffers.h"
#include <xc.h>
#include "mcc_generated_files/mcc.h"

//GSM eeprom storage locations from 0x40 onwards
//Nine digits for allowed phone number.
const uint16_t phonenum = 0x60;

//GSM unsolicited replies for comparison

const uint8_t cmti[] = "+CMTI";
const uint8_t pnum[] = "\"+27766520007\"\r";
const uint8_t spnum[] = "766520007";
const uint8_t anum[] = "\"+27834604609\"\r";
const uint8_t sanum[] = "27834604609";
const uint8_t ackmsg[] = "Message received";
const uint8_t mtmpcm[] = "*121*";
const uint8_t vdcpcm[] = "*140*";

//GSM messages sms
const uint8_t sendms[] = "AT+CMGS=";
const uint8_t smsnmd[] = "AT+CNMI=2,1,0,0,0\r";
const uint8_t smdqry[] = "AT+CSMS?\r";
const uint8_t smsdel[] = "AT+CMGDA=\"DEL ALL\"\r";
const uint8_t smslst[] = "AT+CMGL=\"ALL\"\r";
const uint8_t smscap[] = "AT+CMGL=?\r";
const uint8_t smstxt[] = "AT+CMGF=1\r";
//other
const uint8_t softid[] = "AT+CGMR\r";
const uint8_t alphon[] = "AT+CCPD=1";
const uint8_t alpoff[] = "AT+CCPD=0";
const uint8_t pvdnam[] = "AT+CSPN?\r";
const uint8_t engqry[] = "AT+CENG=2\r";
const uint8_t engfmt[] = "AT+CENG=?";
const uint8_t engoff[] = "AT+CENG=0\r";
const uint8_t noecho[] = "ATE0;V0\r";
//USSD
const uint8_t usdtst[] = "AT+CUSD=?\r";
const uint8_t ussdrd[] = "AT+CUSD?\r";
const uint8_t ussdwe[] = "AT+CUSD=1\r";
const uint8_t ussdwc[] = "AT+CUSD=2\r";
const uint8_t ussdwv[] = "AT+CUSD=1,\"*135*500#\"\r";
const uint8_t ussdwm[] = "AT+CUSD=1,\"*136#\"\r";
const uint8_t ussdw2[] = "AT+CUSD=1,\"*136#\",2\r";
const uint8_t setgsm[] = "AT+CSCS=\"GSM\"\r";
const uint8_t airtim[] = "AT+CUSD =1\r";
//Other
const uint8_t prodid[] = "ATI\r";
const uint8_t dconfg[] = "AT&V\r";
const uint8_t ownnum[] = "AT+CNUM\r";
const uint8_t clockr[] = "AT+CCLK?\r";
const uint8_t clockw[] = "AT+CCLK=";
const uint8_t pwrsta[] = "AT+CBC\r";
const uint8_t loctim[] = "AT+CIPGSMLOC=2\r";
const uint8_t nettst[] = "AT+CLTS=1\r";
const uint8_t netoff[] = "AT+CLTS=0\r";
const uint8_t baudra[] = "AT+IPR=19200\r";
const uint8_t facres[] = "AT&F0\r";
const uint8_t tsoftid[] = "AT+CGMR\r";

struct
{
    unsigned retransmit : 1;
    unsigned meerror : 1;
    unsigned mtn : 1;
    unsigned msgavl : 1;
    unsigned abrtmsg : 1;
    unsigned eomsg : 1;
    unsigned msggod : 1;
    unsigned cfun : 1;
} gsmflags;
//Message strings for 20x4 LCD
const uint8_t clrline[] ="                    ";
const uint8_t inscoin[] = "Insert Notes & PressLit Button To Vend" ;
const uint8_t nochange[] = "No Change Use Exact      Amount!";
const uint8_t credits[] = "  Credit = R";
const uint8_t emptymsg[] = "No Stock";
const uint8_t pricesetmsg[] = "   Price set mode";
const uint8_t pricesetm2[] = "Press channel button    to set price      Service = Exit";
const uint8_t vendsetup[] = "Push 1 Vend Time,   2 ChanLink 3 SensOff4 ClrTot 5 FacReset 8 exit";
const uint8_t setimemsg[] = "Push channel button Push service to exit";
const uint8_t sensoffms[] = "Hold channel button or Push service to  exit";
const uint8_t vendtimem[] = "Push 1 = +.5 second Push 2 = -.5 second ";
const uint8_t chanlinkm[] = "Press channel button    to link to      Service = Exit";
const uint8_t linkmsg[] = "linked to :";
const uint8_t chanmsg[] = "   Channel ";
const uint8_t timemsg[] = "Time in 1/2sec = ";
const uint8_t pricemsg[] = "Price R";
const uint8_t priceexit[] ="Press service to exit";
const uint8_t auditmsg[] = "  Audit Mode";
const uint8_t hoppcoin[] = "Hopper Coin         Button 1 = + & 2 = - Value = R";
const uint8_t senset[] = "  Setup Sensor";
const uint8_t credclr[] = "Push button 1 to clear credits   and exit";
const uint8_t vendtest[] = " Push button to     vend";
const uint8_t notetest[] = "  Insert Note";
//const uint8_t exit[] = "Exit";
const uint8_t servmsg[] = "1 = Audit 2 = Sensor3=Hop-Coin 4=Note-en5=Cred-clr 6=Prices 7=Vend setup 8=Exit";
const uint8_t noteerr[] = "   Note error     code = 0x";
const uint8_t inithop[] = "  Initialize Hopper";
const uint8_t initnote[] = "     Initialize          Note Reader";
const uint8_t setnotes[] = "Enable / Disable    1 = R10, 2 = R20    3 = R50, 4 = R100   5 = R200";
const uint8_t tenrand[] = "   R10  ";
const uint8_t twentyrand[] = "  R20  ";
const uint8_t fiftyrand[] = "  R50  ";
const uint8_t hundredrand[] = "  R100 ";
const uint8_t twohundredrand[] = "  R200 ";
const uint8_t enabled[] = " enabled ";
const uint8_t disabled[] = " disabled";
const uint8_t creditclr[] = "Credits Cleared";
const uint8_t sensmsg[] = "Sensor is ";
const uint8_t onmsg[] = "On ";
const uint8_t offmsg[] = "Off";
const uint8_t clrmsg[] = "         ";
const uint8_t dacmsg[] = "Sensitivity ";
const uint8_t motimemsg[] = " Press Channel Vend Button or Press       Service to Exit";
const uint8_t settimemsg[] = "Press 1 = + or 2 = -  Press 8 to Exit";
const uint8_t chanlinkmsg[] = "Push Button to Link Push again to UnlinkPush Service to Exit";
const uint8_t chanresetmsg[] = "Reset to Default    Start Again";
const uint8_t sensoffmsg[] = "Push 1 = On, 2 = Off, 8 = Exit";
const uint8_t totalmsg[] = "Total R";
const uint8_t cashinmsg[] = "Cash in R";
const uint8_t totalvendsm[] = "Vends ";
const uint8_t vendispmsg[] = "Use button / Service";
const uint8_t coinsout[] = "coins out ";
const uint8_t coinvalu[] = " @ coin = R";

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

uint8_t write_sms(uint8_t i, uint8_t *msgpnt);

uint8_t* convert_hex(__uint24 hexnum);

void gsm_receive(uint8_t noofline, uint8_t messagebuf[]);

void gsm_msg(uint8_t *msgadd);

void gsm_init(bool inittype);

void gsm_txAT(void);

uint8_t gsm_on(void);

uint8_t gsm_Read(void);

void gsm_off(void);

void gsm_netwait(void);

uint8_t EUSARTG_Read(void);

void EUSARTG_Write(uint8_t txData);

int int_sms_notify();

int gsmint_receive( uint8_t messagebuf[] );

void Read_SMS(void);

#ifdef	__cplusplus
}
#endif

#endif	/* GSM_H */

