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
//#include "gsm.h"
/*unsigned char rtbuf[2048];
unsigned char ttbuf[8192];*/
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
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TCPIP_H */

