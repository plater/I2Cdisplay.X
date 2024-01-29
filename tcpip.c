/* 
 * File:   tcpip.c
 * Author: Dave Plater
 *
 * Created on June 23, 2020, 4:00 PM
 */
#include "tcpip.h"
#include <string.h>
#include <xc.h>
#include "mcc_generated_files/mcc.h"

#if 0
struct
{
    unsigned retransmit : 1;
    unsigned meerror : 1;
    unsigned mtn : 1;
    unsigned msgavl : 1;
    unsigned abrtmsg : 1;
    unsigned eomsg : 1;
    unsigned msggod : 1;
    unsigned sigtest : 1;
} gsmflags;
#endif
#define time_t uint32_t


//End of gsm.h declarations

#if 0
//Ping an ip
const uint8_t pingip[] = "AT+CIPPING=\"za.rs-online.com\"\r";

const uint8_t brrqry[] = "AT+SAPBR=2,1\r";
const uint8_t brrqry1[] = "AT+SAPBR=4,1\r";
const uint8_t brrclose[] = "AT+SAPBR=0,1\r";
const uint8_t mercid[] = "CMMCyv0i";
const uint8_t apikey[] = "22d3cf4f-db05-4609-9773-2312375b4523";
const uint8_t tcpstatus[] = "AT+CIPSTATUS\r";
const uint8_t decapikey[] = "MjJkM2NmNGYtZGIwNS00NjA5LTk3NzMtMjMxMjM3NWI0NTIzOg==";

const uint8_t sslopt[] =  "AT+SSLOPT=1,1\r";
const uint8_t startssl[] = "AT+CIPSSL=1\r";
const uint8_t simurl[] = "AT+CIPSTART=\"TCP\",\"data.sparkfun.com\",\"80\"\r";
const uint8_t rsurl[] = "AT+CIPSTART=\"TCP\",\"104.75.216.116\",\"443\"\r";
const uint8_t starttran[] = "AT+CIPSEND\r\n";
#endif
/** Imported from tcpip.c */
//to close TCP Port Explicitly means disconnect connection if any
const uint8_t shuttcp[] = "AT+CIPSHUT\r";
//Checking SIM card has internet connection or not
const uint8_t tcptest[] = "AT+CGATT?\r";
//"APN","userName","Pass" :- connect to internet
const uint8_t tcpconn[] = "AT+CSTT=\"internet\",\"\",\"\"\r";
//bring up with the wireless network.
const uint8_t tcpup[] = "AT+CIICR\r";
//get IP
const uint8_t tcpgetip[] = "AT+CIFSR\r";
//Test http
//const uint8_t clockr[] = "AT+CCLK?\r";
const uint8_t brrgprs[] = "AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r";
const uint8_t brrapn[] = "AT+SAPBR=3,1,\"APN\",\"internet\"\r";
const uint8_t brropen[] = "AT+SAPBR=1,1\r";
const uint8_t brrclose[] = "AT+SAPBR=0,1\r";
//SNTP sync
const uint8_t ntpbp1[] = "AT+CNTPCID=1\r";
const uint8_t ntpsrv[] = "AT+CNTP=\"za.pool.ntp.org\",0\r";
const uint8_t ntpstr[] = "AT+CNTP\r";

const uint8_t tcpfun[] = "AT+CFUN=1\r";
const uint8_t funtest[] = "AT+CFUN?\r";

