/* 
 * File:   gsm.h
 * Author: Dave Plater
 * Ported from PIC18F47KXX
 *
 * Created on 20 June 2020, 1:46 PM
 */

#ifndef GSM_H
#define	GSM_H

#ifdef	__cplusplus
extern "C" {
#endif


//#include <stdbool.h>
/*#include <stdint.h>
#include <stdio.h>*/
#include "mcc_generated_files/mcc.h"
//uint8_t gsmmsg[512];

/*#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <bearssl.h>
*/
const uint8_t tsoftid[] = "AT+CGMR\r";
const uint8_t clockr[] = "AT+CCLK?\r";
const uint8_t setgsm[] = "AT+CSCS=\"GSM\"\r";
const uint8_t ussdwm[] = "AT+CUSD=1,\"*136#\"\r";
const uint8_t ussdwv[] = "AT+CUSD=1,\"*135*500#\"\r";
const uint8_t noecho[] = "ATE0;V0\r";
const uint8_t engqry[] = "AT+CENG=2\r";
const uint8_t engoff[] = "AT+CENG=0\r";
const uint8_t ussdwc[] = "AT+CUSD=2\r";

	/** Imported from tcpip.c */
	//to close TCP Port Explicitly means disconnect connection if any
	/*extern const uint8_t shuttcp[];
	//Checking SIM card has internet connection or not
	extern const uint8_t tcptest[];
	//"APN","userName","Pass" :- connect to internet
	extern const uint8_t tcpconn[];
	//bring up with the wireless network.
	extern const uint8_t tcpup[];
	//get IP
	extern const uint8_t tcpgetip[];
	extern const uint8_t snapurl[];*/
	//#include "display.h"
/** tls_client defines */

//uint8_t timebuf[32];


#if 0
extern uint8_t gsmmsg[512];
//sms storage
//ussd storage
extern uint8_t gsmusd[128];
//Store unsolicited notifications
extern uint8_t gsmusm[24];
extern uint8_t gsmtim[23];
//Store date
extern uint8_t msg.gsdate[10];
//Store time
extern uint8_t msg.gstime[10];
//Phone number scratch pad
uint8_t phnumb[11];
uint8_t noofline;
#endif
//uint16_t tpindex;



//GSM unsolicited replies for comparison

#if 1
const uint8_t cmti[] = "+CMTI";
const uint8_t pnum[] = "\"+27766520007\"\r";
const uint8_t spnum[] = "27766520007";
const uint8_t anum[] = "\"+27834604609\"\r";
const uint8_t sanum[] = "27834604609";
const uint8_t ackmsg[] = "Message received";
const uint8_t mtmpcm[] = "*121*";
const uint8_t vdcpcm[] = "*140*";

//GSM messages status
const uint8_t sigstr[] = "AT+CSQ\r";
const uint8_t pintest[] = "AT+CPIN?\r";

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
const uint8_t engfmt[] = "AT+CENG=?";
//USSD
const uint8_t usdtst[] = "AT+CUSD=?\r";
const uint8_t ussdrd[] = "AT+CUSD?\r";
const uint8_t ussdwe[] = "AT+CUSD=1\r";
const uint8_t ussdw2[] = "AT+CUSD=1,\"*136#\",2\r";
const uint8_t airtim[] = "AT+CUSD =1\r";
//Other
const uint8_t prodid[] = "ATI\r";
const uint8_t dconfg[] = "AT&V\r";
const uint8_t ownnum[] = "AT+CNUM\r";
const uint8_t clockw[] = "AT+CCLK=";
const uint8_t pwrsta[] = "AT+CBC\r";
const uint8_t loctim[] = "AT+CIPGSMLOC=2\r";
const uint8_t nettst[] = "AT+CLTS=1\r";
const uint8_t netoff[] = "AT+CLTS=0\r";
const uint8_t baudra[] = "AT+IPR=19200\r";
const uint8_t facres[] = "AT&F0\r";
#endif

#endif	/* GSM_H */

