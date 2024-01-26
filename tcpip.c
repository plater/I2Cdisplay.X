/* 
 * File:   tcpip.c
 * Author: Dave Plater
 *
 * Created on June 23, 2020, 4:00 PM
 */
#include "buffers.h"
#include "tcpip.h"
#include <string.h>
#include "mcc_generated_files/mcc.h"
uint32_t rdcount;
uint32_t tdcount;
#define time_t uint32_t
uint32_t translngth;
uint8_t * searchbufa;
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
} tcpflags;


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
//SNTP sync
const uint8_t ntpbp1[] = "AT+CNTPCID=1\r";
const uint8_t ntpsrv[] = "AT+CNTP=\"za.pool.ntp.org\",0\r";
const uint8_t ntpstr[] = "AT+CNTP\r";

const uint8_t tcpfun[] = "AT+CFUN=1\r";

const uint8_t funtest[] = "AT+CFUN?\r";

const uint8_t brropen[] = "AT+SAPBR=1,1\r";
const uint8_t snapurl[] = "AT+CIPSTART=\"TCP\",\"pos.snapscan.io\",\"443\"\r";
const uint8_t snapgetid[] = "GET /merchant/api/v1/payments/";
const uint8_t snapnoid[] = "HTTP/1.1\r\n";
const uint8_t snapcommon[] = "Host: pos.snapscan.io\r\n\
Authorization: Basic MjJkM2NmNGYtZGIwNS00NjA5LTk3NzMtMjMxMjM3NWI0NTIzOg==\r\n\
User-Agent: curl/7.71.1\r\n\
Accept: */*\r\n\r\n";
const uint8_t snapgettran[] = "GET /merchant/api/v1/payments/ HTTP/1.1\r\n\
Host: pos.snapscan.io\r\n\
Authorization: Basic MjJkM2NmNGYtZGIwNS00NjA5LTk3NzMtMjMxMjM3NWI0NTIzOg==\r\n\
User-Agent: curl/7.71.1\r\n\
Accept: */*\r\n\r\n";

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
uint8_t gsmmsg[512];//__attribute__((section("tcpsection"),address(0xA0001000)));
uint8_t transid[24];// __attribute__((section("tcpsection")));
uint32_t cntlength;// __attribute__((section("tcpsection")));
//
#if 0
//gsm scratch pad
uint8_t gsmmsg[512];
//sms storage
uint8_t gsmums[512];
 //Store date
uint8_t gsdate[10];
//Store time
uint8_t gstime[10];
uint8_t gsmtim[23];
//Store date
uint8_t gsdate[10];
//Store time
uint8_t gstime[10];
#endif


void tcp_connect(void)
{
	static char searchbuf[32];
tcprep:
    gsm_msg((uint8_t*)funtest);//"AT+CFUN?\r"
    gsm_receive(3, gsmusd);
	gsm_msg((uint8_t*)tcpfun);//"AT+CFUN=1\r"
    gsm_receive(1, gsmusd);
    gsm_msg((uint8_t*)shuttcp);//CIPSHUT
    gsm_receive(2, gsmusd);
    gsm_msg((uint8_t*)tcptest);//CGATT? is attached to GPRS?
    gsm_receive(2, gsmusd);//gsmusd[8] must equal '1' then gsm is connected
//	SEARCH for "+CGATT: 1"
	searchbufa = strstr((const char*) gsmusd, "+CGATT: 1");
	if(!searchbufa)
	{
		goto tcprep;
	}
    
}

bool tcp_getip(void)
{
    gsm_msg((uint8_t*)tcpconn);//CSTT="Internet"
    gsm_receive(1, gsmusd);
    gsm_msg((uint8_t*)tcpup);//CIICR
    gsm_receive(1, gsmusd);
    if(gsmusd[0] != '0')
    {
        return 1;
    }
    gsm_msg((uint8_t*)tcpgetip);//CIFSR
    gsm_receive(2, gsmusd);
    return 0;
}

void ntp_connect(void)
{
    tcprep:
    tcp_connect();
    if(tcp_getip())
    {
        goto tcprep;
    }
    gsm_msg((uint8_t*)brrgprs);//AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r"
    gsm_receive(1, gsmusd);
    gsm_msg((uint8_t*)brrapn);//"AT+SAPBR=3,1,\"APN\",\"internet\"\r"
    gsm_receive(1, gsmusd);
    gsm_msg((uint8_t*)brropen);//"AT+SAPBR=1,1\r"
    gsm_receive(1, gsmusd);
    gsm_msg((uint8_t*)ntpbp1);//"AT+CNTPCID=1\r" Use bearer profile 1
    gsm_receive(1, gsmusd);
    gsm_msg((uint8_t*)ntpsrv);//"AT+CNTP=\"za.pool.ntp.org\",0")
    gsm_receive(1, gsmusd);
    //Synchronize to ntp public server
    gsm_msg((uint8_t*)ntpstr);//AT+CNTP start ntp clock
    gsm_receive(3, gsmusd);
    if (gsmusd[12] == 6)
    {
        goto tcprep;
    }
    tcpflags.msggod = 1;
    gsm_gettime();
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
/** Enable built in tls*/
	gsm_msg((uint8_t*)"AT+CIPSSL=1\r");
	gsm_receive(1, gsmusd);

	gsm_msg((uint8_t*)snapurl);//"AT+CIPSTART=\"TCP\",\"pos.snapscan.io\",\"443\"\r";
	gsm_receive(3, gsmusd);//0\r\n \r\nCONNECT OK\r\n (1\r\n)
	tcpflags.msgavl = 1;
	tcpflags.eomsg = 0;
/** Use built in tls over tcp */
	gsm_msg((uint8_t*)"AT+CIPSEND\r");
	tcpflags.abrtmsg = gsm_waitstart();//Wait for >
    if(getpayment)
    {
        gsm_msg((uint8_t*)snapgetid);
        gsm_msg((uint8_t*)transid);
        gsm_msg((uint8_t*)snapcommon);
    }
    else
    {
        gsm_msg((uint8_t*)snapgettran);
    }
	gsm_transmit(0x1A); //Send Ctrl+Z at end of transmission
}