const uint8_t snapurl[] = "AT+CIPSTART=\"TCP\",\"pos.snapscan.io\",\"443\"\r";
const uint8_t snapgetid[] = "GET /merchant/api/v1/payments/";
const uint8_t snapnoid[] = "HTTP/1.1\r\n";
const uint8_t snapcommon[] = "Host: pos.snapscan.io\r\n\
Authorization: Basic ";
const char snapurlh[] = "GET /merchant/api/v1/payments/ HTTP/1.1\r\nHost: pos.snapscan.io\r\n\
Authorization: Basic %sUser-Agent: curl/7.79.1\r\nAccept: */*\r\n\r\n";
//MjJkM2NmNGYtZGIwNS00NjA5LTk3NzMtMjMxMjM3NWI0NTIzOg==\r\n\;
const uint8_t snapcommon1[] = "User-Agent: curl/7.71.1\r\n\
Accept: */*\r\n\r\n";
const uint8_t snapgettran[] = "GET /merchant/api/v1/payments/ HTTP/1.1\r\n\
Host: pos.snapscan.io\r\n\
Authorization: Basic ";
//MjJkM2NmNGYtZGIwNS00NjA5LTk3NzMtMjMxMjM3NWI0NTIzOg==\r\n\

const uint8_t snapgettran1[] = "User-Agent: curl/7.71.1\r\nAccept: */*\r\n\r\n";

/*Fixed messages 18 characters max*/
static const uint8_t merrefstr[] = "\"merchantReference\":\""; //21 characters ref at 22
static const uint8_t lengthstr[] = "Content-Length: ";//15 characters Length at 16
//static const uint8_t pricemsg[] = " Price R";
static const uint8_t scanmsg[] = " Scan qr to vend";//16 characters
static const uint8_t aprovemsg[] = "Amount Approved";
static const uint8_t declinemsg[] = "Amount Declined";

/*Host: pos.snapscan.io\r\
Authorization: Basic MjJkM2NmNGYtZGIwNS00NjA5LTk3NzMtMjMxMjM3NWI0NTIzOg==\r";
User-Agent: curl/7.67.0\r\
Accept: *\r\
\r\n" ;
*/
//Gsm related memory declared extern in gsm.h
uint8_t tgsmbyte = 0;
//store compare time
uint8_t comptime[10];
/*uint8_t transid[10] __attribute__((section("tcpsection")));//195
uint32_t cntlength __attribute__((section("tcpsection")));*/
//base64_encode(fmerchkey, (idx_t)keysize, base64buf, (idx_t) 58);
const uint16_t midstore = 0x60;
const uint16_t keystore = 0x10;
const uint16_t cntstore = 0x50; //LSB first little endian, 8 bytes long
/*+CMGR: "REC UNREAD","+27766520007","Dave Plater","22/07/19,12:47:35+08"
KEY = 22d3cf4f-db05-4609-9773-2312375b4523:
0*/
const uint8_t fmerchkey[] = "+CMGR: \"REC UNREAD\",\"+27766520007\",\"Dave Plater\",\"22/07/19,12:47:35+08\"\
KEY = 22d3cf4f-db05-4609-9773-2312375b4523:";

void store_merchkey(void)
{
//    strcpy(gsmmsg, fmerchkey);// For debugging only
    size_t b64key; //Size of base 64 encoded merchant key
    uint8_t *y;
    uint8_t *z;
    uint8_t x;
    x = sizeof(snapgettran);
    y = strstr(gsmmsg, "KEY = ");
    z = strchr(y, (int)':');
    z[1] = 0;
    strcpy(merchkey, (const uint8_t*)y + (sizeof("KEY = ") - 1));
    size_t keysize = strlen(merchkey);
    base64_encode(merchkey, (idx_t)keysize, base64buf, (idx_t)64);
    b64key = strlen(base64buf);
    base64buf[b64key] = '\r';
    base64buf[b64key +1] = '\n';
    base64buf[b64key +2] = 0;
    x = 0;
    while(x < b64key)
    {
        tgsmbyte = base64buf[x];
        DATAEE_WriteByte(keystore + x, tgsmbyte);
        x++;
    }
    DATAEE_WriteByte(keystore + x, 0);
    DATAEE_WriteByte(cntstore + 8, 0xFF);
}

