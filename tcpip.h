/* 
 * File:   tcpip.h
 * Author: Dave Plater
 *
 * Created on June 23, 2020, 4:00 PM
 */

#ifndef TCPIP_H
#define	TCPIP_H

#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "buffers.h"
#include "gsm.h"
#include <stdio.h>
//#include "gsm.h"
/*unsigned char rtbuf[2048];
unsigned char ttbuf[8192];*/
uint32_t rdcount;
uint32_t tdcount;
#define time_t uint32_t
struct
{
    unsigned declined : 1;
    unsigned approved : 1;
    unsigned poll : 1;
    unsigned timer4 : 1;
    unsigned swclosed : 1;
    unsigned inittype : 1;
    unsigned spare4 : 1;
    unsigned spare5 : 1;
} vendflags;

const uint16_t merch64key = 0x10; //non volatile store for base 64 merchant key
 
/*const uint8_t rsgettest[] = "GET /web/ma/myaccount/ HTTP/2/r/n \
Host: za.rs-online.com\r\n \
authorization: Basic ZGF2ZXBsOmRhdmUxOTU0\r\n \
user-agent: curl/7.67.0\r\n \
accept: *///\r\n \
\r\n";
//
/*

const uint8_t httpinit[] = "AT+HTTPINIT\r";
const uint8_t httphead[] = "AT+HTTPHEAD\r";
const uint8_t httpsetp[] = "AT+HTTPPARA=\"CID\",1\r";
const uint8_t httpsnap[] = "AT+HTTPPARA=\"URL\",\"pos.snapscan.io/merchant/api/v1/payments\"\r";//\0
const uint8_t httpudat[] = "AT+HTTPPARA=\"USERDATA\",\"22d3cf4f-db05-4609-9773-2312375b4523:@\"\r";
const uint8_t httpcont[] = "AT+HTTPPARA=\"CONTENT\",\"22d3cf4f-db05-4609-9773-2312375b4523:@\"\r";
const uint8_t httpuagt[] = "AT+HTTPPARA=\"UA\",\"22d3cf4f-db05-4609-9773-2312375b4523:@\"\r";
// base64 = MjJkM2NmNGYtZGIwNS00NjA5LTk3NzMtMjMxMjM3NWI0NTIzOg==
//This is for https it comes after httpurl
const uint8_t httpredir[] = "AT+HTTPPARA=\"REDIR\",1\r";
//This enables SSL for HTTPS
const uint8_t httpssl[] = "AT+HTTPSSL=1\r";
const uint8_t httpsslo[] = "AT+HTTPSSL=0\r";
//Method 0 = GET, 1=POST, 2=HEAD. Returns +HTTPACTION: <Method>,<StatusCode>,<DataLen>
//Status code of 200 is success.
const uint8_t httpget[] = "AT+HTTPACTION=0\r";
const uint8_t httphed[] = "AT+HTTPACTION=2\r";
const uint8_t httpread[] = "AT+HTTPREAD\r";
const uint8_t httpterm[] = "AT+HTTPTERM\r";
*/
bool gsm_waitstart(void);

void ntp_connect(void);

bool tcp_getip(void);

void tcp_getsnapscan(bool getpayment);

bool tcp_gethead(bool getid);

void tcp_close(void);

bool get_snaprecord(void);

uint8_t tcp_getid(void);

void tcp_connect(void);

void tcp_ping(void);

void tcp_httpget(uint8_t httpurl[128], bool sslflag);

void http_receive(uint8_t noofline, uint8_t *messagebuf);

uint32_t ascnumtohex(uint8_t *numberbuf);

void tgsm_msg(uint8_t *msgadd);

void Delay_60mil(void);

void snap_incid(void);

void tgsm_receive(uint8_t noofline, uint8_t *messagebuf);



#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TCPIP_H */