uint8_t tcp_getid(void)
{
    tcp_getsnapscan(1);
    tcp_gethead();
    /*HTTP/1.1 404 Not Found*/
	int z = 0;
    int x;
    tcpflags.msgavl = 1;
    while(tcpflags.msgavl)
    {
        tgsmbyte = gsm_Read();
        if(tgsmbyte == '}')
        {
            tcpflags.msgavl = 0;
            gsmmsg[z++] = NULL;
            break;
        }
        gsmmsg[z++] = tgsmbyte;        
    }
    tcp_close();
    uint8_t ret = 0;
    searchbufa = strstr(qrbuffer, "404 Not Found");
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
    searchbufa = strstr(gsmmsg, "\"status\":\"error\"");
    if(searchbufa)
    {
        //Case where payment declined
        Graphic_Clear();
        Write_String(declinemsg, 3);
        snap_incid();
        return 0xFF;
    }
    searchbufa = strstr(gsmmsg, "\"status\":\"completed\"");
    if(searchbufa)
    {
        Graphic_Clear();
        //Payment succeeded 
        Write_String(aprovemsg, 3);
        snap_incid();
        return 1;
    }
    
}

void snap_incid(void)
{
    ++cntlength;
    translngth = sprintf(transid, "%d HTTP/1.1\r\n", cntlength);
}

void tcp_gethead(void)
{

	int z = 0;
//	uint8_t buf[1850];//1850 - 1455 = 395
    
    while(tcpflags.msgavl)
    {
        tgsmbyte = gsm_Read();
        if(tgsmbyte == '{')
        {
            tcpflags.msgavl = 0;
            qrbuffer[z++] = NULL;
            break;
        }
        qrbuffer[z++] = tgsmbyte;        
    }
}

void tcp_close(void)
{
	gsm_msg((uint8_t*)"AT+CIPCLOSE/r");
//	gsm_receive(2, gsmusd);
    Delay_60mil();
    gsm_msg((uint8_t*)"AT+CIPCLOSE/r");
    repshut:
    Delay_60mil();
	gsm_msg((uint8_t*)shuttcp);//CIPSHUT
	gsm_receive(1, gsmusd);
    if(gsmusd[0] == '4')
    {
        goto repshut;
    }
    gsm_receive(1, gsmusd);
/*	gsm_msg((uint8_t*)"AT+CIPSSL=0/r");
	gsm_receive(1, gsmusd);
*/
}
void get_snaprecord(void)
{
    tcp_getsnapscan(0);
    tcp_gethead();
    int z = 0;
    uint32_t contlength;
    tcpflags.msgavl = 1;
	while(tcpflags.msgavl)
	{
		tgsmbyte = gsm_Read();
		gsmmsg[z++] = tgsmbyte;
		if(tgsmbyte == 0x7D)//end of first record is '}'
		{
            LATDbits.LATD0 = 0;
			tcpflags.msgavl = 0; // [{"id":15,"status":"completed","totalAmount":2500,
            searchbufa = strstr((const char*) qrbuffer, lengthstr);
            searchbufa = searchbufa + 16;
            int x = 0;
            z = 0;
            while(z != 0x0D)
            {
                z = searchbufa[x++];
            }
            searchbufa[--x] = NULL;
            contlength = atol(searchbufa);
            /*Find the id of the last transaction
             and and increment it for the next transaction*/
            searchbufa = strstr((const char*) gsmmsg, "\"id\":");
            searchbufa = searchbufa + 5; // "id":16,"status":"completed"
            z = 0;
            x = z;
            while(z != ',')
            {
                z = searchbufa[x];
                transid[x++] = z;
            }
            transid[--x] = ' ';
            x++;
            cntlength = atol(transid);
            ++cntlength;
            translngth = sprintf(transid, "%d HTTP/1.1\r\n", cntlength);
            
            x = z;
           
            /*Delay = record times 5 in milliseconds divided by 60
             83 milliseconds per record*/
		}
	}
    Delay_60mil();
    TMR2_Initialize();
    TMR2_Start(); //5 seconds for gsm modem to stabilize
    LATDbits.LATD0 = 1;
    gsm_init();
    tcp_connect();
    ntp_connect();
    disp_clock();
}
/*char * strncpy(char *dest, const char *src, size_t n) { 
    size_t i; 

    for (i = 0; i < n && src[i] != '\0'; i++) 
        dest[i] = src[i]; 
    for ( ; i < n; i++) 
        dest[i] = '\0'; 

    return dest; }*/

void Start_TMR1(void)
{
    IFS0bits.T1IF = 0;
    TMR1_Initialize();
    TMR1_Start();
}

void Start_TMR4(void)
{
    IFS0bits.T4IF = 0;
    TMR4_Initialize();
    PR4 = 0xFFFF; //Maximum time 527~mS
    TMR4_Start();
}

void Delay_60mil(void)
{
    TMR5_Initialize(); // 60ms timer
    T5CONbits.ON = 1;
    while(!IFS0bits.T5IF){}
    T5CONbits.ON = 0;
    IFS0CLR= 1 << _IFS0_T5IF_POSITION;
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