//,"snapCode":"CMMCyv0i",
void store_mid(void)
{
    uint8_t *y;
    uint8_t *z;
    uint8_t x;
    y = strstr(gsmmsg, "MID = ");
    z = strchr(y, (int)':');
    z[0] = 0;
    strcpy(merchid, (const uint8_t*)y + (sizeof("MID = ") - 1));
    size_t keysize = strlen(merchid);
    x = 0;
    while(x < keysize)
    {
        tgsmbyte = merchid[x];
        DATAEE_WriteByte(midstore + x, tgsmbyte);
        x++;
    }
    DATAEE_WriteByte(midstore + x, 0);
    DATAEE_WriteByte(cntstore + 8, 0xFF);
}

bool check_mid()
{
    
}

void gprs_off(void)
{
    gsm_msg((uint8_t*)"AT+SAPBR=0,1\r");//"AT+SAPBR=0,1\r"
    gsm_receive(1, gsmusd);
    gsm_msg((uint8_t*)"AT+CIPSHUT\r");//CIPSHUT
    Read_timeout2(gsmusd);
}

void mid_init(void)
{
    uint8_t x;
    x = 0;
    tgsmbyte = 0xFF;
    while(tgsmbyte > 0)
    {
        tgsmbyte = DATAEE_ReadByte(midstore + x);
        merchid[x] = tgsmbyte;
        x++;
        if(x > (sizeof(merchid)))
        {
            x--;
            break;
        }
    }
     merchid[x - 1] = 0;

}

void mkey_init(void)
{
    uint8_t x;
    x = 0;
    tgsmbyte = 0xFF;
    while(tgsmbyte > 0)
    {
        tgsmbyte = DATAEE_ReadByte(keystore + x);
        base64buf[x] = tgsmbyte;
        x++;
        if(x > (sizeof(base64buf)-2))
        {
            x--;
            break;
        }
    }
    base64buf[x - 1] = 0;
    base64buf[x] = 0;
    base64buf[x + 1] = 0;
    //int memcmp(const void *s1, const void *s2, size_t 4);
    long long iserased = 0xFFFFFFFFFFFFFFFF;
    int y = memcmp(base64buf, &iserased, 8);
    if(y == 0) //If eeprom contains 0xFFFFFFFF then it needs to be initialized
    {
        Orange_light(); //display orange light until setup button pressed
        Read_SMS();
    }
}

void Orange_light(void)
{
    uint8_t x = 0;
    while(SERVICE_PORT)
    {
        if(x)
        {
            led_switch(1);
            x = 0;
        }
        else
        {
            led_switch(0);
            x = 1;
        }
        delay_10mS(1);

    }
}
//translngth = sprintf(transid, "%d HTTP/1.1\r\n", cntlength);

void tcp_connect(void)
{
	static char searchbuf[32];
tcprep:
//    Read_timeout(gsmusm);
/*    gsm_msg((uint8_t*)shuttcp);//CIPSHUT
    gsm_receive(2, gsmusd);*/
    gsm_msg((uint8_t*)tcptest);//CGATT? is attached to GPRS?
    gsm_receive(2, gsmusd);//gsmusd[8] must equal '1' then gprs is connected
    if(gsmusd[8] != '1')
    {
        gsm_msg("AT+CGATT=1\r");
        gsm_receive(1, gsmusd);
        goto tcprep;
    }
//	SEARCH for "+CGATT: 1"
/*	searchbufa = strstr((const char*) gsmusd, "+CGATT: 1");
	if(gsmusd[8] != '1')
	{
        
        led_switch(3); //LED toggle GREEN
        __delay_ms(10);
		goto tcprep;
	}*/
}

bool tcp_getip(void)
{
    gsm_msg((uint8_t*)tcpconn);//CSTT="Internet"
    gsm_receive(1, gsmusd);
    gsm_msg((uint8_t*)tcpup);//CIICR
    Read_timeout2(gsmusd);
    if(gsmusd[0] != '0')
    {
        led_switch(1);
        gsm_msg((uint8_t*)shuttcp);//CIPSHUT
        Read_timeout2(gsmusd);
        return 1;
    }
    gsm_msg((uint8_t*)tcpgetip);//CIFSR
    Read_timeout2(gsmusd);
    return 0;
}

void ntp_connect(void)
{
    led_switch(1);
    tcprep:
    gsm_msg((uint8_t*)brrclose);//"AT+SAPBR=0,1\r"
    gsm_receive(1, gsmusd);
    gsm_msg((uint8_t*)shuttcp);//CIPSHUT
    Read_timeout2(gsmusd);
    tcp_connect();
    if(tcp_getip())
    {
        led_switch(3); //LED toggle GREEN
        goto tcprep;
    }
    gsm_msg((uint8_t*)brrgprs);//AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r"
    gsm_receive(1, gsmusd);
    gsm_msg((uint8_t*)brrapn);//"AT+SAPBR=3,1,\"APN\",\"internet\"\r"
    gsm_receive(1, gsmusd);
    gsm_msg((uint8_t*)brropen);//"AT+SAPBR=1,1\r"
    gsm_receive(1, gsmusd);
    if(gsmusd[0] != '0')
    {
        gsmusd[1] = 0;
        goto tcprep;
    }
    gsm_msg((uint8_t*)ntpbp1);//"AT+CNTPCID=1\r" Use bearer profile 1
    gsm_receive(1, gsmusd);
    gsm_msg((uint8_t*)"AT+CNTP=\"za.pool.ntp.org\",0\r");//"AT+CNTP=\"za.pool.ntp.org\",0")
    gsm_receive(1, gsmusd);
    //Synchronize to ntp public server
    gsm_msg((uint8_t*)ntpstr);//AT+CNTP start ntp clock"AT+CNTP\r"
    gsm_receive(3, gsmusd);
    if (gsmusd[12] != '1')
    {
        RLED_Toggle(); //LED toggle GREEN
        goto tcprep;
    }
    gsmflags.msggod = 1;
// PLEASE FIXME    gsm_gettime(); Careful the value of i in parse date time exceeds it's limit
    __asm__("NOP");
}

void tcp_getsnapscan(bool getpayment)
{
    noip:
    tcp_connect();
    if(tcp_getip())
    {
        goto noip;
    }
    led_switch(0);
    gsm_zerobuff(qrbuffer, 254);
    gsm_zerobuff(gsmmsg, 511);
    gsm_zerobuff(gsmusd, 127);
/*	gsm_msg((uint8_t*)"AT+CIPSSL=0\r");
	gsm_receive(1, gsmusd);
*//** Enable built in tls*/
	gsm_msg((uint8_t*)"AT+CIPSSL=1\r");
	gsm_receive(1, gsmusd);

	gsm_msg((uint8_t*)snapurl);//"AT+CIPSTART=\"TCP\",\"pos.snapscan.io\",\"443\"\r";
    gsm_receive(1, gsmtim);
    if(gsmtim[0] != '0')
    {
        gsmflags.retransmit = 0;
        goto noip;
    }
	gsm_receive(2, gsmusd);//0\r\n \r\nCONNECT OK\r\n (1\r\n)
    if(gsmflags.retransmit)
    {
        gsmflags.retransmit = 0;
        goto noip;
    }
    int x = strstr(gsmusd, "CONNECT OK");
    if(!x)
    {
        x = 0;
        goto noip;
    }
    led_switch(0);
	gsmflags.msgavl = 1;
	gsmflags.eomsg = 0;
/** Use built in tls over tcp */
	gsm_msg((uint8_t*)"AT+CIPSEND\r");
	gsmflags.abrtmsg = gsm_waitstart();//Wait for >
    gsm_msg(snap64buf);
	gsm_transmit(0x1A); //Send Ctrl+Z at end of transmission
    ClrWdt();
}


uint8_t tcp_getid(void)
{
    tcp_getsnapscan(1);
    gsmflags.msgavl = tcp_gethead(1);
    led_switch(0); // Green = 0;
    if(gsmflags.meerror)
    {
        led_switch(1);
        return NULL;
    }
    gsmflags.msgavl = 1;
	int z = 0;
    int x;
    while(gsmflags.msgavl)
    {
        tgsmbyte = gsm_Read();
        if(tgsmbyte == '}')
        {
            gsmflags.msgavl = 0;
            gsmmsg[z++] = NULL;
            break;
        }
        gsmmsg[z++] = tgsmbyte;        
    }
    tcp_close();
    led_switch(0); // Green = 0;
    /*HTTP/1.1 404 Not Found*/
    searchbufa = strstr(gsmusd, "404 Not Found"); //0x13D
    if(searchbufa)
    {
        return NULL;
    }

    searchbufa = strstr(gsmmsg, "Payment not found");
    if(searchbufa)
    {
        //payment id doesn't exist yet
        return NULL;
    }
    //int strcmp(const char *s1, const char *s2);
    //,"snapCode":"CMMCyv0i",
    searchbufa = strstr(gsmmsg, "\"snapCode\":\"");
    searchbufa = searchbufa + strlen("\"snapCode\":\""); //begin MID
    int s = strncmp(searchbufa, merchid, 8);
    if(s != 0)
    {
        snap_incid();
        return NULL; //Not this machine
    }
    searchbufa = strstr(gsmmsg, "\"status\":\"error\"");
    if(searchbufa)
    {
        //Case where payment declined
//        Graphic_Clear();
//        Write_String(declinemsg, 3);
        snap_incid();
        return 0xFF;
    }
    searchbufa = strstr(gsmmsg, "\"status\":\"completed\"");
    if(searchbufa)
    {
        searchbufa = strstr(gsmmsg, "\"merchantReference\":\"");
        searchbufa = searchbufa + 25;
        searchbufa[1] = 0;
        channum = atoi((const char*)searchbufa);
        channum--; //chan 1 is actually motor 0
        snap_incid();
        searchbufa = strstr(gsmmsg, "\"totalAmount\":");
        searchbufa = searchbufa + 14;
        z = 0;
        x = 0;
        while(z != ',')
        {
            z = searchbufa[x];
            x++;
        }
        x--;
        searchbufa[x] = NULL;
        price = atoi((const char*)searchbufa);
        return 1;
    }
    return NULL;
    
}

void snap_incid(void)
{
    Store_Count(); //Store last completed transaction id
    ++cntlength; // Next transaction id
    build_url();
}

bool tcp_gethead(bool getid)
{
    int x;
	int z = 0;
    gsmflags.abrtmsg = 1;
//	uint8_t buf[1850];//1850 - 1455 = 395
    gsm_receive(3, gsmusd);
    x = strstr(gsmusd, "HTTP/1.1 200 OK");
    if(!x && !getid)
    {
        gsmflags.abrtmsg = 0; //error
//        tcp_close();
        return 0;
    }
    httpf:
    //Ignore unecessary data
    x = 0;
    while(tgsmbyte != 'X')
    {
        tgsmbyte = gsm_Read();
        if(gsmflags.meerror)
        {
            led_switch(1);
            return 0;
        }
    }
    //Look for "X-Total: 71"
    x = NULL;
    while(x == NULL)
    {
        gsm_receive(1, qrbuffer);
        x = strstr(qrbuffer, "X-XSS-Protection:");
    }
    z = 33;
    while(gsmflags.msgavl)
    {
        tgsmbyte = gsm_Read();
        qrbuffer[z++] = tgsmbyte;
        if(tgsmbyte == '{')
        {
            gsmflags.msgavl = 0;
            qrbuffer[z++] = NULL;
            qrbuffer[z++] = NULL;
            return 1; //Get header success
        }
     }
    return 0;
}

void tcp_close(void)
{
    repshut:
	gsm_msg((uint8_t*)shuttcp);//CIPSHUT
	gsm_receive(1, gsmusm);
    if(gsmusm[0] == '4')
    {
        goto repshut;
    }
    Read_timeout(gsmusm);
    NOP();
}
//Read until 10 mS timeout
uint8_t Read_timeout(uint8_t *msgadd)
{
    uint8_t v = 0;
    TMR3_Initialize();
    T3CONbits.TMR3ON = 1;
    while(!PIR4bits.TMR3IF)
    {
        if(PIR3bits.RC1IF)
        {
            PIR3bits.RC1IF = 0;
            msgadd[v] = RC1REG;
            T3CONbits.TMR3ON = 0;
            TMR3_Initialize();
            T3CONbits.TMR3ON = 1;
            if(v < 127)
            {
                v++;
            }
            
        }
    }
//    msgadd[v] = 0;
    return v;
}

bool get_snaprecord(void)
{
    errno = 0;
//    size_t y = sizeoff(snapurlh) + sizeoff(base64buf); base64buf[27] @ 0X2BB 0x2C = ,
 //   int x = snprintf(snap64buf, snapurlh, base64buf);
    int x = sprintf(snap64buf, "GET /merchant/api/v1/payments/ HTTP/1.1\r\nHost: pos.snapscan.io\r\n"
"Authorization: Basic %s\r\nUser-Agent: scandrop/0.1\r\nAccept: */*\r\n\r\n", base64buf);
    tcp_getsnapscan(0);
    gsmflags.msgavl = tcp_gethead(0);//0x46F 0x6b
    gsmflags.abrtmsg = gsmflags.msgavl;
    int z = 0;
	while(gsmflags.msgavl)
	{
		tgsmbyte = gsm_Read();
		gsmmsg[z++] = tgsmbyte;
		if(tgsmbyte == 0x7D)//end of first record is '}'
		{
            tcp_close();
			gsmflags.msgavl = 0;
//base640; // [{"id":15,"status":"completed","totalAmount":2500,
            /*Find the id of the last transaction
             and increment it for the next transaction*/
            searchbufa = strstr((const char*) gsmmsg, "\"id\":");
            searchbufa = searchbufa + 5; // "id":16,"status":"completed"
            z = 0;
            int x = z;
            while(z != ',')
            {
                z = searchbufa[x];
                if(z >= '0' && z <= '9')
                {
                    transid[x] = z;
                }
                x++;
            }
            transid[--x] = ' ';
            x++;
            cntlength = atol(transid);
            Store_Count(); //Initialize
           
            /*Delay = record times 5 in milliseconds divided by 60
             83 milliseconds per record*/
		}
	}
    return gsmflags.abrtmsg;
}

void Store_Count(void)//cntstore char* pBlah = (char*)&blah;
{
    uint8_t cs = 1;
    uint8_t y = 0;
    uint16_t x = 0;
    uint16_t z = cntstore;
    uint8_t *countbyte = (uint8_t*)&cntlength;
    while(x < 8)
    {
        DATAEE_WriteByte(z + x, countbyte[x]);
        cs = cs + countbyte[x];
        x++;
    }
    DATAEE_WriteByte(z + x, cs); //write checksum
}

bool Retrieve_Count(void)
{
    uint8_t cs = 1;
    uint8_t x = 0;
    uint16_t z = cntstore;
    uint8_t *countbyte = (uint8_t*)&countstore;
    while(x < 8)
    {
        countbyte[x] = DATAEE_ReadByte(z + x);
        cs = cs + countbyte[x];
        x++;
    }
    countbyte[x] = DATAEE_ReadByte(z + x); //Read checksum byte for compare
    if(cs != countbyte[x])
    {
        return 1;
    }
    return 0;//Success
}

void snap_buildurl(void)
{
    build_url();
    size_t one, two, three, four, five;
    const uint8_t Urlline1[] = "GET /merchant/api/v1/payments/";//cntlength goes here
    const uint8_t Urlline2[] = " HTTP/1.1\r\nHost: pos.snapscan.io\r\nAuthorization: Basic ";//base64buf goes here
    const uint8_t Urlline3[] = "User-Agent: curl/7.71.1\r\nAccept: */*\r\n\r\n";
    one   = strlen(Urlline1);
    two   = strlen(Urlline2);
    three = strlen(Urlline3);
    four = strlen(transid);
    five = strlen(base64buf);
    strcpy(snap64buf, Urlline1);
    strcpy(snap64buf + one, transid);
    strcpy(snap64buf + one + four, Urlline2);
    strcpy(snap64buf + one + four + two, base64buf);
    strcpy(snap64buf + one + four + two + five, Urlline3);
    snap64buf[ one + four + two + five + three + 1] = 0;
}

void build_url(void)
{
    /*.
     * cntlength contains the next record
     * and base64buf[64] contains a base64 constant string of a key
     */                  
                     
    translngth = sprintf(snap64buf, "GET /merchant/api/v1/payments/%lld HTTP/1.1\r\nHost: pos.snapscan.io\r\n"
"Authorization: Basic %s\r\nUser-Agent: scandrop/0.1\r\nAccept: */*\r\n\r\n", cntlength, base64buf);
//    printf("%s", urlbuf);
    asm("NOP");

}


/*char * strncpy(char *dest, const char *src, size_t n) { 
    size_t i; 

    for (i = 0; i < n && src[i] != '\0'; i++) 
        dest[i] = src[i]; 
    for ( ; i < n; i++) 
        dest[i] = '\0'; 

    return dest; }*/

/*
void Start_TMR4(void)
{
    IFS0bits.T4IF = 0;
    TMR4_Initialize();
    PR4 = 0xFFFF; //Maximum time 527~mS
    TMR4_Start();
}
*/
void Delay_60mil(void)
{
__delay_ms(60);
}

bool gsm_waitstart(void)
{
    uint8_t x = 0;
    while(tgsmbyte != '>')
    {
        tgsmbyte = EUSARTG_Read();
        x++;
        if(x >= 255)
        {
            return 1;
        }
    }
    tgsmbyte = EUSARTG_Read();
    return 0;
}
#if 0
uint8_t entbuf[256];
unsigned int seed;
#define epoch_year 1970

time_t time(time_t *tloc)
{
    //We only return a time_t integer not a *tloc
    if(tloc != NULL)
    {
        return -1;
    }
    gsm_msg((uint8_t*)"AT+CCLK?\r");
    gsm_receive(2,entbuf);

	time_t result;

	unsigned int actyear;
    unsigned int months;
	unsigned int leapdays;
	unsigned int days;
	unsigned int seconds;
    unsigned int mday;
    unsigned int hours;
    unsigned int minutes;
    unsigned int secs;

	actyear = (((entbuf[8] & 0x0F) * 10) + (entbuf[9] & 0x0F) + 2000);
	months = ((entbuf[11] & 0x0F) * 10) + (entbuf[12] & 0x0F) - 1;// Month, where 0 = jan
	mday = ((entbuf[14] & 0x0F) * 10) + (entbuf[15] & 0x0F);// Day of the month
	hours = ((entbuf[17] & 0x0F) * 10) + (entbuf[18] & 0x0F);
	minutes = ((entbuf[20] & 0x0F) * 10) + (entbuf[21] & 0x0F);
	secs = ((entbuf[23] & 0x0F) * 10) + (entbuf[24] & 0x0F);

	leapdays = (actyear - 1968) / 4;
	days = ((actyear - 1970) * 365) + (months * 30) + leapdays + mday + 1;//Where do I loose the 1 day?
	seconds = days * 86400;
	seconds = seconds + (hours * 60 * 60) + (minutes * 60) + secs;
	result = (time_t)seconds;
    return result;

}
#endif
